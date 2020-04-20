//
// Created by xam74 on 13/04/2020.
//

#include <sys/fcntl.h>
#include "kademiliaTest.h"

Node * node;


void ini(Node *fromNode) {

    node = fromNode;
    iniIp();
    iniPort();
    iniID();
}

void iniPort() {
    node->port = 2048;
}

void iniIp() {
    node->ipAddres = 0;
}

int iniID() {

    for (int i = 0; i < IDLENGTH_INT; ++i) {
        node->id[i] = rand();
    }
}

void setNodeId(Node *fromNode,int id[IDLENGTH_INT]){
    for (int i = 0; i < IDLENGTH_INT; ++i) {
        fromNode->id[i] = id[i];
    }
}


//Met une un id simple au node , uttilise pour les test
void setNodeIdSimple(Node *fromNode,int id){
    fromNode->id[0] =id;
    for (int i = 1; i < IDLENGTH_INT; ++i) {
        fromNode->id[i] = 0;
    }
}




void createFifo(Node *fromNode) {


    struct stat st = {0};

    if (stat(DIRECTORYTEST, &st) == -1) {
        mkdir(DIRECTORYTEST, 0700);
    }


    char * fifoName=getPipeFromId(fromNode->id);
    printf("createFifo : %s \n",fifoName);
    if(mkfifo(fifoName, 0644)!=0){
        printf("impossible de cree la fifo");
    }else{
        printf("fifo cree");
    }

}



char *getPipeFromId(int *id) {

    char buf[64];
    snprintf(buf,sizeof(buf),"/%x",id[0]);
    char * folderName =  concat(DIRECTORYTEST, buf);

    char * tmp;
    for (int i = 1; i < IDLENGTH_INT; i++) {
        snprintf(buf,sizeof(buf),"-%x",id[i]);
        tmp =  concat(folderName,buf);
        free(folderName);
        folderName = tmp;

    }
    char * retour = malloc(255*sizeof(char));
    strcpy(retour,folderName);
    free(folderName);

    return retour;
}


void setTabIndex(Node * node,int index){
    node->tabIndex = index;
}



void send(Node *node, char *str) {
    umask(0);
    char nomTube[] = "nodespace/essai.fifo";

    char * fitoPath = getPipeFromId(node->id);
    printf("write into %s  \n ",fitoPath);

    int pipe ;
    if((pipe = open(fitoPath ,O_RDWR) )== -1){

        printf("impossible de lire \n");
    }else {

        write(pipe, str, strlen(str) + 1);
    }
    //close(pipe);
}

void receive(Node *node) {

    char buf[255];
    char * fitoPath = getPipeFromId(node->id);

    int pipe = open(fitoPath,O_RDONLY | O_NONBLOCK);
    if(pipe!=0) {
        printf("isOpen for %s \n", fitoPath);
        read(pipe, buf, 255);
        close(pipe);


        printf("read : %s \n", buf);
    }
}

