//
// Created by root on 6/6/20.
//

#include "publish_key.h"
#include "find_node.h"
#include "send_udp.h"
#include "../utilitaires/hashFile.h"
#include "../utilitaires/fileTabChar.h"
#include "bdd.h"

void * publish_key(Node * from,char * fileName){
//Change le fichier pour quil sois logique
    char * path = fileName;


    int * hashName = hashString(fileName);
    int * hashF = hashFile(path);
    int sizeFie = fileSize(path);

    int nameLength = strlen(fileName)+1;

    //Longteure total a alouer
    //Longeure total a stoque = hashName(160 b)+hashFile(160b)+sizeFile(int)+nbCharInName+name
    int size = IDLENGTH_SIZE*2+sizeof(int)*2+nameLength;

    int total = 0;
    void * data = malloc(size);
//On recopie tout dans la bonne zone memoire
    memcpy(data+total,hashName,IDLENGTH_SIZE);
    total+=IDLENGTH_SIZE;
    memcpy(data+total,hashF,IDLENGTH_SIZE);
    total+=IDLENGTH_SIZE;
    memcpy(data+total,&sizeFie,sizeof(int));
    total+=sizeof(int);
    memcpy(data+total,&nameLength,sizeof(int));
    total+=sizeof(int);
    memcpy(data+total,fileName,nameLength);


    //on trouve la node ou on publie
    struct Node * toPublish = find_node(from,hashName);

    printf("\033[0;33m Node trouve on lui envoie les donne \033[0m \n");

    send_udp(from,toPublish,MSG_PUBLISH_KEY,data,size);

  //  free(data);
}

void * receive_publish_key(Node * from,Node * container,void * buffer){
printf("reveive publish key \n");
    uint32_t * hashName = malloc(IDLENGTH_SIZE);
    uint32_t * hashFile = malloc(IDLENGTH_SIZE);
    int fileSize;
    int nameLength;


    int decalage = sizeof(char)+IDLENGTH_SIZE;
    memcpy(hashName, buffer + decalage, IDLENGTH_SIZE);
    decalage += IDLENGTH_SIZE;
    memcpy(hashFile, buffer + decalage, IDLENGTH_SIZE);
    decalage += IDLENGTH_SIZE;
    memcpy(&fileSize, buffer + decalage, sizeof(int));
    decalage += sizeof(int);
    memcpy(&nameLength, buffer + decalage, sizeof(int));
    decalage += sizeof(int);
//On recupere le nom du fichier
    char * fileName = malloc(sizeof(char)*nameLength);
    memcpy(fileName, buffer + decalage, sizeof(char)*nameLength);
    decalage+=sizeof(char)*nameLength;

    //on enregistre en base de donne
    Fichier * f = malloc(sizeof(Fichier));
    inFichier(f,container,hashName,hashFile,fileSize,fileName);
    SetFile(from,f);
    printf("\033[0;32m clef %s publier avec succe dans %s \033[0m \n ",getPipeFromId(hashName),getPipeFromId(from->id));
}