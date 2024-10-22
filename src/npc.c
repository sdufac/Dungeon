#include "npc.h"
#include "stdlib.h"
#include "raylib.h"
#include "stdio.h"
#include "string.h"

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
    dialogueParser(&monoko);

    npcTab[0] = monoko;

    Npc jelly;

    jelly.name = "Jelly";
    jelly.spritePath = "img/Jelly.png";
    jelly.texture = LoadTexture(jelly.spritePath);
    jelly.position = (Vector3){20,1.5f,10};
    jelly.dialogues = NULL;
    dialogueParser(&jelly);

    npcTab[1] = jelly; 

    return npcTab;
}
void dialogueParser(Npc *npc){
    char path[100] = {0};

    strcpy(path,"data/dialogue/");
    strcat(path,npc->name); 

    FILE *dialogueFile = fopen(path,"rb");

    if(dialogueFile != NULL){
        while(!feof(dialogueFile)){
            char* currentLine = malloc(sizeof(char)*200);
            char* finalLine = malloc(sizeof(char)*2000);
            *finalLine = 0;

            fgets(currentLine,200,dialogueFile); 

            while(strcmp(currentLine,"//\n")!=0){
                if(feof(dialogueFile)){
                    break;
                }else{
                    strcat(finalLine,currentLine);
                }
                fgets(currentLine,200,dialogueFile); 
            }
            addNode(&npc->dialogues,finalLine);
            free(currentLine);
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
