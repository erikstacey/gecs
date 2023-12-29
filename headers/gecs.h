#ifndef GECS_GECS_H
#define GECS_GECS_H
#include "gecs_typedefs.h"
#include "gecs_gdata.h"
#include "gecs_componentgroup.h"
#include "gecs_bitset.h"
#include "gecs_entityarray.h"

typedef struct{
    GECS_ComponentDefinition baseComponents[GECS_MAX_COMPONENTS];
    // This is an array of pointers to component groups.
    GECS_ComponentGroup** componentGroups;
    // An array of bitsets that is used in looking up a component group
    // This remains ordered, so a binary search can always find a CG in log(n) time
    GECS_Bitset *componentGroupsMapping;
    // An array of pointers to the CGs
    int nComponentGroups;
    GECS_EntityArray entities;

} GECS_Instance;

GECS_Instance* GECS_Init();

GECS_ComponentGroup* GECS_GetComponentGroup(GECS_Instance* i, GECS_Bitset bitset);
// Adds an entity to the specified ECS instance and returns its id
GECS_EntityId GECS_AddEntity(GECS_Instance* i);
// Deletes an entity from the specified ECS instance
void GECS_FreeEntity(GECS_Instance* i, GECS_EntityId id);
// Gracefully closes the ECS instance
void GECS_Close(GECS_Instance* i);



#endif //GECS_GECS_H
