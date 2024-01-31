#include <stdlib.h>
#include "gecs.h"
#include <string.h>

typedef struct{int texID; uint8_t r; uint8_t g; uint8_t b; uint8_t alpha;} TextureData;
typedef struct{float x; float y; float z;} PositionData;
typedef struct{int x;} ExampleComponent;

int main() {

    fprintf(stderr, "STD Err TEST!\n");

    GECS_Bitset testBitset = 0;

    GECS_BitsetSet(&testBitset, 0, 1);
    GECS_BitsetSet(&testBitset, 1, 0);

    GECS_Bitset testBitset2 = 0;

    GECS_BitsetSet(&testBitset2, 0, 1);
    GECS_BitsetSet(&testBitset2, 1, 1);
    GECS_BitsetSet(&testBitset2, 2, 1);

    // Instance test
    GECS_Instance* ecs = GECS_Init();
    GECS_RegisterComponent(ecs, 0, "Texture", sizeof(TextureData), NULL);
    GECS_RegisterComponent(ecs, 1, "Position", sizeof(PositionData), NULL);
    GECS_RegisterComponent(ecs, 2, "TestComponent", sizeof(ExampleComponent), NULL);


    GECS_ComponentGroup* testCG = malloc(sizeof(GECS_ComponentGroup));
    GECS_ComponentGroup* testCG2 = malloc(sizeof(GECS_ComponentGroup));
    GECS_ComponentGroupInit(testCG, &testBitset, ecs->baseComponents);
    GECS_ComponentGroupInit(testCG2, &testBitset2, ecs->baseComponents);


    GECS_ComponentGroupResize(testCG, 10);
    for (int i = 1; i < 6; ++i) {
        GECS_ComponentGroupRegisterEntity(testCG, i);
    }
    GECS_ComponentGroupRemoveEntity(testCG, 3);

    TextureData* testAssign = GECS_ComponentGroupGet(testCG, 2, 0);
    testAssign->alpha = 59;
    printf("Texture component alpha of entity 2: %d \n", testAssign->alpha);

    GECS_ComponentGroupMigrate(testCG, testCG2, 2);

    TextureData* testAssign2 = GECS_ComponentGroupGet(testCG2, 2, 0);
    printf("Texture component alpha of entity 2: %d \n", testAssign2->alpha);

    GECS_ComponentGroupClose(testCG);
    GECS_ComponentGroupClose(testCG2);
    free(testCG);
    free(testCG2);


    GECS_Close(ecs);


}