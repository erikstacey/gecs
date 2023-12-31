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
    GECS_ComponentId numComponents;

    // The last populated element of the data arrays
    GECS_EntityId dataArraysLen;
    // The last allocated element of the data arrays
    GECS_EntityId dataArraysSize;

} GECS_ComponentGroup;

// Sets up and allocates a new componentgroup with components specified by the componentmask taken in conjunction with
// baseComponents
GECS_ComponentGroup* GECS_ComponentGroupInit(GECS_Bitset* componentMask,
                                             GECS_ComponentDefinition baseComponents[GECS_MAX_COMPONENTS]);

void GECS_ComponentGroupResize(GECS_ComponentGroup* c, GECS_EntityId newSize);

// Closes a componentgroup by freeing all its (dynamically allocated) children after instructing them to do the same
// DOES NOT free c, as this must be handled by its parent ECS instance
void GECS_ComponentGroupClose(GECS_ComponentGroup c);

#endif //GECS_GECS_COMPONENTGROUP_H
