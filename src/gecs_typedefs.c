//
// Created by Erik Stacey on 2023-12-19.
//
#include "gecs_typedefs.h"
#include "string.h"

GECS_TypeId GECS_NUMTYPES = 0;

void GECS_AddTypeDefinition(char name[], size_t size, void* prototype) {
    if (GECS_NUMTYPES <= GECS_MAX_TYPES) {
        if (strlen(name) < GECS_MAX_TYPENAME_LENGTH - 1) {
            // Copy the string and ensure the null terminator
            strncpy(GECS_DEFINEDTYPES[GECS_NUMTYPES].name, name, GECS_MAX_TYPENAME_LENGTH - 1);
            GECS_DEFINEDTYPES[GECS_NUMTYPES].name[GECS_MAX_TYPENAME_LENGTH - 1] = '\0';
            GECS_DEFINEDTYPES[GECS_NUMTYPES].size = size;
            GECS_DEFINEDTYPES[GECS_NUMTYPES].prototype = prototype;
            GECS_NUMTYPES++;
        }
        else {
            fprintf(stderr, "[GECS] Error registering new type: name too long. Maximum name length is %d\n",
                    GECS_MAX_TYPENAME_LENGTH);
            return;
        }
    }
    else {
        fprintf(stderr, "[GECS] Error registering new type: Maximum number of types exceeded. Maximum types: %d\n",
                GECS_MAX_TYPES);
        return;
    }
}