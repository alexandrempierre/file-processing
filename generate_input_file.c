#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <common_defs.h>

#include <counting_seq.h>
#include <single_value.h>
#include <triplets.h>
#include <print_results.h>

#define USE_KNOWN_INPUT 0

#define WRITE_BLOCK_SIZE 1024

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

    srand(time(NULL));

    write_file_size(file, file_size);
    write_random_blocks(file, file_size);

    fclose(file);
}

void write_file_size(FILE* file, llint file_size) {
    fwrite(&file_size, sizeof(llint), 1, file);
}

void fill_with_random_numbers(int* write_buffer, llint numbers_to_write) {
    #if USE_KNOWN_INPUT
    
    static int j = 0;
    int buffer_contents[] = {1, 2, 3, 1, 1, 1, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 3, 3, 3, 0, 1, 2, 3, 4, 5, 0};

    for(int i = 0; i < numbers_to_write; i++) {
        write_buffer[i] = buffer_contents[j++];
    }

    #else

    for(int i = 0; i < numbers_to_write; i++) {
        write_buffer[i] = rand() % 6;
    }

    #endif
}

void write_random_blocks(FILE* file, llint file_size) {
    counting_seq_data_t counting_seq_data = new_counting_seq_data();
    single_value_data_t single_value_data = new_single_value_data();
    triplets_data_t triplets_data = new_triplets_data();

    llint numbers_written = 0;
    int* write_buffer = (int*) malloc(WRITE_BLOCK_SIZE * sizeof(int));

    while(numbers_written < file_size) {
        llint numbers_to_write = (file_size - numbers_written) < WRITE_BLOCK_SIZE ?
                                 (file_size - numbers_written) :
                                 WRITE_BLOCK_SIZE;

        fill_with_random_numbers(write_buffer, numbers_to_write);

        counting_seq(&counting_seq_data, write_buffer, numbers_to_write);
        single_value(&single_value_data, numbers_written, write_buffer, numbers_to_write);
        triplets(&triplets_data, write_buffer, numbers_to_write);

        fwrite(write_buffer, sizeof(int), numbers_to_write, file);
        numbers_written += numbers_to_write;
    }

    printf("Arquivo preenchido com as seguintes características:\n");
    print_single_value(&single_value_data);
    print_triplets(&triplets_data);
    print_counting_seq(&counting_seq_data);

    free(write_buffer);
}