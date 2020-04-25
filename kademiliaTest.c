//
// Created by xam74 on 13/04/2020.
//

#include <sys/fcntl.h>
#include "kademiliaTest.h"

Node * node;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */

void ini(Node *fromNode) {

    node = fromNode;
    iniIp();
    iniPort();
    iniID();
    node->nbVoisin=0;
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


void addVoisin(Node *original,Node *voisin){
    int pos = original->nbVoisin;
    original->voisin[pos] = voisin;
    original->nbVoisin++;
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
        printf("fifo cree\n");
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
    pthread_mutex_unlock (&mutex); /* On verrouille le mutex */

    return retour;
}


int findClosedNeibourg(){

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

void *askId(Node *node,char *dest) {
    umask(0);

    //  char *fitoPath = getPipeFromId(node->id);
    char *fitoPath = dest;
    printf("write into %s  \n ", fitoPath);

    int pipe = -1;

    if ((pipe = open(fitoPath, O_WRONLY )) == -1) {

        printf("impossible de decrire \n");
        sleep(1);
    } else {
        char id=ASK_ID;
        u_int32_t val = node->id[0];
        write(pipe, &id  ,1);
        write(pipe,&node->id,sizeof(node->id[0])*IDLENGTH_INT);
        //  write(pipe,&val,sizeof(val));
        printf("endWrite %d \n",pipe);
        //close(pipe);
        sleep(0.1);
    }


}


void *sendId(Node *node,char *dest) {
    umask(0);

    //  char *fitoPath = getPipeFromId(node->id);
    char *fitoPath = dest;
    printf("write into %s  \n ", fitoPath);

    int pipe = -1;

    if ((pipe = open(fitoPath, O_WRONLY )) == -1) {

        printf("impossible de decrire \n");
        sleep(1);
    } else {
        char id=ASK_ID_REP;
        u_int32_t val = node->id[0];
        write(pipe, &id  ,1);
        write(pipe,&node->id,sizeof(node->id[0])*IDLENGTH_INT);
        //  write(pipe,&val,sizeof(val));
        printf("endWrite %d \n",pipe);
        //close(pipe);
        sleep(0.1);
    }


}


void *askVoisin(Node *node,char *dest) {
    umask(0);

    //  char *fitoPath = getPipeFromId(node->id);
    char *fitoPath = dest;
    printf("write into %s  \n ", fitoPath);

    int pipe = -1;

    if ((pipe = open(fitoPath, O_WRONLY )) == -1) {

        printf("impossible de decrire \n");
        sleep(1);
    } else {
        char id=ASK_VOISIN;
        u_int32_t val = node->id[0];
        write(pipe, &id  ,1);
        write(pipe,&node->id,sizeof(node->id[0])*IDLENGTH_INT);
        //  write(pipe,&val,sizeof(val));
        printf("endWrite %d \n",pipe);
        //close(pipe);
        sleep(0.1);
    }


}

void reciveVoisin(Node * node , int pipe){
    int length;
    read(pipe,&length,sizeof(int));
    printf("recus %d \n",length);

    u_int32_t tab[IDLENGTH_INT];
    for(int i =0;i<length;i++){
        read(pipe,tab,sizeof(u_int32_t)*IDLENGTH_INT);
        printf("Voisin recssu %s \n",getPipeFromId(tab));
    }

}

void sendVoisin(Node * node,char * dest){
    umask(0);

    //  char *fitoPath = getPipeFromId(node->id);
    char *fitoPath = dest;
    printf("write into %s  \n ", fitoPath);

    int pipe = -1;

    if ((pipe = open(fitoPath, O_WRONLY )) == -1) {

        printf("impossible de decrire \n");
        sleep(1);
    } else {
        char type=REP_VOISIN;
        int length= node->nbVoisin;


        printf("Envois de %d voisin \n",length);
        write(pipe, &type  ,1);
        write(pipe,&node->nbVoisin,sizeof(int));
        for(int i =0;i<length;i++){
            write(pipe,node->voisin[i]->id,sizeof(u_int32_t)*IDLENGTH_INT);
        }

        printf("endWrite %d \n",pipe);
        //close(pipe);
        sleep(0.1);
    }


}

void * testSend(Node *node,char *dest,char *str) {
    umask(0);



    //  char *fitoPath = getPipeFromId(node->id);
    char *fitoPath = dest;
    printf("write into %s  \n ", fitoPath);

    int pipe = -1;

    if ((pipe = open(fitoPath, O_WRONLY )) == -1) {

        printf("impossible de decrire \n");
        sleep(1);
    } else {

        write(pipe, str, strlen(str) + 1);
        printf("endWrite %d \n",pipe);
        //close(pipe);
        sleep(0.1);
    }


}

void *testReceive(Node * node){
    printf("testicive\n");

    char* buf[255];
    char type ;
    u_int32_t id[IDLENGTH_INT];

    char * fitoPath = getPipeFromId(node->id);
    printf("avant read \n");
    sleep(1);
    int pipe = open(fitoPath,O_RDONLY );
    printf("pipe : %d \n ",pipe);
    if(pipe!=-1) {
        printf("isOpen for %s \n", fitoPath);
        int i = 0;
        while(i<10) {
            //sleep(1);
            read(pipe, buf, sizeof(char));

            printf("type = %d\n",buf[0]);
            type = buf[0];

            if(type==ASK_ID) {
                u_int32_t val = -1;
                read(pipe, id, sizeof(node->id[0] )* IDLENGTH_INT);

                printf(" id : %s \n",getPipeFromId(id));

                //On lui repond


            }else if(type==ASK_VOISIN){
                read(pipe, id, sizeof(node->id[0] )* IDLENGTH_INT);
                sendVoisin(node,getPipeFromId(id));
            }else if(type==REP_VOISIN){
                reciveVoisin(node,pipe);
            }else{
                printf("Id inconus \n");
            }


            i++;

        }

        close(pipe);



    }else{
        printf("erreur dans overture de pipe \n");
    }
}