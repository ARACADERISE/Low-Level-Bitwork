#include "set.h"

BinaryDataStruct* init_binary_data_struct(int BINARY_POINTER, int* __data) {
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
int** resolve_into_sections(BinaryDataStruct* b_d_s,int* __data, int __sec_size) {

    int index = 0, current_sec_size = 0, total_amount_of_arrays = 0, current_used_array = 0;
    for(;; index++) {
        if(!(__data[index])) break;
        current_sec_size++;

        if(current_sec_size == __sec_size) {
            total_amount_of_arrays++;
            b_d_s->binary_sections = realloc(
                b_d_s->binary_sections,
                total_amount_of_arrays*sizeof(*b_d_s->binary_sections)
            );
            current_sec_size = 0;
        }

        if(current_sec_size == 0) {
            b_d_s->binary_sections[total_amount_of_arrays] = realloc(
                b_d_s->binary_sections,
                (current_sec_size+1)*sizeof(*b_d_s->binary_sections[total_amount_of_arrays])
            );
        } else {
            b_d_s->binary_sections[total_amount_of_arrays] = realloc(
                b_d_s->binary_sections,
                current_sec_size*sizeof(*b_d_s->binary_sections[total_amount_of_arrays])
            );
        }

        b_d_s->binary_sections[total_amount_of_arrays][current_sec_size] = __data[index];
        
    }

    return b_d_s->binary_sections;
}