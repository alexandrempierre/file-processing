#include <counting_seq.h>

counting_seq_data_t new_counting_seq_data() {
    counting_seq_data_t result = {
        .count = 0,
        .query = 0
    };

    return result;
}

void counting_seq (counting_seq_data_t* data, int buffer[], int buffer_size) {
    for (int i = 0; i < buffer_size; i++) {
        if (buffer[i] == data->query) {
            if (data->query == 5) data->count++;
            
            data->query = (data->query + 1) % 6;
        }
        else {
            data->query = 0;
        }
    }
}