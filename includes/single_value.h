#ifndef SINGLE_VALUE_H
#define SINGLE_VALUE_H

typedef struct
{
    int start_largest;
    int count_largest;
    int value_largest;

    int start_current;
    int count_current;
    int value_current;
} single_value_data_t;

single_value_data_t new_single_value_data();
void single_value (single_value_data_t*, int, int [], int);

#endif