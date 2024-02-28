//
// Created by Erik on 2024-02-20.
//

#ifndef GECS_GECS_SYSTEM_H
#define GECS_GECS_SYSTEM_H

#include "gecs_componentgroup.h"
#include "gecs_bitset.h"

typedef struct{
    // Function which is called on every update cycle
    // Takes a double argument deltaT which represents the time since last frame in seconds
    //
    void (*callEveryFrame)(double deltaT, GECS_ComponentGroup* cg);
    // Defines the components that this system operates on (same way as ComponentGroup, as a bitset)
    GECS_Bitset operatesOn;
    // If this is >=1, then it will only operate on componentgroups which exactly match the GECS Bitset.
    // Otherwise, operates on component groups which contain the specified components (in addition to whatever else
    // they may contain)
    int requireExactMatch;
    GECS_ComponentGroup* targetsArray;

} GECS_System;

// Constructor
void GECS_SystemInit(GECS_System* system, void (*callEveryFrame)(double deltaT, GECS_ComponentGroup* cg), GECS_Bitset operatesOn, int requireExactMatch);
// Destructor
void GECS_SystemClose(GECS_System* system);


#endif //GECS_GECS_SYSTEM_H
