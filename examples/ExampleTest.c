#include "gecs.h"

typedef struct{int texID; uint8_t r; uint8_t g; uint8_t b; uint8_t alpha;} TextureData;

int main() {
    GECS_Bitset testBitSet = 0;
    GECS_BitsetFlip(&testBitSet, 0);
    GECS_BitsetFlip(&testBitSet, 1);
    GECS_BitsetFlip(&testBitSet, 63);

    GECS_BitsetSet(&testBitSet, 0, 0);
    GECS_BitsetSet(&testBitSet, 1, 1);
    GECS_BitsetSet(&testBitSet, 2, 1);
    GECS_BitsetSet(&testBitSet, 3, 0);


    GECS_DEBUG_BitsetPrint(&testBitSet);

    GECS_Instance* ecs = GECS_Init();


}