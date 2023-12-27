#include "gecs.h"

#include <stdio.h>

GECS_Instance* GECS_Init() {
    // initialize the ecs
    GECS_Instance* gecsInstance = malloc(sizeof(GECS_Instance));
    // set up the entity management system
    GECS_EntityArray* e = &(gecsInstance->entities);
    e->nextId = 0; e->len = 1; e->numEntities = 0;
    e->freedIds = NULL;
    e->entityComponents = NULL;
}

GECS_EntityId GECS_AddEntity(GECS_Instance* i) {
    if (i == NULL) {
        fprintf(stderr, "[GECS] Error: Attempted to add entity to NULL ecs instance!");
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
