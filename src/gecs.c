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
    return gecsInstance;
}

void GECS_Close(GECS_Instance* i) {
    // %todo: finish writing the destructor for the ECS
    GECS_EntityArrayClose(&(i->entities));
    for (int k = 0; k < i->nComponentGroups; k++) {

    }
    free(i);
}

void GECS_AddComponent(GECS_Instance* i, GECS_EntityId entity, GECS_ComponentId component) {
    // Register that the entity has the component
    // Add the entity to the componentgroup to which it belongs
    // If neccessary, copy over the data from the old componentgroup and remove it
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
    }
}