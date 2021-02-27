#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "counting_seq.h"
#include "single_value.h"
#include "triplets.h"

#define BUFFER_SIZE 30

int buffer_size = BUFFER_SIZE;
int buffer[BUFFER_SIZE];

// void *counting (void *);
// void *triplets (void *);
// void *single_value (void *);

int main(int argc, char const *argv[])
{
    int buffer_contents[] = {1, 2, 3, 1, 1, 1, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 3, 3, 3, 0, 1, 2, 3, 4, 5, 0};

    for (int i = 0; i < BUFFER_SIZE; i++) { buffer[i] = buffer_contents[i]; }

    int query = 0;
    int count_seqs = counting_seq(0, &query, buffer, buffer_size);

    int count_single = 0, sing_start = 0, sing_value = -1;
    single_value(&sing_start, &count_single, &sing_value, buffer, buffer_size);

    int count_triplets = 0, count_val = 0, value = -1;
    count_triplets = triplets(&value, &count_val, 0, buffer, buffer_size);

    printf("Maior sequência de valores idênticos: %d %d %d\n", sing_start, count_single, sing_value);
    printf("Quantidade de triplas: %d\n", count_triplets);
    printf("Quantidade de ocorrências da sequência <012345>: %d\n", count_seqs);

    return 0;
}

// void *counting (void * arg) {

// }

// void *triplets (void * arg) {

// }

// void *single_value (void * arg) {

// }