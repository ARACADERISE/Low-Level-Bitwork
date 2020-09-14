#include <stdio.h>
#include "src/binary_set/set.h"

int main(void) {

    int** items = calloc(4,sizeof(*items));
    items[0] = calloc(2,sizeof(*items[0]));
    items[0][0] = 10;
    items[0][1] = 20;

    BinaryDataStruct* b_d_s = init_binary_data_struct(binary_set_current_ptr, items);

    allign_bits(b_d_s, 1, 10, 2); // offset of one for extra memory

    for(int i = 0; i < b_d_s->amount_of_sections; i++) {
        for(int j = 0; j < b_d_s->amount_of_bits_in_each_section; j++) {
            printf("%d\n",b_d_s->binary_sections[i][j]);
        }
    }

    return 0;
}