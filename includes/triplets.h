#ifndef TRIPLETS_H
#define TRIPLETS_H

typedef struct
{
    int value;
    int value_count;
    int triplets_count;
} triplets_data_t;

triplets_data_t new_triplets_data();
int triplets (triplets_data_t*, int [], int);

#endif