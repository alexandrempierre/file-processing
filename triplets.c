#include "triplets.h"

triplets_data_t new_triplets_data() {
    triplets_data_t result = {
        .triplets_count = 0,
        .value_count = 0,
        .value = -1
    };

    return result;
}

void triplets (triplets_data_t* data, int buffer[], int buffer_size) {
    for (int i = 0; i < buffer_size; i++) {
        if (buffer[i] == data->value) {
            if ( ++data->value_count == 3 ) {
                data->triplets_count++;
                data->value_count = 0;
            }
        }
        else {
            data->value = buffer[i];
            data->value_count = 1;
        }
    }
}