#include "single_value.h"

single_value_data_t new_single_value_data() {
    single_value_data_t result = {
        .count = 0,
        .start = 0,
        .value = -1
    };

    return result;
}

// TODO: Start depende do de qual bloco do arquivo está sendo lido e não pode receber o valor de i simplesmente
// TODO: Como o tamanho do arquivo é um long long, start e count também devem ser long long
void single_value (single_value_data_t* data, int buffer[], int buffer_size) {
    int start = data->start;
    int count = data->count;
    int value = -1;

    // TODO: Não entendi essa linha. V não deveria ser sempre value?
    if ( (start + count) % buffer_size == 0 ) value = data->value;

    for (int i = 0; i < buffer_size; i++) {
        // NOTE: Nao deve ocorrer
        if (buffer[i] < 0 || buffer[i] > 5) continue;

        if (buffer[i] == value) count++;
        else {
            if (count > data->count) {
                data->count = count;
                data->start = start;
                data->value = value;
            }

            value = buffer[i];
            count = 1;
            start = i+1;
        }
    }
}