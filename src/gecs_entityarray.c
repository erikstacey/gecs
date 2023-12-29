//
// Created by Erik Stacey on 2023-12-27.
//
#include <stdlib.h>
#include "gecs_entityarray.h"


void GECS_EntityArrayInit(GECS_EntityArray* e) {
    e->nextId = 1;
    // Set up entityComponents array and metadata
    e->entityComponents = malloc(sizeof(GECS_Bitset));
    e->entityComponentsLen = 0; e->entityComponentsSize = 0;
    // Set up freedIds array and metadata
    e->freedIdsLen = 0; e->freedIdsSize = 0;
    e->freedIds = malloc(sizeof(GECS_EntityId));
}

GECS_Bitset* GECS_EntityArrayFindComponents(GECS_EntityArray* entityArray, GECS_EntityId id) {
    if (entityArray == NULL) {
        fprintf(stderr, "[GECS] Error: tried to find entity's components from null array!");
        return NULL;
    }
    else if (entityArray->entityComponentsLen < id - 1) {
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
    // Can add another else-if to recycle old ids here later
    // %todo: add entity recycling option with logic here
    // case where the array is out of space
    //
    else if (entityArray->entityComponentsSize < entityArray->nextId + 1) {
        // new allocation is (size+10) * 1.2, cast back to an integer type
        GECS_EntityId newSize = (entityArray->entityComponentsSize + 10) * 1.2;
        GECS_Bitset* newBlock = realloc(entityArray->entityComponents,
                                                sizeof(GECS_Bitset)*newSize);
        if (newBlock == NULL) {
            free(newBlock);
            fprintf(stderr, "[GECS] Error: Reallocation failed when adding an entity!");
            return 0;
        }
        else {
            entityArray->entityComponents = newBlock;
            entityArray->entityComponentsSize = newSize;
        }
    }
    // Space in the array should now be guaranteed (if the allocation/reallocation was successful)
    // so a new entity can be added
    entityArray->entityComponents[entityArray->nextId] = 0;
    entityArray->nextId++;
    return entityArray->nextId - 1;
}

void GECS_EntityArrayFreeEntity(GECS_EntityArray* e, GECS_EntityId id) {
    // The entity array can only free the entity from its own registry. The controlling ECS must also instruct
    // all components to strike the entity from themselves.
    // This is handled in the FreeEntity function which operates on the instance itself.
    if (e == NULL) {
        fprintf(stderr, "[GECS] Error: attempted to free entity from NULL entity array");
    }
    else {
        e->entityComponents[id] = 0;
        // Make sure we can keep track of the freed entity
        // Reallocate the array if we must
        if (e->freedIdsLen == e->freedIdsSize) {
            GECS_EntityId* newBlock = realloc(e->freedIds, sizeof(GECS_EntityId) * e->freedIdsSize+1);
            if (newBlock == NULL) {
                fprintf(stderr, "[GECS] Error: reallocation failed when trying to expand list of unregistered entities."
                                "Entity has NOT been freed.");
                return;
            }
            else {
                e->entityComponents[id]=0;
                e->freedIds[e->freedIdsLen] = id;
                e->freedIdsLen++;
            }
        }
        // Otherwise, we can free the entity and add it to the list.
        e->entityComponents[e->freedIdsLen] = id;
        e->freedIdsLen++;
        e->entityComponents[id]=0;
    }
}

void GECS_EntityArrayClose(GECS_EntityArray* entityArray) {
    free(entityArray->entityComponents);
    entityArray->entityComponents = NULL;
    free(entityArray->freedIds);
    entityArray->freedIds = NULL;
}