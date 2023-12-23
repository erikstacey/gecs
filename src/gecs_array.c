//
// Created by Erik on 2023-12-14.
//

#include "gecs_array.h"
#include <stdio.h>
#include <string.h>

GECS_Array* GECS_ArrayConstruct(GECS_TypeId type, GECS_ArrayIndex initSize) {
    // Creates a new array to hold data of the type specified by the GECS_TypeDefinition element in GECS_DEFINEDTYPES

    // Case where type doesn't exist
    if (type > GECS_NUMTYPES) {
        fprintf(stderr, "[GECS] Attempted to construct array with undefined type ID.\n");
        return NULL;
    }
    // Case where the length of the created array would be <1. The reason for the requirement that the array be of at
    // least size 1 (right now) is that malloc(0) behaves differently depending on platform
    else if (initSize <= 0) {
        fprintf(stderr, "[GECS] Attempted to construct array with <=0 initial size. For cross-platform reasons, please"
                        " initialize arrays with size at least 1.\n");
        return NULL;
    }
    else {
        // allocate array and set metadata
        GECS_Array* newArray = malloc(GECS_DEFINEDTYPES[type].size*initSize);
        newArray->type = type;
        newArray->length = initSize;
        newArray->itemSize = GECS_DEFINEDTYPES[type].size;
        return newArray;
    }
}

void GECS_ArrayResize(GECS_Array* array, GECS_ArrayIndex newLength) {
    // Resizes the array to hold newLength number of elements. If the resizing fails for whatever reason, this
    // leaves the array unmodified.
    void* oldPtr = array->data;
    // if the following fails, the original memory block is unmodified. The above statement lets us set the data pointer
    // back to this data block, gracefully handling a failure to reallocate.
    array->data = realloc(array->data, GECS_DEFINEDTYPES[array->type].size*newLength);
    if (array->data == NULL) {
        array->data = oldPtr;
        fprintf(stderr, "[GECS] Error: Failed to resize array and the array has not been modified!\n");
    }
    else {
        array->length = newLength;
    }
}

void* GECS_ArrayGet(GECS_Array* array, GECS_ArrayIndex index) {
    // Gets a void pointer to the first byte of the data element at the specified index
    // The caller is responsible for casting this to the appropriate type
    if (index > array->length-1) {
        fprintf(stderr, "[GECS] Error: Attempted to retrieve data from index exceeding length of array!\n");
    }
    else {
        char *newPtr = (char *) array;
        newPtr += index * GECS_DEFINEDTYPES[array->type].size;
        return (void *) newPtr;
    }
}

void GECS_ArrayAppend(GECS_Array* array, GECS_GData* data) {
    // Appends the data part of GData to the end of the array. The gdata structure is otherwise unmodified. Therefore,
    // if the user created the gdata object solely to append the contained data to the array, it should be freed.
    if (array == NULL) {
        fprintf(stderr, "[GECS] Error: Attempted to append to null array!\n");
    }
    else if (data == NULL) {
        fprintf(stderr, "[GECS] Error: Attempted to append to array with null data!\n");
    }
    else if (array->type != data->type) {
        fprintf(stderr, "[GECS] Error: Attempted to append wrong data type to array!\n");
    }
    else {
        GECS_ArrayResize(array, array->length+1);
        GECS_ArraySet(array, array->length-1, data);
    }
}

void GECS_ArraySet(GECS_Array* array, GECS_ArrayIndex index, GECS_GData* setTo) {
    // sets an array element at the specified index to the data held by the GData
    void* setAt = GECS_ArrayGet(array, index);
    memcpy(setAt, setTo->d, GECS_DEFINEDTYPES[setTo->type].size);
}