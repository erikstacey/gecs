//
// Created by Erik Stacey on 2023-12-22.
//
#include <stdlib.h>
#include "gecs_componentgroup.h"

GECS_ComponentGroup* GECS_ComponentGroupInit(GECS_Bitset* componentMask,
                                             GECS_ComponentDefinition baseComponents[GECS_MAX_COMPONENTS]) {
    GECS_ComponentGroup* newCG = malloc(sizeof(GECS_ComponentGroup));
    GECS_CheckAlloc(newCG, "ComponentGroupInit", "Allocated Component Group");

    // track the number of components
    int numComponents = 0;
    // allocate the data arrays
    newCG->dataArrays = malloc(sizeof(GECS_CGDArray*)*(GECS_BitsetSum(componentMask)));
    // Iterate over the complete bitset to collect all the components
    for (int i = 0; i < 64; i++) {
        if (GECS_BitsetCheck(componentMask, i)) {
            GECS_CGDArray* newArray = GECS_CGDArrayInit(&(baseComponents[i]), 1);
            newCG->dataArrays[numComponents] = *newArray;
            numComponents++;
        }
    }
    // set the number of components
    newCG->numComponents = numComponents;
    newCG->idList = malloc(sizeof(GECS_EntityId));
    GECS_CheckAlloc(newCG->idList, "ComponentGroupInit", "idList");

    newCG->dataArraysLen = 0;
    newCG->dataArraysSize = 1;

    return newCG;
}

void GECS_ComponentGroupResize(GECS_ComponentGroup* c, GECS_EntityId newSize) {
    // resize all data arrays
    for (int i = 0; i < c->numComponents; ++i) {
        GECS_CGDArrayResize(c->dataArrays + i, newSize);
    }
    GECS_EntityId* newIdList = realloc(c->idList, sizeof(GECS_EntityId) * newSize);
    GECS_CheckAlloc(newIdList, "ComponentGroupResize", "Reallocated ID List");
    c->idList = newIdList;
    c->dataArraysSize = newSize;
}

void GECS_ComponentGroupClose(GECS_ComponentGroup c) {
    // works backwards closing each data array and freeing them
    // when it gets to the first element, it frees the entire
    for (int i = 0; i < c.numComponents; ++i) {
        GECS_CGDArrayClose(c.dataArrays+i);
    }
    free(c.idList);
    c.idList = NULL;
    free(c.dataArrays);
    c.dataArrays = NULL;
}