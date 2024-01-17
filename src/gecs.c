#include "gecs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GECS_Instance* GECS_Init() {
    // initialize the ecs
    GECS_Instance* gecsInstance = malloc(sizeof(GECS_Instance));
    // set up the entity management system
    GECS_EntityArray* e = &(gecsInstance->entities);
    GECS_EntityArrayInit(e);
    // misc
    gecsInstance->definedComponentsLen = 0;
    return gecsInstance;
}

void GECS_Close(GECS_Instance* i) {
    // %todo: finish writing the destructor for the ECS
    GECS_EntityArrayClose(&(i->entities));
    for (int k = 0; k < i->nComponentGroups; k++) {

    }
    free(i);
}

int GECS_CheckComponentMgmtArgs(GECS_Instance* i, GECS_EntityId entity, GECS_ComponentId component) {
    if (!GECS_CheckInput(i, "AddComponent", "ECS Instance")) {
        return 0;
    }
    else if (i->entities.entityComponentsLen > entity) {
        fprintf(stderr, "[GECS] Error: Cannot add component %d to entity %d - entity doesn't exist!\n", component, entity);
        return 0;
    }
    else if (component >= i->definedComponentsLen) {
        fprintf(stderr, "[GECS] Error: Cannot add component %d to entity %d - Component not defined!\n", component, entity);
        return 0;
    }
    else {
        return 1;
    }
}

void GECS_AddComponent(GECS_Instance* i, GECS_EntityId entity, GECS_ComponentId component) {
    if (!GECS_HasComponent(i, entity, component)) {
        // set the bitflag
        GECS_BitsetSet(&(i->entities.entityComponents[entity]), component, 1);
        // Find component group if it exists
        GECS_ComponentGroup* addTo = GECS_GetComponentGroup(i, i->entities.entityComponents[entity]);
        if (addTo == NULL) {
            // We need to make the component group first
        }

    }
}

int GECS_HasComponent(GECS_Instance* i, GECS_EntityId entity, GECS_ComponentId component) {
    if (GECS_CheckComponentMgmtArgs(i, entity, component)) {
        return GECS_BitsetCheck(&(i->entities.entityComponents[entity]), component);
    }
    else {
        return 0;
    }
}

void GECS_RemoveComponent(GECS_Instance* i, GECS_EntityId entity, GECS_ComponentId component) {

}

GECS_EntityId GECS_AddEntity(GECS_Instance* i) {
    if (i == NULL) {
        fprintf(stderr, "[GECS] Error: Attempted to add entity to NULL ecs instance!");
        return 0;
    }
    else {
        return GECS_EntityArrayAddEntity(&(i->entities));
    }
}

void GECS_FreeEntity(GECS_Instance* i, GECS_EntityId id) {
    if (i == NULL) {
        fprintf(stderr, "[GECS] Error: Attempted to remove entity from NULL ecs instance!");
    }
    else {
        GECS_EntityArrayFreeEntity(&(i->entities), id);
    }
}



void GECS_RegisterComponent(GECS_Instance* i, GECS_ComponentId id, char* name, size_t size, void* prototype) {
    if (id > GECS_MAX_COMPONENTS - 1) {
        fprintf(stderr, "[GECS] Error: Cannot register entity with id > %d!", GECS_MAX_COMPONENTS);
    }
    else if (strlen(name) > GECS_MAX_COMPONENT_NAME_LENGTH) {
        fprintf(stderr, "[GECS] Error: Cannot register entity with name of length > %d!", GECS_MAX_COMPONENT_NAME_LENGTH);
    }
    else {
        // Set the base component
        strcpy(i->baseComponents[id].name, name);
        i->baseComponents[id].size = size;
        i->baseComponents[id].prototype=prototype;
        i->definedComponentsLen++;
    }
}

uint64_t GECS_GetComponentGroupIndex(const GECS_Bitset* arr, uint64_t left, uint64_t right, GECS_Bitset target) {
    while (left <= right) {
        uint64_t mid = left + (right - left) / 2;

        // Check if the target is at the middle
        if (arr[mid] == target)
            return mid;

        // If target is greater, ignore left half
        if (arr[mid] < target)
            left = mid + 1;
            // If target is smaller, ignore right half
        else
            right = mid - 1;
    }

    // Target not present in the array
    return right+1;
}

GECS_ComponentGroup* GECS_GetComponentGroup(GECS_Instance* i, GECS_Bitset bitset) {
    if (!GECS_CheckInput(i, "GetComponentGroup", "ECS Instance i")) {
        return NULL;
    }
    // check if we're about to overflow. Close the program if we are. The price of using unsigned integers to store
    // twice as many component groups is we don't actually get to use the last one.
    else if (i->nComponentGroups + 1 == 0) {
        fprintf(stderr, "[GECS] Error: Integer overflow in ComponentGroup index!");
        exit(1);
    }
    else {
        uint64_t cgIdx = GECS_GetComponentGroupIndex(i->componentGroupsMapping, 0, i->nComponentGroups, bitset);
        if (cgIdx == i->nComponentGroups + 1) {
            return NULL;
        }
        else {
            return i->componentGroups+cgIdx;
        }
    }

}

GECS_ComponentGroup* GECS_CreateAndAddComponentGroup(GECS_Instance, GECS_Bitset bitset) {

}