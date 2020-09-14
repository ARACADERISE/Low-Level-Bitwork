#include "set.h"
#include <stdio.h>

BinaryDataStruct* init_binary_data_struct(int BINARY_POINTER, int** __data) {
    BinaryDataStruct* b_d_s = calloc(1,sizeof(*b_d_s));

    b_d_s->init_bit_data = __data;
    b_d_s->binary_sections = calloc(1,sizeof(*b_d_s->binary_sections));
    b_d_s->binary_sections[0] = calloc(1,sizeof(*b_d_s->binary_sections));
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
    b_d_s->amount_of_sections = 0;
    b_d_s->amount_of_bits_in_each_section = 0;

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
                amount_of_arrays*sizeof(*b_d_s->binary_sections)*sizeof(int*)
            );
            b_d_s->binary_sections[amount_of_arrays] = calloc(
                amount_of_items,
                sizeof(int*)*sizeof(*b_d_s->binary_sections)
            );
            total_items+=amount_of_items;
            index_++;

            amount_of_items = 0;
        }

        if(amount_of_items != 0) {
            b_d_s->binary_sections[amount_of_arrays] = realloc(
                b_d_s->binary_sections[amount_of_arrays],
                amount_of_items*sizeof(*b_d_s->binary_sections)
            );
        }

        if(__data[index_]) b_d_s->binary_sections[amount_of_arrays][amount_of_items] = __data[index_][index];
        else free(__data[index_]);

        amount_of_items++;
    }

    b_d_s->amount_of_sections = index_;
    b_d_s->amount_of_bits_in_each_section = __sec_size;

    return b_d_s->binary_sections;
}

BinaryDataStruct* allign_bits(BinaryDataStruct* data_struct, int offset, int allignment, int amount_of_elements) {

    int outcome_number = 0;

    resolve_into_sections(data_struct, data_struct->init_bit_data, 2, amount_of_elements);

    for(int i = 0; i < data_struct->amount_of_sections; i++) {
        for(int j = 0; j < data_struct->amount_of_bits_in_each_section; j++) {
            outcome_number += data_struct->binary_sections[i][j] | allignment;
        }
    }

    int* cur = calloc(1,sizeof(*cur)), index = 0;
    for(int i = 0; i < data_struct->amount_of_sections; i++) {
        for(int j = 0; j < data_struct->amount_of_bits_in_each_section; j++) {
            data_struct->binary_sections[i][j] <<= allignment;

            cur = realloc(
                cur,
                index+1*sizeof(int*)
            );
            cur[index] = data_struct->binary_sections[i][j] / outcome_number;
            index++;
        }
    }

    float size = 0;
    float figure_by = 0;
    for(int i = 0; i < index; i++) {
        if(abs(cur[i]-cur[i+1]) == cur[i] || abs(cur[i]-cur[i+1]) == cur[i+1]) {
            size = abs(cur[i]-cur[i+1]);
            break;
        }
    }
    size = abs(~(int)size&allignment)|(offset << allignment);

    figure_by = size/40;

    size = size/figure_by;

    if(size == outcome_number) {
        // the value can only double its doubled value(or offset of 1)
        if(offset <= 2) {
            size = (int)size << offset;

            for(int i = 0; i < data_struct->amount_of_sections; i++) {
                for(int j = 0; j < data_struct->amount_of_bits_in_each_section; j++) {
                    data_struct->binary_sections[i][j] = (data_struct->binary_sections[i][j] << offset) / size;
                }
            }
        }
        
        if(size > outcome_number) {
            data_struct->left_over_memory = size-outcome_number;
        }
    }

    free(cur);

    return data_struct;
}