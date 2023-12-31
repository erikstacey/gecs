#ifndef GECS_GECS_H
#define GECS_GECS_H
#include "gecs_typedefs.h"
#include "gecs_componentgroup.h"
#include "gecs_bitset.h"
#include "gecs_entityarray.h"
#include "gecs_cgdarray.h"

typedef struct{
    // Holds type definitions for the components.
    // Each is a GECS_ComponentDefinition object which stores a name, size, and prototype for each component.
    GECS_ComponentDefinition baseComponents[GECS_MAX_COMPONENTS];
    // This is an array of pointers to component groups.
    GECS_ComponentGroup* componentGroups;
    // An array of bitsets that is used in looking up a component group
    // This remains ordered, so a binary search can always find a CG in log(n) time
    GECS_Bitset *componentGroupsMapping;
    // An array of pointers to the CGs
    uint64_t nComponentGroups;
    GECS_EntityArray entities;

} GECS_Instance;

// === INSTANCE MANAGEMENT ===

// Starts up an instance and returns a pointer to the instance
GECS_Instance* GECS_Init();
// Gracefully closes the ECS instance
void GECS_Close(GECS_Instance* i);

// === ECS FUNCTIONALITY

// Adds the specified component to the specified entity
void GECS_AddComponent(GECS_Instance* i, GECS_EntityId entity, GECS_ComponentId component);
// Removes the specified component from the specified entity
void GECS_RemoveComponent(GECS_Instance* i, GECS_EntityId entity, GECS_ComponentId component);

// === ENTITIES MANAGMENT ===

// Adds an entity to the specified ECS instance and returns its id
GECS_EntityId GECS_AddEntity(GECS_Instance* i);
// Deletes an entity from the specified ECS instance
void GECS_FreeEntity(GECS_Instance* i, GECS_EntityId id);

// === COMPONENT MANAGEMENT ===
void GECS_RegisterComponent(GECS_Instance* i, GECS_ComponentId id, char* name, size_t size, void* prototype);

// Retrieves the component group corresponding to the provided bitset, which indices the presence of certain components
GECS_ComponentGroup* GECS_GetComponentGroup(GECS_Instance* i, GECS_Bitset bitset);


#endif //GECS_GECS_H
