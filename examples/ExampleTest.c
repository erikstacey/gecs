#include "gecs.h"

typedef struct{int texID; uint8_t r; uint8_t g; uint8_t b; uint8_t alpha;} TextureData;

int main() {

    TextureData* sampleTextureData = malloc(sizeof(TextureData));
    sampleTextureData->texID = 0; sampleTextureData->r = 255; sampleTextureData->g = 255; sampleTextureData->b = 255;
    sampleTextureData->alpha = 255;

    GECS_AddTypeDefinition("Texture Data", sizeof(TextureData), sampleTextureData);

    GECS_GData* testGData = GECS_MakeGData(0);
    GECS_Array* testArray = GECS_ArrayConstruct(0, 2000);
    GECS_ArrayAppend(testArray, testGData);
    GECS_FreeGData(testGData);


}