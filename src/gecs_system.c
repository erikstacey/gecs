//
// Created by Erik on 2024-02-20.
//
#include "gecs_system.h"

void GECS_SystemInit(GECS_System* system, void (*callEveryFrame)(double deltaT, GECS_ComponentGroup* cg),
                     GECS_Bitset operatesOn, int requireExactMatch) {
    GECS_CheckInput(system, "Init", "system");
    GECS_CheckInput(callEveryFrame, "Init", "System Function");

    system->callEveryFrame = callEveryFrame;
    system->operatesOn = operatesOn;
    system->requireExactMatch = requireExactMatch;

    system->targetsArray = malloc(sizeof(GECS_ComponentGroup*));


}

void GECS_SystemClose(GECS_System* system) {
    free(system->targetsArray);
    system->targetsArray = NULL;
}