#include <counting_seq.h>

counting_seq_data_t new_counting_seq_data() {
    counting_seq_data_t result = {
        .count = 0,
        .query = 0
    };

    return result;
}

int counting_seq (counting_seq_data_t* data, int buffer[], int buffer_size) {
    int query = data->query;

    for (int i = 0; i < buffer_size; i++) {
        if (buffer[i] == query) {
            if (query == 5) data->count++;
            
            query = (query + 1) % 6;
        }
        else {
            query = 0;
        }
    }

    data->query = query;

    return data->count;
}