//
// Created by Erik Stacey on 2023-12-29.
//

#ifndef GECS_GECS_CGDARRAY_H
#define GECS_GECS_CGDARRAY_H
#include "gecs_typedefs.h"
#include "gecs_errors.h"

// The Component Group Data (CGD) array is used in conjunction with the component groups to store the component data
// The parent component group is responsible for managing this object
typedef struct{
    // Pointer to component definition which specifies the type (and therefore size of data)
    GECS_ComponentDefinition* type;
    // Pointer to first element of the data array
    void* d;
} GECS_CGDArray;

// Sets up an CGDArray in place. This is intended to operate on elements of allocated CGDArrays
void GECS_CGDArrayInit(GECS_CGDArray* a, GECS_ComponentDefinition* type, GECS_EntityId initSize);

// resizes the allocated memory for the CGDArray a
void GECS_CGDArrayResize(GECS_CGDArray* a, GECS_EntityId newSize);
// Gets the pointer to a SPECIFIC element. The user is responsible for casting this to the appropriate type.
void* GECS_CGDArrayGetPtrToElement(GECS_CGDArray* a, GECS_EntityId idx);

// Closes the CGDArray. As these are intended to be used in arrays in ComponentGroups, this DOES NOT free a, as
// a should be freed by the parent componentgroup when freeing its array of CGDArrays
void GECS_CGDArrayClose(GECS_CGDArray* a);

#endif //GECS_GECS_CGDARRAY_H
