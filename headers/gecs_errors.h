//
// Created by Erik Stacey on 2023-12-29.
//

#ifndef GECS_GECS_ERRORS_H
#define GECS_GECS_ERRORS_H
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

// Checks if the pointer is null. If so, prints an error message and exits the program.
void GECS_CheckAlloc(void* p, char* func, char* obj);
int GECS_CheckInput(void* p, char* func, char* arg);

#endif //GECS_GECS_ERRORS_H
