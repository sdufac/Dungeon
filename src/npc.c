#include "npc.h"
#include "stdlib.h"
#include "raylib.h"

bool isFacingNPC(Npc npc,Vector3 nextPosition){
    bool isFacingNpc = false;

    if(npc.position.x == nextPosition.x && npc.position.z == nextPosition.z){
            isFacingNpc = true; 
    }
    return isFacingNpc;
}

Npc* npcInitiate(){
    int numberOfNpc = 1;

    Npc *npcTab = (Npc*)malloc(sizeof(Npc)*numberOfNpc);

    Npc monoko;
    monoko.name = "Monoko";
    monoko.spritePath = "img/Monoko.png";
    monoko.texture = LoadTexture(monoko.spritePath); 
    monoko.position = (Vector3){15,((float)monoko.texture.height)/2/100,20};

    npcTab[0] = monoko;

    return npcTab;
}
