#include "npc.h"
#include "stdlib.h"
#include "raylib.h"
#include "stdio.h"
#include "string.h"
#include <stddef.h>
#include <string.h>

bool isFacingNPC(Npc npc,Vector3 nextPosition){
    bool isFacingNpc = false;

    if(npc.position.x == nextPosition.x && npc.position.z == nextPosition.z){
            isFacingNpc = true; 
    }
    return isFacingNpc;
}

Npc* npcInitiate(){
    int numberOfNpc = 2;

    //Npc init
    Npc *npcTab = (Npc*)malloc(sizeof(Npc)*numberOfNpc);

    Npc monoko;

    monoko.name = "Monoko";
    monoko.spritePath = "img/Monoko.png";
    monoko.texture = LoadTexture(monoko.spritePath); 
    monoko.position = (Vector3){15,1.5f,20};
    monoko.dialogues = NULL;
    dialogueParser(&monoko,1);

    npcTab[0] = monoko;

    Npc jelly;

    jelly.name = "Jelly";
    jelly.spritePath = "img/Jelly.png";
    jelly.texture = LoadTexture(jelly.spritePath);
    jelly.position = (Vector3){20,1.5f,10};
    jelly.dialogues = NULL;
    dialogueParser(&jelly,2);

    npcTab[1] = jelly; 

    return npcTab;
}

void dialogueParser(Npc *npc,int index){
	char path[100] = {0};
	strcpy(path,"data/dialogue/");
	strcat(path,npc->name); 

	size_t maxLineSize = 1000;
	char charIndex[10];
	sprintf(charIndex, "%d", index);

	FILE *dialogueFile = fopen(path,"rb");
	if(dialogueFile == NULL){
		perror("Erreur lors de l'ouverture du fichier de dialogue");
		exit(1);
	}

	char* currentLine = malloc(sizeof(char)*200);
	fgets(currentLine,200,dialogueFile);

	while(currentLine[0] != charIndex[0]){
		if(feof(dialogueFile)){
			perror("Erreur, ligne de dialogue introuvable");
			exit(1);
		}

		fgets(currentLine,200,dialogueFile);
	}
	
	bool endOfDialoguePart = false;


	fgets(currentLine,200,dialogueFile);
	while(!endOfDialoguePart){
		if(currentLine[0] != '\t' || currentLine[1] != '['){
			perror("Erreur dans la structure du fichier");
			exit(1);
		}

		char* dialogueLine = malloc(maxLineSize);
		dialogueLine[0] = '\0';

		fgets(currentLine,200,dialogueFile);
		while(currentLine[0] != '\t' || currentLine[1] != ']'){
			strcat(dialogueLine,currentLine);

			fgets(currentLine,200,dialogueFile);
		}

		addNode(&npc->dialogues,dialogueLine);

		fgets(currentLine,200,dialogueFile);
		if(currentLine[0] == ']'){
			endOfDialoguePart = true;
		}
	}
	fclose(dialogueFile);
}

void addNode(node_t **head,char *line){
    node_t *newNode = malloc(sizeof(node_t));
    newNode->line = line;
    newNode->next = NULL;

    if(*head == NULL){
        *head = newNode;
    }else{
        node_t *currentNode = *head;
        while(currentNode->next != NULL){
            currentNode = currentNode -> next;
        }

        currentNode->next = newNode;
    }
}
