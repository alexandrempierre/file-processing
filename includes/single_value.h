#ifndef SINGLE_VALUE_H
#define SINGLE_VALUE_H

typedef struct
{
    int start;
    int count;
    int value;
} single_value_data_t;

single_value_data_t new_single_value_data();
void single_value (single_value_data_t*, int [], int);

#endif