//
// Created by Erik Stacey on 2023-12-29.
//

#include "gecs_errors.h"

void GECS_CheckAlloc(void* p, char* func, char* obj) {
    if (p==NULL) {
        fprintf(stderr, "[GECS] Allocation error in %s for %s!\n", func, obj);
        exit(EXIT_FAILURE);
    }
}

int GECS_CheckRealloc(void* p, char* func, char* obj) {

}

