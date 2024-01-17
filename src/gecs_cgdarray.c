//
// Created by Erik Stacey on 2023-12-29.
//
#include <stdlib.h>
#include "gecs_cgdarray.h"

void GECS_CGDArrayInit(GECS_CGDArray* a, GECS_ComponentDefinition* type, GECS_EntityId initSize) {
    GECS_CheckInput(a, "CGDArrayInit", "CGDArray");
    GECS_CheckInput(type, "GCDArrayInit", "type");
    a->type = type;
    a->d = malloc((type->size) * initSize);
    GECS_CheckAlloc(a->d, "CGDArrayInit", "Allocated data array");
}

void GECS_CGDArrayResize(GECS_CGDArray* a, GECS_EntityId newSize) {
    a->d = realloc(a->d, (a->type->size * newSize));
    // Prints an error message and closes the program if the reallocation failed.
    if (newSize != 0) {
        GECS_CheckAlloc(a->d, "CGDArrayRealloc", "newBlock");
    }
}

void* GECS_CGDArrayGetPtrToElement(GECS_CGDArray* a, GECS_EntityId idx) {
    // Char ptrs increment by 1 byte when you add 1
    // Use this to increment pointer by explicit number of bytes
    char* charPtr = (char*) a;
    a += (a->type->size) * idx;
    return (void*) a;

}

void GECS_CGDArrayClose(GECS_CGDArray* a) {
    free(a->d);
    a->d = NULL;
    a->type = NULL;
}