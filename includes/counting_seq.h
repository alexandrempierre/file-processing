#ifndef COUNTING_SEQ_H
#define COUNTING_SEQ_H

typedef struct
{
    int count;
    int query;
} counting_seq_data_t;


counting_seq_data_t new_counting_seq_data();
void counting_seq (counting_seq_data_t*, int [], int);

#endif