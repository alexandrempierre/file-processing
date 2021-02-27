#include "single_value.h"

single_value_data_t new_single_value_data() {
    single_value_data_t result = {
        .count_largest = 0,
        .start_largest = 0,
        .value_largest = -1,

        .count_current = 0,
        .start_current = 0,
        .value_current = -1
    };

    return result;
}

// TODO: Start depende do de qual bloco do arquivo está sendo lido e não pode receber o valor de i simplesmente
// TODO: Como o tamanho do arquivo é um long long, start e count também devem ser long long
void single_value (single_value_data_t* data, int numbers_before_buffer, int buffer[], int buffer_size) {
    for (int i = 0; i < buffer_size; i++) {
        // NOTE: Nao deve ocorrer
        if (buffer[i] < 0 || buffer[i] > 5) continue;

        if (buffer[i] == data->value_current) data->count_current++;
        else {
            if (data->count_current > data->count_largest) {
                data->count_largest = data->count_current;
                data->start_largest = data->start_current;
                data->value_largest = data->value_current;
            }

            data->value_current = buffer[i];
            data->count_current = 1;
            data->start_current = numbers_before_buffer + i + 1;
        }
    }
}