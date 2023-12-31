//
// Created by Erik Stacey on 2023-12-26.
//
#include "gecs_bitset.h"
#include <stdio.h>

void GECS_BitsetFlip(GECS_Bitset* b, int i) {
    if (i<0 || i > 63) {
        // do nothing if i is not valid (0<i<63)
        return;
    }
    // xor the bitset with a mask containing a single bit at a position i
    // 1ULL creates a bitset like [0000...001], then bitshift it by i
    *b = *b ^ (1ULL << i);

}

void GECS_BitsetSet(GECS_Bitset* b, int i, int value) {
    if (i<0 || i > 63) {
        // do nothing if i is not valid (0<i<63)
        return;
    }
    else if (value >= 1) {
        *b = *b | (1ULL << i);
    }
    else {
        *b = *b & ~ (1ULL << i);
    }
}

int GECS_BitsetCheck(const GECS_Bitset* b, int i) {
    if (*b & (1ULL << i)) {
        return 1;
    }
    else {
        return 0;
    }
}

int GECS_BitsetSum(const GECS_Bitset* bitset) {
    int count = 0;
    GECS_Bitset b = *bitset;
    while (b) {
        count += b & 1ULL;
        b >>= 1;
    }
    return count;
}

void GECS_DEBUG_BitsetPrint(const GECS_Bitset* b) {
    printf("DEBUG BITSET: ");
    for (int i = 0; i < 64; i++) {
        printf("%i", GECS_BitsetCheck(b, i));
    }
    printf("\n");
}