//
// Created by Erik Stacey on 2023-12-29.
//
#include <stdlib.h>
#include "gecs_cgdarray.h"

GECS_CGDArray* GECS_CGDArrayInit(GECS_ComponentDefinition* type, GECS_EntityId initSize) {
    GECS_CGDArray* newArray = malloc(sizeof(GECS_CGDArray));
    GECS_CheckAlloc(newArray, "CGDArrayInit", "Allocated Array");
    newArray->type = type;
    newArray->d = malloc((type->size) * initSize);
    GECS_CheckAlloc(newArray->d, "CGDArrayInit", "Allocated data array");
    return newArray;
}

void GECS_CGDArrayResize(GECS_CGDArray* a, GECS_EntityId newSize) {
    a->d = realloc(a->d, (a->type->size * newSize));
    // Prints an error message and closes the program if the reallocation failed.
    if (newSize != 0) {
        GECS_CheckAlloc(a->d, "CGDArrayRealloc", "newBlock");
    }
}

void GECS_CGDArrayClose(GECS_CGDArray* a) {
    free(a->d);
    a->d = NULL;
}