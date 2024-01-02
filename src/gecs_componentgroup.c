//
// Created by Erik Stacey on 2023-12-22.
//
#include <stdlib.h>
#include "gecs_componentgroup.h"

GECS_ComponentGroup* GECS_ComponentGroupInit(GECS_Bitset* componentMask,
                                             GECS_ComponentDefinition baseComponents[GECS_MAX_COMPONENTS]) {
    GECS_CheckInput(componentMask, "ComponentGroupInit", "componentMask");

    GECS_ComponentGroup* newCG = malloc(sizeof(GECS_ComponentGroup));
    GECS_CheckAlloc(newCG, "ComponentGroupInit", "Allocated Component Group");
    newCG->componentMask = *componentMask;

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
    GECS_CheckInput(c, "ComponentGroupResize", "c");
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
    for (int i = 0; i < c.numComponents; ++i) {
        GECS_CGDArrayClose(c.dataArrays+i);
    }
    free(c.idList);
    c.idList = NULL;
    free(c.dataArrays);
    c.dataArrays = NULL;
}

void GECS_ComponentGroupRegisterEntity(GECS_ComponentGroup* cg, GECS_EntityId id) {
    GECS_CheckInput(cg, "ComponentGroupRegisterEntity", "cg");
    // Check if we must reallocate, do so if necessary
    if (cg->dataArraysLen >= cg->dataArraysSize) {
        GECS_ComponentGroupResize(cg, (cg->dataArraysSize+10)*1.2);
    }
    cg->idList[cg->dataArraysLen] = id;
    cg->dataArraysLen++;

}

GECS_EntityId GECS_ComponentGroupFindEntity(GECS_ComponentGroup* cg, GECS_EntityId id) {
    GECS_CheckInput(cg, "ComponentGroupFindEntity", "cg");
    // basic linear search for now
    // can optimize this later if necessary
    for (GECS_EntityId i= 0; i < cg->dataArraysLen; ++i) {
        if (cg->idList[i] == id) {
            return i;
        }
    }
    // Not ideal, but returns the first unassigned index if we can't find the entity.
    return cg->dataArraysLen;
}

void GECS_ComponentGroupRemoveEntity(GECS_ComponentGroup* cg, GECS_EntityId id) {
    GECS_CheckInput(cg, "ComponentGroupRemoveEntity", "cg");
    GECS_EntityId index = GECS_ComponentGroupFindEntity(cg, id);
    // case where we cannot find entity
    if (index == cg->dataArraysLen) {
        return;
    }
    else {
        // First overwrite the idList
        memmove(cg->idList+index, cg->idList+index+1, sizeof(GECS_EntityId) * (cg->dataArraysLen-index));
        // Perform the same operation on the data arrays
        for (int i = 0; i < cg->numComponents; ++i) {
            memmove(cg->dataArrays[i].d+index, cg->dataArrays[i].d+index+1,
                    cg->dataArrays[i].type->size*(cg->dataArraysLen-index));
            }
    }
}

void* GECS_ComponentGroupGet(GECS_ComponentGroup* cg, GECS_EntityId eId, GECS_ComponentId cId) {
}