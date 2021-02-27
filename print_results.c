#include <stdio.h>

#include <counting_seq.h>
#include <single_value.h>
#include <triplets.h>
#include <print_results.h>

void print_single_value(single_value_data_t* data) {
    printf("Maior sequência de valores idênticos: %d %d %d\n", data->start_largest, data->count_largest, data->value_largest);
}

void print_triplets(triplets_data_t* data) {
    printf("Quantidade de triplas: %d\n", data->triplets_count);
}

void print_counting_seq(counting_seq_data_t* data) {
    printf("Quantidade de ocorrências da sequência <012345>: %d\n", data->count);
}
