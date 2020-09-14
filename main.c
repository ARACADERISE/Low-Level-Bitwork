#include <stdio.h>
#include "src/binary_set/set.h"

int main(void) {

    int** items = calloc(1,sizeof(*items));
    items[0] = calloc(1,sizeof(*items[0]));
    items[0][0] = 10;
    items[0][1] = 20;

    BinaryDataStruct* b_d_s = init_binary_data_struct(binary_set_current_ptr, items);

    resolve_into_sections(b_d_s, b_d_s->init_bit_data, 2, 2);

    return 0;
}