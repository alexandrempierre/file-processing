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
    int value = data->value;
    int value_count = data->value_count;
    int triplets_count = data->triplets_count;

    for (int i = 0; i < buffer_size; i++) {
        if (buffer[i] == value) {
            if ( ++value_count == 3 ) {
                triplets_count++;
                value_count = 0;
            }
        }
        else {
            value = buffer[i];
            value_count = 1;
        }
    }
    
    data->value_count = value_count;
    data->value = value;
    data->triplets_count = triplets_count;
}