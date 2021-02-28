#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include <counting_seq.h>
#include <single_value.h>
#include <triplets.h>
#include <threads.h>
#include <timer.h>
#include <print_results.h>

#define N_CONSUMERS 3

counting_seq_data_t counting_seq_data;
single_value_data_t single_value_data;
triplets_data_t triplets_data;

void counting_seq_action(buffer_block_t*);
void triplets_action(buffer_block_t*);
void single_value_action(buffer_block_t*);

int main(int argc, char const *argv[])
{
    if(argc < 4) {
        printf("Usage: %s <BLOCK_SIZE: N> <NUMBER_OF_BLOCKS: M> <INPUT_FILE>\n", argv[0]);
        exit(1);
    }

    double t0;
    double t1;

    llint buffer_block_size = atoll(argv[1]);
    llint buffer_capacity = atoll(argv[2]);
    const char* file_name = argv[3];

    FILE* file = fopen(file_name, "rb");
    if(file == NULL) {
        printf("Could not open: %s\n", file_name);
        exit(1);
    }

    counting_seq_data = new_counting_seq_data();
    single_value_data = new_single_value_data();
    triplets_data = new_triplets_data();

    circular_buffer_t buffer = new_circular_buffer(buffer_capacity);
    thread_data_t shared_data = new_thread_data(&buffer);

    producer_thread_t file_thread = new_producer_thread(buffer_block_size, file, &shared_data);
    consumer_thread_t counting_seq_thread = new_consumer_thread(N_CONSUMERS, &shared_data, counting_seq_action);
    consumer_thread_t triplets_thread = new_consumer_thread(N_CONSUMERS, &shared_data, triplets_action);
    consumer_thread_t single_value_thread = new_consumer_thread(N_CONSUMERS, &shared_data, single_value_action);

    GET_TIME(t0);
    
    pthread_t pids[N_CONSUMERS + 1];
    start_producer_thread(&file_thread, &pids[0]);
    start_consumer_thread(&counting_seq_thread, &pids[1]);
    start_consumer_thread(&triplets_thread, &pids[2]);
    start_consumer_thread(&single_value_thread, &pids[3]);

    for(int i = 0; i < N_CONSUMERS + 1; i++) {
        pthread_join(pids[i], NULL);
    }

    GET_TIME(t1);

    print_single_value(&single_value_data);
    print_triplets(&triplets_data);
    print_counting_seq(&counting_seq_data);

    printf("Time: %lfs\n", t1 - t0);

    delete_thread_data(&shared_data);
    fclose(file);

    return 0;
}

void counting_seq_action(buffer_block_t* block) {
    counting_seq(&counting_seq_data, block->block_data, block->block_size);
}

void triplets_action(buffer_block_t* block) {
    single_value(&single_value_data, block->numbers_already_read, block->block_data, block->block_size);
}

void single_value_action(buffer_block_t* block) {
    triplets(&triplets_data, block->block_data, block->block_size);
}

