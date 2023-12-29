#include "gecs.h"

#include <stdio.h>

GECS_Instance* GECS_Init() {
    // initialize the ecs
    GECS_Instance* gecsInstance = malloc(sizeof(GECS_Instance));
    // set up the entity management system
    GECS_EntityArray* e = &(gecsInstance->entities);
    GECS_EntityArrayInit(e);
    return gecsInstance;
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

void GECS_Close(GECS_Instance* i) {
    // %todo: finish writing the destructor for the ECS
    GECS_EntityArrayClose(&(i->entities));
    for (int k = 0; k < i->nComponentGroups; k++) {

    }

}
