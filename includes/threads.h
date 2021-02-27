#ifndef THREADS_H
#define THREADS_h

#include <stdio.h>
#include <pthread.h>

#include <common_defs.h>
#include <buffer.h>

typedef void (*consumer_action_f) (buffer_block_t*);

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t empty_buffer_cond;
    pthread_cond_t full_buffer_cond;

    circular_buffer_t* buffer;
} thread_data_t;

typedef struct
{
    thread_data_t* thread_data;
    consumer_action_f action;
    int n_consumers;
} consumer_thread_t;

typedef struct
{
    thread_data_t* thread_data;
    FILE* input_file;
    llint block_size;
} producer_thread_t;

thread_data_t new_thread_data(circular_buffer_t*);
void delete_thread_data(thread_data_t*);

consumer_thread_t new_consumer_thread(int, thread_data_t*, consumer_action_f);
producer_thread_t new_producer_thread(llint, FILE*, thread_data_t*);

void* producer_thread(void*);
void* consumer_thread(void*);

void start_producer_thread(producer_thread_t*, pthread_t*);
void start_consumer_thread(consumer_thread_t*, pthread_t*);

#endif