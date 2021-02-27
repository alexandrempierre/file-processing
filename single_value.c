#include "single_value.h"

// TODO: Start depende do de qual bloco do arquivo está sendo lido e não pode receber o valor de i simplesmente
// TODO: Como o tamanho do arquivo é um long long, start e count também devem ser long long
void single_value (int *start, int *count, int *value, int buffer[], int buffer_size) {
    int i, s = *start, c = *count, v = -1;

    // TODO: Não entendi essa linha. V não deveria ser sempre value?
    if ( (s + c) % buffer_size == 0 ) v = *value;

    for (i = 0; i < buffer_size; i++) {
        // NOTE: Nao deve ocorrer
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