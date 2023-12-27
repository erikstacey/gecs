//
// Created by Erik Stacey on 2023-12-27.
//

#ifndef GECS_GECS_ENTITYARRAY_H
#define GECS_GECS_ENTITYARRAY_H
#include "gecs_typedefs.h"
#include "gecs_bitset.h"

typedef struct{
    // dynamic array of bitsets where the index represents the ID and the value represents a bitset of components
    GECS_Bitset* entityComponents;
    // array of IDs that have been deleted (thus, they may be recycled)
    GECS_EntityId* freedIds;
    // next ID to assign. This will be the minimum unassigned index in the bitset array.
    GECS_EntityId nextId;
    // Total space in bitset array
    GECS_EntityId len;
    // total active entities
    GECS_EntityId numEntities;
} GECS_EntityArray;
// Finds and returns a pointer to the component bitset for an entity with the given id
GECS_Bitset* GECS_EntityArrayFindComponents(GECS_EntityArray* entityArray, GECS_EntityId id);
// Adds a new entity to the ecs and returns its ID
GECS_EntityId GECS_EntityArrayAddEntity(GECS_EntityArray* entityArray);
// Destroys an entity with the given id
void GECS_EntityArrayFreeEntity(GECS_EntityArray* entityArray, GECS_EntityId);

#endif //GECS_GECS_ENTITYARRAY_H
