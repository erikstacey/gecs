//
// Created by Erik Stacey on 2023-12-27.
//
#include <stdlib.h>
#include "gecs_entityarray.h"

GECS_Bitset* GECS_EntityArrayFindComponents(GECS_EntityArray* entityArray, GECS_EntityId id) {
    if (entityArray == NULL) {
        fprintf(stderr, "[GECS] Error: tried to find entity's components from null array!");
        return NULL;
    }
    else if (entityArray->len < id - 1) {
        fprintf(stderr, "[GECS] Error: tried to find components for invalid entity ID");
    }
    else {
        return entityArray->entityComponents+id;
    }
}

GECS_EntityId GECS_EntityArrayAddEntity(GECS_EntityArray* entityArray) {
    if (entityArray == NULL) {
        fprintf(stderr, "[GECS] Error: tried to add entity to null array! (0 returned)");
        return 0;
    }
    else if (entityArray->entityComponents == NULL) {
        entityArray->entityComponents = malloc(sizeof(GECS_Bitset));
        if (entityArray->entityComponents == NULL) {
            fprintf(stderr, "[GECS] Error: Could not allocate entityComponents in entityArray!");
        }
        entityArray->len = 1;
        entityArray->nextId ++;
        // initialize the value ([000...000])
        *entityArray->entityComponents = 0;
        return 0;
    }
    // Can add another else-if to recycle old ids here later
    // case where the array is out of space
    //
    else if (entityArray->len < entityArray->nextId + 1) {
        // new allocation is (size+10) * 1.2, cast back to an integer type
        GECS_EntityId newLen = (entityArray->len + 10) * 1.2;
        GECS_Bitset* newBlock = realloc(entityArray->entityComponents,
                                                sizeof(GECS_Bitset)*newLen);
        if (newBlock == NULL) {
            free(newBlock);
            fprintf(stderr, "[GECS] Error: Reallocation failed when adding an entity!");
            return 0;
        }
        else {
            entityArray->entityComponents = newBlock;
            entityArray->len = newLen;
        }
    }
    // Space in the array should now be guaranteed (if the allocation/reallocation was successful)
    // so a new entity can be added
    entityArray->entityComponents[entityArray->nextId] = 0;
    entityArray->nextId++;
    return entityArray->nextId - 1;
}