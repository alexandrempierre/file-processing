#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include <counting_seq.h>
#include <single_value.h>
#include <triplets.h>
#include <threads.h>
#include <print_results.h>

#define N_CONSUMERS 3

// void *counting (void *);
// void *triplets (void *);
// void *single_value (void *);

void counting_seq_action(buffer_block_t*);
void triplets_action(buffer_block_t*);
void single_value_action(buffer_block_t*);

int main(int argc, char const *argv[])
{
    #if 0

    int buffer_contents[] = {1, 2, 3, 1, 1, 1, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 3, 3, 3, 0, 1, 2, 3, 4, 5, 0};

    for (int i = 0; i < BUFFER_SIZE; i++) { buffer[i] = buffer_contents[i]; }

    counting_seq_data_t counting_seq_data = new_counting_seq_data();
    single_value_data_t single_value_data = new_single_value_data();
    triplets_data_t triplets_data = new_triplets_data();
    
    counting_seq(&counting_seq_data, buffer, buffer_size);
    single_value(&single_value_data, 0, buffer, buffer_size);
    triplets(&triplets_data, buffer, buffer_size);

    print_single_value(&single_value_data);
    print_triplets(&triplets_data);
    print_counting_seq(&counting_seq_data);

    #endif

    // TODO: Get file name and sizes from command line arguments
    llint buffer_capacity = 10;
    llint buffer_block_size = 10;

    char* file_name = "test.input";
    FILE* file = fopen(file_name, "rb");

    if(file == NULL) {
        printf("Could not open: %s\n", file_name);
        exit(1);
    }

    circular_buffer_t buffer = new_circular_buffer(buffer_capacity);
    thread_data_t shared_data = new_thread_data(&buffer);

    producer_thread_t file_thread = new_producer_thread(buffer_block_size, file, &shared_data);
    consumer_thread_t counting_seq_thread = new_consumer_thread(N_CONSUMERS, &shared_data, counting_seq_action);
    consumer_thread_t triplets_thread = new_consumer_thread(N_CONSUMERS, &shared_data, triplets_action);
    consumer_thread_t single_value_thread = new_consumer_thread(N_CONSUMERS, &shared_data, single_value_action);

    pthread_t pids[N_CONSUMERS + 1];
    start_producer_thread(&file_thread, &pids[0]);
    start_consumer_thread(&counting_seq_thread, &pids[1]);
    start_consumer_thread(&triplets_thread, &pids[2]);
    start_consumer_thread(&single_value_thread, &pids[3]);

    for(int i = 0; i < N_CONSUMERS + 1; i++) {
        pthread_join(pids[i], NULL);
    }

    return 0;
}

void counting_seq_action(buffer_block_t* block) {

}
void triplets_action(buffer_block_t* block) {

}

void single_value_action(buffer_block_t* block) {

}

