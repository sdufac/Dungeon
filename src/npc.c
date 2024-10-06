#include "npc.h"
#include "raylib.h"

void initializeNpc(Npc npc, Camera *camera){
    npc.texture = LoadTexture(npc.spritePath); 
    npc.toScreenPosition = GetWorldToScreen(npc.position,*camera);
}
