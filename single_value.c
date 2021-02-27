#include "single_value.h"

void single_value (int *start, int *count, int *value, int buffer[], int buffer_size) {
    int i, s = *start, c = *count, v = -1;

    if ( (s + c) % buffer_size == 0 ) v = *value;

    for (i = 0; i < buffer_size; i++) {
        if (buffer[i] < 0 || buffer[i] > 5) continue;

        if (buffer[i] == v) c++;
        else {
            if (c > *count) {
                *count = c;
                *start = s;
                *value = v;
            }

            v = buffer[i];
            c = 1;
            s = i+1;
        }
    }
}