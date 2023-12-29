//
// Created by Erik Stacey on 2023-12-27.
//

#ifndef GECS_GECS_ENTITYARRAY_H
#define GECS_GECS_ENTITYARRAY_H
#include "gecs_typedefs.h"
#include "gecs_bitset.h"

typedef struct{
    // dynamic array of bitsets where the index represents the ID and the value represents a bitset of components
    // The first element of this array should always be [000...000], because entityID=0 is used to represent a null
    // value.
    GECS_Bitset* entityComponents;
    // Last populated index in the entityComponents array
    GECS_EntityId entityComponentsLen;
    // Total allocated length of entityComponents array
    GECS_EntityId entityComponentsSize;
    GECS_EntityId* freedIds;
    // Last populated index in the entityComponents array
    GECS_EntityId freedIdsLen;
    // Total allocated length of entityComponents array
    GECS_EntityId freedIdsSize;
    // next ID to assign. This will be the minimum unassigned index in the bitset array.
    GECS_EntityId nextId;
} GECS_EntityArray;
// Given a pointer to an already-allocated entity array, this sets up its initial values.
void GECS_EntityArrayInit(GECS_EntityArray* e);
// Finds and returns a pointer to the component bitset for an entity with the given id
GECS_Bitset* GECS_EntityArrayFindComponents(GECS_EntityArray* entityArray, GECS_EntityId id);
// Adds a new entity to the ecs and returns its ID
GECS_EntityId GECS_EntityArrayAddEntity(GECS_EntityArray* entityArray);
// Destroys an entity with the given id
void GECS_EntityArrayFreeEntity(GECS_EntityArray* entityArray, GECS_EntityId id);

void GECS_EntityArrayClose(GECS_EntityArray* entityArray);

#endif //GECS_GECS_ENTITYARRAY_H
