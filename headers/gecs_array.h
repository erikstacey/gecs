//
// Created by Erik on 2023-12-14.
//

#ifndef GECS_GECSARRAY_H
#define GECS_GECSARRAY_H
#include "gecs_typedefs.h"
#include "gecs_gdata.h"
#include <stdlib.h>

typedef uint32_t GECS_ArrayIndex;

typedef struct {
    GECS_TypeId type;
    size_t itemSize;
    GECS_ArrayIndex length;
    void* data;
} GECS_Array;


GECS_Array* GECS_ArrayConstruct(GECS_TypeId type, GECS_ArrayIndex initSize);
void GECS_ArrayResize(GECS_Array* array, GECS_ArrayIndex newLength);
void GECS_ArrayAppend(GECS_Array* array, GECS_GData* data);
void* GECS_ArrayGet(GECS_Array* array, GECS_ArrayIndex index);
void GECS_ArraySet(GECS_Array* array, GECS_ArrayIndex index, GECS_GData* setTo);


#endif //GECS_GECSARRAY_H
