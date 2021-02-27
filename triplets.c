#include "triplets.h"

int triplets (int *value, int *count_val, int count_triplets, int buffer[], int buffer_size) {
    int i, v = *value, cv = *count_val, ct = count_triplets;

    for (i = 0; i < buffer_size; i++) {
        if (buffer[i] == v) {
            if ( ++cv == 3 ) {
                ct++;
                cv = 0;
            }
        }
        else {
            v = buffer[i];
            cv = 1;
        }
    }
    
    *count_val = cv; *value = v;

    return ct;
}