#include "counting_seq.h"

int counting_seq (int count, int *query, int buffer[], int buffer_size) {
    int i, q = *query;

    for (i = 0; i < buffer_size; i++) {
        if (buffer[i] == q) {
            if (q == 5) count++;
            
            q = (q + 1) % 6;
        }
        else {
            q = 0;
        }
    }

    *query = q;

    return count;
}