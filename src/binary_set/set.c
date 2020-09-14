#include "set.h"
#include <stdio.h>

BinaryDataStruct* init_binary_data_struct(int BINARY_POINTER, int** __data) {
    BinaryDataStruct* b_d_s = calloc(1,sizeof(*b_d_s));

    b_d_s->init_bit_data = __data;
    b_d_s->binary_sections = calloc(1,sizeof(*b_d_s->binary_sections));
    b_d_s->binary_sections[0] = calloc(1,sizeof(*b_d_s->binary_sections[0]));
    b_d_s->binary_bits = calloc(1,sizeof(*b_d_s->binary_bits));
    b_d_s->binary_bit_allignments = calloc(1,sizeof(*b_d_s->binary_bit_allignments));
    b_d_s->binary_section_alligned = calloc(1,sizeof(*b_d_s->binary_section_alligned));
    
    b_d_s->offset = 0;
    b_d_s->allignment = 0;
    b_d_s->left_over_memory = 0;
    b_d_s->bit_allocation_allignment = 0;
    b_d_s->current_alligned_size = 0;
    b_d_s->amount_of_offsets = 0;
    b_d_s->amount_of_allignments = 0;

    return b_d_s;
}
/* HELPER FUNCTIONS */
void* resolve_into_sections(BinaryDataStruct* b_d_s,int** __data, int __sec_size, size_t amount_of_elements) {
    int index=0,index_=0, amount_of_items=0, amount_of_arrays=0, total_items=0;

    for(;index <= amount_of_elements;index++) {

        if(amount_of_items == __sec_size) {
            amount_of_arrays++;
            b_d_s->binary_sections = realloc(
                b_d_s->binary_sections,
                amount_of_arrays*sizeof(int**)*sizeof(*b_d_s->binary_sections)
            );
            b_d_s->binary_sections[amount_of_arrays] = calloc(
                amount_of_items,
                sizeof(int**)*sizeof(*b_d_s->binary_sections)
            );
            total_items+=amount_of_items;

            amount_of_items = 0;
        }

        if(!(amount_of_items == 0)) {
            b_d_s->binary_sections[amount_of_arrays] = realloc(
                b_d_s->binary_sections[amount_of_arrays],
                amount_of_items*sizeof(int*)
            );
        }

        b_d_s->binary_sections[amount_of_arrays][amount_of_items] = __data[index_][index];

        amount_of_items++;
    }

    return b_d_s->binary_sections;
}