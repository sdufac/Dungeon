#ifndef NPC_H
#define NPC_H
#include "raylib.h"

typedef struct node{
	struct node *next;
	char *line;
}node_t;

typedef struct{
	char *name;
	char *spritePath;
	Texture2D texture;
	Vector3 position;
	Vector2 toScreenPosition;
	node_t *dialogues;
}Npc;

bool isFacingNPC(Npc npc,Vector3 nextPosition);
Npc* npcInitiate();
void dialogueParser(Npc *npc);
void addNode(node_t **head,char *line);

#endif
