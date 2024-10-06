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
    int numberOfNpc = 2;

    Npc *npcTab = (Npc*)malloc(sizeof(Npc)*numberOfNpc);

    Npc monoko;
    monoko.name = "Monoko";
    monoko.spritePath = "img/Monoko.png";
    monoko.texture = LoadTexture(monoko.spritePath); 
    monoko.position = (Vector3){15,1.5f,20};

    npcTab[0] = monoko;

    Npc jelly;
    jelly.name = "Jelly";
    jelly.spritePath = "img/Jelly.png";
    jelly.texture = LoadTexture(jelly.spritePath);
    jelly.position = (Vector3){20,1.5f,10};

    npcTab[1] = jelly; 
    
    return npcTab;
}
