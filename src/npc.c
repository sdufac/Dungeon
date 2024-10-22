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
    dialogueParser(monoko);

    //addNode(&monoko.dialogues,"TEST");

    npcTab[0] = monoko;

    Npc jelly;

    jelly.name = "Jelly";
    jelly.spritePath = "img/Jelly.png";
    jelly.texture = LoadTexture(jelly.spritePath);
    jelly.position = (Vector3){20,1.5f,10};
    jelly.dialogues = NULL;
    dialogueParser(jelly);

    //addNode(&jelly.dialogues,"TEST");

    npcTab[1] = jelly; 

    return npcTab;
}
void dialogueParser(Npc npc){
    char* currentLine = malloc(sizeof(char)*200);
    char* finalLine = malloc(sizeof(char)*2000);
    *finalLine = 0;
    char path[100] = {0};

    strcpy(path,"data/dialogue/");
    strcat(path,npc.name); 

    FILE *dialogueFile = fopen(path,"rb");

    if(dialogueFile != NULL){
        fgets(currentLine,200,dialogueFile); 

        while(!feof(dialogueFile)){
            if(strcmp(currentLine,"//\n")==0){
                addNode(&npc.dialogues,finalLine);
                *finalLine = 0;
                fgets(currentLine,200,dialogueFile); 
            }else if(feof(dialogueFile)){
                addNode(&npc.dialogues,finalLine);
                break;
            } 
            else{
                strcat(finalLine,currentLine);
                fgets(currentLine,200,dialogueFile); 
            }
        } 
        fclose(dialogueFile);
        *finalLine = 0;
        *currentLine = 0;
    }
    free(currentLine);
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
