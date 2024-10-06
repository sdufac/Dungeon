#ifndef NPC_H
#define NPC_H
#include "raylib.h"

typedef struct{
	char *spritePath;
	Texture2D texture;
	Vector3 position;
	Vector2 toScreenPosition;
}Npc;

void initializeNpc(Npc npc,Camera *camera);

#endif
