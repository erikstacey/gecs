//
// Created by Erik on 2023-12-13. Here you will find all of the basic type definitions for GECS.
// This does not include the definitions of e.g. data structures, just basic aliases and that which is necessary for
// the user to define their own types.
// GECS must be made aware of the data structures that the user intends to use as components. To do so, the user must
// call GECS_AddTypeDefinition to register a data type. Then, it is added to the array of data types GECS_DEFINEDTYPES
// and GECS uses this data to track information about data stored under void* pointers (most importantly, the data size)


#ifndef GECS_GECS_TYPEDEFS_H
#define GECS_GECS_TYPEDEFS_H
#include <stdio.h>
#include <stdint.h>

// This sets the maximum number of data types that can be stored and used with GECS. This increases the memory footprint
// of the library. Particularly, the following yields the total memory requirement:
// Memory = GECS_MAX_TYPES * (GECS_MAX_TYPENAME_LENGTH + sizeof(void*) + sizeof(size_t))
// The latter two sizeof statements are 4 bytes on 32-bit systems and 8 bytes on 64-bit systems.
// For example, with GECS_MAX_TYPES = 256 and GECS_MAX_TYPENAME_LENGTH = 64, the total minimum memory footprint of
// GECS due to type storage requirements is 20.48 kB.
#define GECS_MAX_COMPONENTS 64
// The following includes the null terminator, so the number of characters permitted is this minus 1
#define GECS_MAX_COMPONENT_NAME_LENGTH 64

typedef uint32_t GECS_EntityId;
typedef char GECS_TypeId;

typedef struct{
    char name[GECS_MAX_COMPONENT_NAME_LENGTH];
    size_t size;
    void* prototype;
} GECS_ComponentDefinition;





#endif //GECS_GECS_TYPEDEFS_H
