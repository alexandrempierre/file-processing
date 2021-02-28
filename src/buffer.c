#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include <common_defs.h>
#include <buffer.h>


buffer_block_t new_buffer_block(int* data, llint size, llint numbers_already_read) {
    buffer_block_t block = {
        .block_data = data,
        .block_size = size,
        .numbers_already_read = numbers_already_read
    };

    return block;
}

circular_buffer_t new_circular_buffer(llint capacity) {
    circular_buffer_t buffer = {
        .buffer_capacity = capacity,
        .buffer_data = (buffer_block_t*) malloc(capacity * sizeof(buffer_block_t)),
        .buffer_count = 0,
        .start_index = 0
    };

    return buffer;
}

bool is_full(circular_buffer_t* buffer) {
    return buffer->buffer_count == buffer->buffer_capacity;
}

bool is_empty(circular_buffer_t* buffer) {
    return buffer->buffer_count == 0;
}

void enqueue_block(circular_buffer_t* buffer, buffer_block_t block) {
    assert(!is_full(buffer));

    llint current_index = (buffer->start_index + buffer->buffer_count) % buffer->buffer_capacity;
    buffer->buffer_data[current_index] = block;

    buffer->buffer_count++;
}

void dequeue_block(circular_buffer_t* buffer) {
    assert(!is_empty(buffer));

    buffer->start_index = (buffer->start_index + 1) % buffer->buffer_capacity;
    buffer->buffer_count--;
}

buffer_block_t* get_first_block(circular_buffer_t* buffer) {
    assert(!is_empty(buffer));

    return &buffer->buffer_data[buffer->start_index];
}