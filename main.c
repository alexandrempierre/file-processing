#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include <counting_seq.h>
#include <single_value.h>
#include <triplets.h>

#define BUFFER_SIZE 30

int buffer_size = BUFFER_SIZE;
int buffer[BUFFER_SIZE];

void print_single_value(single_value_data_t*);
void print_triplets(triplets_data_t*);
void print_counting_seq(counting_seq_data_t*);

// void *counting (void *);
// void *triplets (void *);
// void *single_value (void *);

int main(int argc, char const *argv[])
{
    int buffer_contents[] = {1, 2, 3, 1, 1, 1, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 3, 3, 3, 0, 1, 2, 3, 4, 5, 0};

    for (int i = 0; i < BUFFER_SIZE; i++) { buffer[i] = buffer_contents[i]; }

    counting_seq_data_t counting_seq_data = new_counting_seq_data();
    counting_seq(&counting_seq_data, buffer, buffer_size);

    single_value_data_t single_value_data = new_single_value_data();
    single_value(&single_value_data, buffer, buffer_size);

    triplets_data_t triplets_data = new_triplets_data();
    triplets(&triplets_data, buffer, buffer_size);

    print_single_value(&single_value_data);
    print_triplets(&triplets_data);
    print_counting_seq(&counting_seq_data);

    return 0;
}

// void *counting (void * arg) {

// }

// void *triplets (void * arg) {

// }

// void *single_value (void * arg) {

// }

void print_single_value(single_value_data_t* data) {
    printf("Maior sequência de valores idênticos: %d %d %d\n", data->start, data->count, data->value);
}

void print_triplets(triplets_data_t* data) {
    printf("Quantidade de triplas: %d\n", data->triplets_count);
}

void print_counting_seq(counting_seq_data_t* data) {
    printf("Quantidade de ocorrências da sequência <012345>: %d\n", data->count);
}