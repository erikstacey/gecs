//
// Created by Erik Stacey on 2023-12-22.
//

#ifndef GECS_GECS_COMPONENTGROUP_H
#define GECS_GECS_COMPONENTGROUP_H
#include "gecs_typedefs.h"
#include "gecs_cgdarray.h"
#include "gecs_bitset.h"

typedef struct{
    // A parallel array to the main data arrays, storing the corresponding entity ID
    GECS_EntityId* idList;
    // The data arrays holding generic data types.
    GECS_CGDArray* dataArrays;
    // The number of components in the component group e.g. the number of data arrays
    GECS_Bitset componentMask;
    GECS_ComponentId numComponents;

    // Number of populated elements (this is also the index of the first unset element)
    GECS_EntityId dataArraysLen;
    // The last allocated element of the data arrays
    GECS_EntityId dataArraysSize;

} GECS_ComponentGroup;

// Sets up and allocates a new componentgroup with components specified by the componentmask taken in conjunction with
// baseComponents
GECS_ComponentGroup* GECS_ComponentGroupInit(GECS_Bitset* componentMask,
                                             GECS_ComponentDefinition baseComponents[GECS_MAX_COMPONENTS]);
// Resizes the component group (all the data array children and the entity id map) to hold a new number of elements
void GECS_ComponentGroupResize(GECS_ComponentGroup* c, GECS_EntityId newSize);

// Registers an entity in the component group. Does not set any data, but implicitely assigns space for its data
void GECS_ComponentGroupRegisterEntity(GECS_ComponentGroup* cg, GECS_EntityId id);
// Removes an Entity from the component group. Shifts all data so it's contiguous as well.
void GECS_ComponentGroupRemoveEntity(GECS_ComponentGroup* cg, GECS_EntityId id);
// finds and returns the index corresponding to the specified entity
GECS_EntityId GECS_ComponentGroupFindEntity(GECS_ComponentGroup* cg, GECS_EntityId id);
// gets a pointer to the CGD array corresponding to the specified component ID
GECS_CGDArray* GECS_ComponentGroupGetCGDArray(GECS_ComponentGroup* cg, GECS_ComponentId cId);
// returns a pointer to the component data for the specified entity. THE USER IS RESPONSIBLE FOR CASTING THIS
// TO THE CORRECT TYPE.
void* GECS_ComponentGroupGet(GECS_ComponentGroup* cg, GECS_EntityId eId, GECS_ComponentId cId);


// Closes a componentgroup by freeing all its (dynamically allocated) children after instructing them to do the same
// DOES NOT free c, as this must be handled by its parent ECS instance
void GECS_ComponentGroupClose(GECS_ComponentGroup c);

#endif //GECS_GECS_COMPONENTGROUP_H
