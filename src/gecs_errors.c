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

int GECS_CheckInput(void* p, char* func, char* arg) {
    if (p == NULL) {
        fprintf(stderr, "[GECS]  Null argument in %s: %s!\n", func, arg);
        return 0;
    }
    else {
        return 1;
    }
}

