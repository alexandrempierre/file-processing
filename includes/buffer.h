#ifndef BUFFER_H
#define BUFFER_H

#include <stdbool.h>

#include "common_defs.h"

typedef struct
{
    int* block_data;
    llint block_size;
    llint numbers_already_read;
} buffer_block_t;

typedef struct
{
    buffer_block_t* buffer_data;
    llint buffer_count;
    llint buffer_capacity;
    llint start_index;
} circular_buffer_t;


buffer_block_t new_buffer_block(int*, llint, llint);
circular_buffer_t new_circular_buffer(llint);

bool is_full(circular_buffer_t*);
bool is_empty(circular_buffer_t*);

void enqueue_block(circular_buffer_t*, buffer_block_t);
buffer_block_t* dequeue_block(circular_buffer_t*);

buffer_block_t* get_first_block(circular_buffer_t*);

#endif