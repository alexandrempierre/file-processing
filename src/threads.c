#include <stdlib.h>
#include <pthread.h>

#include <buffer.h>

#include <threads.h>

thread_data_t new_thread_data(circular_buffer_t* buffer) {
    thread_data_t result;

    result.buffer = buffer;
    pthread_mutex_init(&result.mutex, NULL);
    pthread_cond_init(&result.empty_buffer_cond, NULL);
    pthread_cond_init(&result.full_buffer_cond, NULL);  

    return result;
}

void delete_thread_data(thread_data_t* data) {
    pthread_mutex_destroy(&data->mutex);
    pthread_cond_destroy(&data->empty_buffer_cond);
    pthread_cond_destroy(&data->full_buffer_cond);
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

void* producer_thread(void* _args) {
    producer_thread_t* producer_data = (producer_thread_t*) _args;

    pthread_exit(NULL);
}

void* consumer_thread(void* _args) {
    consumer_thread_t* consumer_data = (consumer_thread_t*) _args;

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