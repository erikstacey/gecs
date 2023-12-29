#include "gecs.h"

typedef struct{int texID; uint8_t r; uint8_t g; uint8_t b; uint8_t alpha;} TextureData;

int main() {

    GECS_Instance* ecs = GECS_Init();
    GECS_EntityId newEntity = GECS_AddEntity(ecs);

    GECS_Close(ecs);


}