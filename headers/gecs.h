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
    u_int8_t definedComponentsLen;
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
// Checks the arguments for the component management functions. This is a shared requirement across other functions
// which deal with the management of components belonging to entities. Returns 1 if all are good, else returns 0.
int GECS_CheckComponentMgmtArgs(GECS_Instance* i, GECS_EntityId entity, GECS_ComponentId component);
// Adds the specified component to the specified entity
void GECS_AddComponent(GECS_Instance* i, GECS_EntityId entity, GECS_ComponentId component);
// Checks to see if an entity has a component. Returns 1 if it does, 0 otherwise.
int GECS_HasComponent(GECS_Instance* i, GECS_EntityId entity, GECS_ComponentId component);
// Removes the specified component from the specified entity
void GECS_RemoveComponent(GECS_Instance* i, GECS_EntityId entity, GECS_ComponentId component);

// === ENTITIES MANAGMENT ===

// Adds an entity to the specified ECS instance and returns its id
GECS_EntityId GECS_AddEntity(GECS_Instance* i);
// Deletes an entity from the specified ECS instance
void GECS_FreeEntity(GECS_Instance* i, GECS_EntityId id);

// === COMPONENT MANAGEMENT ===
void GECS_RegisterComponent(GECS_Instance* i, GECS_ComponentId id, char* name, size_t size, void* prototype);

// Creates a new component group based on the bitset
GECS_ComponentGroup* GECS_CreateAndAddComponentGroup(GECS_Instance, GECS_Bitset bitset);
// Retrieves the component group corresponding to the provided bitset, which indices the presence of certain components
GECS_ComponentGroup* GECS_GetComponentGroup(GECS_Instance* i, GECS_Bitset bitset);


#endif //GECS_GECS_H
