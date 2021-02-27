#include <stdio.h>
#include <stdlib.h>

#include "common_defs.h"

#include "counting_seq.h"
#include "single_value.h"
#include "triplets.h"

#define WRITE_BLOCK_SIZE 10

void write_file_size(FILE* file, llint file_size);
void fill_with_random_numbers(int* write_buffer, llint numbers_to_write);
void write_random_blocks(FILE* file, llint file_size);

int main(int argc, char** argv) {
    if(argc < 3)
    {
        printf("Usage: %s <FILE_SIZE> <FILE_NAME>\n", argv[0]);
        exit(1);
    }

    llint file_size = atoll(argv[1]);
    char* file_name = argv[2];

    FILE* file = fopen(file_name, "wb");

    write_file_size(file, file_size);
    write_random_blocks(file, file_size);

    fclose(file);

    // int query = 0;
    // int count_single = 0, sing_start = 0, sing_value = -1;
    // int count_triplets = 0, count_val = 0, value = -1;

    // int count_seqs = counting_seq(0, &query, buffer, buffer_size);

    
    // single_value(&sing_start, &count_single, &sing_value, buffer, buffer_size);

    
    // count_triplets = triplets(&value, &count_val, 0, buffer, buffer_size);

}

void write_file_size(FILE* file, llint file_size) {
    fwrite(&file_size, sizeof(llint), 1, file);
}

void fill_with_random_numbers(int* write_buffer, llint numbers_to_write) {
    #if 0
    for(int i = 0; i < numbers_to_write; i++) {
        write_buffer[i] = rand() % 6;
    }
    #else

    static int j = 0;
    int buffer_contents[] = {1, 2, 3, 1, 1, 1, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 3, 3, 3, 0, 1, 2, 3, 4, 5, 0};

    for(int i = 0; i < numbers_to_write; i++) {
        write_buffer[i] = buffer_contents[j++];
    }

    #endif
}

void write_random_blocks(FILE* file, llint file_size) {
    llint numbers_written = 0;
    int* write_buffer = (int*) malloc(WRITE_BLOCK_SIZE * sizeof(int));

    while(numbers_written < file_size) {
        llint numbers_to_write = (file_size - numbers_written) < WRITE_BLOCK_SIZE ?
                                 (file_size - numbers_written) :
                                 WRITE_BLOCK_SIZE;

        fill_with_random_numbers(write_buffer, numbers_to_write);

        fwrite(write_buffer, sizeof(int), numbers_to_write, file);

        numbers_written += numbers_to_write;
    }

    free(write_buffer);
}