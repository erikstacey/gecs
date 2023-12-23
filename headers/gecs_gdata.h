//
// Created by Erik Stacey on 2023-12-19. The GData (Generic Data) object holds one (1) instance of a data structure.
// This can be a user-defined struct, or a primitive. Regardless, GECS needs to be made aware of the user's intent
// to use the desired data type in GECS containers (see gecs_typedefs.h and GECS_TypeDefinition).
//

#ifndef GECS_GECS_GDATA_H
#define GECS_GECS_GDATA_H

#include "gecs_typedefs.h"


typedef struct{
    GECS_TypeId type;
    void* d;
} GECS_GData;

// The following two functions are a constructor and destructor for the GECS_GData structures.
GECS_GData* GECS_MakeGData(GECS_TypeId type);
void GECS_FreeGData(GECS_GData* gData);


#endif //GECS_GECS_GDATA_H
