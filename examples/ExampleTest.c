#include <stdlib.h>
#include "gecs.h"
#include <string.h>

typedef struct{int texID; uint8_t r; uint8_t g; uint8_t b; uint8_t alpha;} TextureData;
typedef struct{float x; float y; float z;} PositionData;

int main() {
    fprintf(stderr, "STD Err TEST!\n");
    // Bitset
    GECS_Bitset testBitset = 1;
    GECS_DEBUG_BitsetPrint(&testBitset);
    printf("Num bits: %d\n", GECS_BitsetSum(&testBitset));
    testBitset++;
    GECS_DEBUG_BitsetPrint(&testBitset);
    printf("Num bits: %d\n", GECS_BitsetSum(&testBitset));
    testBitset++;
    GECS_DEBUG_BitsetPrint(&testBitset);
    printf("Num bits: %d\n", GECS_BitsetSum(&testBitset));
    testBitset = 0;
    testBitset-=1;
    GECS_DEBUG_BitsetPrint(&testBitset);
    printf("Num bits: %d\n", GECS_BitsetSum(&testBitset));

    testBitset = 0;

    GECS_BitsetSet(&testBitset, 0, 1);
    GECS_BitsetSet(&testBitset, 1, 1);





    // Instance test
    GECS_Instance* ecs = GECS_Init();
    GECS_RegisterComponent(ecs, 0, "Texture", sizeof(TextureData), NULL);
    GECS_RegisterComponent(ecs, 1, "Position", sizeof(PositionData), NULL);


    GECS_ComponentGroup* testCG = GECS_ComponentGroupInit(&testBitset, ecs->baseComponents);
    GECS_ComponentGroupResize(testCG, 10);
    for (int i = 1; i < 6; ++i) {
        GECS_ComponentGroupRegisterEntity(testCG, i);
    }
    GECS_ComponentGroupRemoveEntity(testCG, 3);

    GECS_ComponentGroupClose(*testCG);
    free(testCG);


    GECS_Close(ecs);


}