//
// Created by Erik Stacey on 2023-12-26.
//

#ifndef GECS_GECS_BITSET_H
#define GECS_GECS_BITSET_H
#include <stdint.h>

typedef uint64_t GECS_Bitset;

// flips the bit at position i in the bitset b
void GECS_BitsetFlip(GECS_Bitset* b, int i);
// sets the bit at position i to the given explicit value (value = 0; 0, value >0; 1) in the bitset b
void GECS_BitsetSet(GECS_Bitset* b, int i, int value);
// returns 0 or 1 based on the value of position i in bitset b
int GECS_BitsetCheck(const GECS_Bitset* b, int i);
// Get the number of set bits
int GECS_BitsetSum(const GECS_Bitset* b);
// Get the number of set bits up to a specified bit
int GECS_BitsetCountUpTo(const GECS_Bitset* bitset, int bit);
// Prints the bitset to console
void GECS_DEBUG_BitsetPrint(const GECS_Bitset* b);


#endif //GECS_GECS_BITSET_H
