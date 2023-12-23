//
// Created by Erik Stacey on 2023-12-19.
//
#include "gecs_gdata.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

GECS_GData* GECS_MakeGData(GECS_TypeId type) {
    GECS_GData* newGData = malloc(sizeof(GECS_GData));
    if (type > GECS_NUMTYPES) {
        fprintf(stderr, "Attempted to allocate GData with undefined type!\n");
    }
    else if (newGData == NULL) {
        fprintf(stderr, "Failed to allocate GData (malloc)!\n");
    }
    else {
        newGData->type = type;
        newGData->d = malloc(GECS_DEFINEDTYPES[type].size);
        if (GECS_DEFINEDTYPES[type].prototype != NULL) {
            memcpy(newGData->d, GECS_DEFINEDTYPES[type].prototype, GECS_DEFINEDTYPES[type].size);
        }
        return newGData;
    }

}

void GECS_FreeGData(GECS_GData* gData) {
    free(gData->d);
    free(gData);
}

