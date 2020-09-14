#ifndef set
#define set
#include <stdlib.h>

typedef struct Binary_Data_Struct {

    enum {
        binary_set_current_ptr, // this will just be the current point of the binary allocation
        binary_set_ptr_end, // this will set the ptr of the binary "data" to the very last binary "digit"
        binary_set_ptr_mid // this will figure out the total length of the binary then figure where to assign the binary pointer at(dependable on the offset)
    } BinaryPtr;

    int** init_bit_data; // this will hold all initital values of each "bit" for possible reference when alligning or offsetting bits(or both)

    int offset; // offset of each bit
    int allignment; // allign each bit if possible
    int left_over_memory; // this will be the amount of memory left aside after the allignment of each bit_allocation_allignment
    int** binary_sections; // the binary will be split into "sections"
    size_t amount_of_sections;
    size_t amount_of_bits_in_each_section;

    int* binary_bits; // the sections will then be split to bits(another words, each bit of each "sections" will be pulled and stored seperately)
    int* binary_bit_allignments; // this will be each "bits" offset dependable on the shift of each binary "bit" off of the offset set by the user or each "bits" allignment
    /*
        Another words, the binary_bit_allignments will hold each "bit" after it was shifted depending on the offset set by the user or after the "bits" allignment
    */
    int* binary_section_alligned; // this will re-allign each section dependable on each "bit" after the shiftment of the offset or allignment

    size_t bit_allocation_allignment; // this will increment after each shift on each bit(or after each section is realligned), thus being the total allocated memory

    // current_alligned_size will hold the size even if it has an offset
    size_t current_alligned_size; // This will change after each "bit" is shifted, then it will be added to the "bit_allocation_allignment"

    /* Basic information for all allignments/offsets */
    size_t amount_of_offsets;
    size_t amount_of_allignments;
} BinaryDataStruct;

/*
    The BINARY_POINTER will set the pointer of where we are working with each bit at.

    The BINARY_POINTER enables the application to work on the binary side of things at a specific spot.
    This is helpful specifically for the fact that the user may just want to work with the "last" bit, or the "first" bit to the "last" bit, or the "middle" bit to the "last" bit.
    The BINARY_POINTER is based off of how frequently the user wants the allocation number/the output to change by.

    binary_set_current_ptr: Always set the pointer to the current bit. Meaning, the first bit is always accessed but there will be "helper functions" that enable us to access other bits depending on the first bit.
        binary_set_current_ptr changes the binary output/allocation size majorly.
    
    binary_set_ptr_mid: Set the pointer to the "middle" bit of the binary value. This means, we are working/changing only the other half of the bits.
        binary_set_ptr_mid is just a way of telling the application to not change the whole value of the binary size/output.
    
    binary_set_ptr_end: Set the pointer to the very "last" bit of the binary. This means we will only ever work with one bit, but this also indicates we can add some additional bits after it(if needed).
        binary_set_ptr_end indicates that we want to work with the very last "bit" of any value. It is also a indicator that the user is looking to elongate the initial value based off of the "last" bit.
        Another words, if you want everything but the very last "bit" of a value to stay the same, use binary_set_ptr_end.
*/
BinaryDataStruct* init_binary_data_struct(int BINARY_POINTER, int** __data);

/*
    allign_bit function:
        this will allign each bit accordingly.
        Each bit may have an offset, but that will be dependable on the BinaryPtr and what each bits "pointer" value is.
        Each bit will be alligned according to the "allignment" argument.

        The only reason a bit may not have an offset is due to the fact it will also be having an allignment and the allignment will either enable or disable the offset to cooperate with the bit.

        A bit allignment tries to enable each bit to be alligned to an allignment value for more accurate allocations, or another words:
            alligning a bit sets each bit to an "alligned" value, most likely allowing the allocation size to double its value.
            This is useful when you want strict alloctions, but want to make sure there is extra memory for addition allocations.
*/
BinaryDataStruct* allign_bits(BinaryDataStruct* data_struct, int offset, int allignment, int amount_of_elements);

#endif