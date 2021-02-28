#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include <buffer.h>

#include <threads.h>

thread_data_t new_thread_data(circular_buffer_t* buffer) {
    thread_data_t result;

    pthread_mutex_init(&result.mutex, NULL);
    pthread_cond_init(&result.empty_buffer_cond, NULL);
    pthread_cond_init(&result.full_buffer_cond, NULL);  
    pthread_cond_init(&result.consumer_barrier_cond, NULL); 

    result.buffer = buffer;
    result.consumers_on_barrier = 0;
    result.no_more_work = false;
    result.file_has_ended = false;

    return result;
}

void delete_thread_data(thread_data_t* data) {
    pthread_mutex_destroy(&data->mutex);
    pthread_cond_destroy(&data->empty_buffer_cond);
    pthread_cond_destroy(&data->full_buffer_cond);
    pthread_cond_destroy(&data->consumer_barrier_cond);
}

consumer_thread_t new_consumer_thread(int n_consumers, thread_data_t* thread_data, consumer_action_f action) {
    consumer_thread_t result = {
        .n_consumers = n_consumers,
        .thread_data = thread_data,
        .action = action
    };

    return result;
}

producer_thread_t new_producer_thread(llint block_size, FILE* file, thread_data_t* thread_data) {
    producer_thread_t result = {
        .block_size = block_size,
        .input_file = file,
        .thread_data = thread_data
    };

    return result;
}

void put_block_into_buffer(thread_data_t* thread_data, buffer_block_t block) {
    circular_buffer_t* buffer = thread_data->buffer;

    pthread_mutex_lock(&thread_data->mutex);

    while(is_full(buffer)) {
        pthread_cond_wait(&thread_data->full_buffer_cond, &thread_data->mutex);
    }

    enqueue_block(buffer, block);

    // TODO: Should this be a broadcast?
    pthread_cond_signal(&thread_data->empty_buffer_cond);
    pthread_mutex_unlock(&thread_data->mutex);
}

buffer_block_t* read_block_from_buffer(thread_data_t* thread_data) {
    circular_buffer_t* buffer = thread_data->buffer;

    pthread_mutex_lock(&thread_data->mutex);

    while(is_empty(buffer)) {
        pthread_cond_wait(&thread_data->empty_buffer_cond, &thread_data->mutex);
    }

    buffer_block_t* block = get_first_block(buffer);

    pthread_mutex_unlock(&thread_data->mutex);

    return block;
}

void wait_on_barrier(consumer_thread_t* consumer_data) {
    thread_data_t* thread_data = consumer_data->thread_data;
    pthread_mutex_lock(&thread_data->mutex);

    int order = ++thread_data->consumers_on_barrier;

    if (thread_data->consumers_on_barrier < consumer_data->n_consumers) {
        pthread_cond_wait(&thread_data->consumer_barrier_cond, &thread_data->mutex);
    }

    // NOTE: The last thread do the cleaning
    if(order == consumer_data->n_consumers) {
        thread_data->consumers_on_barrier = 0;
        dequeue_block(thread_data->buffer);

        if(thread_data->file_has_ended && is_empty(thread_data->buffer)) {
            thread_data->no_more_work = true;
        }
        
        pthread_cond_signal(&thread_data->full_buffer_cond);
        pthread_cond_broadcast(&thread_data->consumer_barrier_cond);
    }

    pthread_mutex_unlock(&thread_data->mutex);
}

void* producer_thread(void* _args) {
    producer_thread_t* producer_data = (producer_thread_t*) _args;

    llint total_numbers_read = 0;
    while (!feof(producer_data->input_file)) {
        int* block_data = (int*) malloc(producer_data->block_size * sizeof(int));

        llint numbers_read = fread(block_data, sizeof(int), producer_data->block_size, producer_data->input_file);

        buffer_block_t block = new_buffer_block(block_data, numbers_read, total_numbers_read);

        put_block_into_buffer(producer_data->thread_data, block);

        total_numbers_read += numbers_read;
    }

    // NOTE: Since 'file_has_ended' only changes from 'false' to 'true' while
    // the program is running, we can change it without a mutex
    producer_data->thread_data->file_has_ended = true;

    pthread_exit(NULL);
}

void* consumer_thread(void* _args) {
    consumer_thread_t* consumer_data = (consumer_thread_t*) _args;

    while (!consumer_data->thread_data->no_more_work) {
    
        buffer_block_t* block = read_block_from_buffer(consumer_data->thread_data);

        consumer_data->action(block);

        // TODO: Can we improve this code and stop using a barrier?
        wait_on_barrier(consumer_data);
    }
    
    pthread_exit(NULL);
}

void start_producer_thread(producer_thread_t* thread, pthread_t* pid) {
    int error = pthread_create(pid, NULL, producer_thread, thread);

    if(error) {
        printf("Error creating producer thread\n");
        exit(1);
    }
}
void start_consumer_thread(consumer_thread_t* thread, pthread_t* pid) {
    int error = pthread_create(pid, NULL, consumer_thread, thread);

    if(error) {
        printf("Error creating consumer thread\n");
        exit(1);
    }
}