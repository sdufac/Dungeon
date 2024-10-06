#ifndef NPC_H
#define NPC_H
#include "raylib.h"

typedef struct{
	char *name;
	char *spritePath;
	Texture2D texture;
	Vector3 position;
	Vector2 toScreenPosition;
}Npc;

bool isFacingNPC(Npc npc,Vector3 nextPosition);

#endif
