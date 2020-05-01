//
// Created by xam74 on 13/04/2020.
//

#include <sys/fcntl.h>
#include "kademiliaTest.h"

Node * node;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */

/*
 * INitilise une node
 */
void ini(Node *fromNode) {

    node = fromNode;
    iniIp();
    iniPort();
    iniID();
    node->nbVoisin=0;
}
//Initle le port
void iniPort() {
    node->port = 2048;
}
//Inisil l'ip
void iniIp() {
    node->ipAddres = 0;
}

//inilise id
int iniID() {

    for (int i = 0; i < IDLENGTH_INT; ++i) {
        node->id[i] = rand();
    }
}

//Set id d'une node
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

//Ajoute un voisin a une node
void addVoisin(Node *original,Node *voisin){
    int pos = original->nbVoisin;
    original->voisin[pos] = voisin;
    original->nbVoisin++;
}
//=====Gestion des pip ====

//Creationde la pipe
void createFifo(Node *fromNode) {


    struct stat st = {0};
//Si le dossie n'exite pas on le cree
    if (stat(DIRECTORYTEST, &st) == -1) {
        mkdir(DIRECTORYTEST, 0700);
    }

//On recupre le nom de la pipe a partir du nom du fichier
    char * fifoName=getPipeFromId(fromNode->id);
    printf("createFifo : %s \n",fifoName);
    //On cre la pipe
    if( access( fifoName, F_OK ) != -1 ) {
        // file exists
        printf("Fifo exite deja ");
    } else {
        // file doesn't exist
        if(mkfifo(fifoName, 0644)!=0){
            printf("impossible de cree la fifo");
        }else{
            printf("fifo cree\n");
        }
    }


}

/*
 * Input : id de la node
 * Out : le chemin ou ce situe la pipe de cette node au format nodespace/id en exa
 * Cela resemble a un forma du tuype "nodespace/f802b07-3bd8dd1d-31d33872-30b23a63-6324665b"
 */

char *getPipeFromId(int *id) {

    char buf[64];
    //On concatene le buffer et id
    snprintf(buf,sizeof(buf),"/%x",id[0]);
    //On concate le nom du dosse a id
    char * folderName =  concat(DIRECTORYTEST, buf);

    char * tmp;
    //On ajoute tout les id a la suite
    for (int i = 1; i < IDLENGTH_INT; i++) {

        snprintf(buf,sizeof(buf),"-%x",id[i]);
        tmp =  concat(folderName,buf);
        //Ne pas ouble de libere lespace pour evite les fuite memoire
        free(folderName);
        folderName = tmp;

    }
    //Allication pour le retoue (si non la valleur est suprime)
    char * retour = malloc(255*sizeof(char));
    strcpy(retour,folderName);
    //libere balkani !!! :p
    free(folderName);
    pthread_mutex_unlock (&mutex); /* On verrouille le mutex */

    return retour;
}

//Worik in Progresse
int findClosedNeibourg(Node * node){
printf("Debut de la rechesse de voisin \n");
    int nbVoisin = 1;
    Node ** tabVoisin = malloc(sizeof(Node *)*255);
    tabVoisin[0] = node->voisin[0];

    int  delta = 1;

    do{

        node->idRessu = 0; //On vas attendre que un therad assyncrone ecrive ici l'id de la node recus , a ce moment le ptr sera diffrent de 0
        askVoisin(node,getPipeFromId(tabVoisin[nbVoisin-1]->id));

        //Tanque l'on a pas recus une reponce on attend
        while(node->idRessu==0){
            sleep(0.1);
        }

        printf("Le voisin le plus proche est : %s \n",getPipeFromId(node->idRessu));

        int * nvx = xordistanceTableau(node->id,node->idRessu,IDLENGTH_INT);
        int * old = xordistanceTableau(node->id,tabVoisin[nbVoisin-1]->id,IDLENGTH_INT);

        delta = GreatOrEqueals(nvx,old,IDLENGTH_INT);

        nbVoisin++;
        Node * tmp = malloc(sizeof(Node));
        ini(tmp);
        setNodeId(tmp,node->idRessu);
        tabVoisin[nbVoisin-1] = tmp;



    }while(delta>0);

    printf("Le voisin final est %s \n",getPipeFromId(tabVoisin[nbVoisin-1]->id));
}


//Envoie a une node un message
void send(Node *node, char *str) {
    umask(0);

//Chemin vers la node
    char * fitoPath = getPipeFromId(node->id);
    printf("write into %s  \n ",fitoPath);

    int pipe ;
    //on ouvre la pipe en mode O_RDWR
    //Mode on ecris et on sens vas meme si il ny a perssone pour lire
    if((pipe = open(fitoPath ,O_RDWR) )== -1){

        printf("impossible de lire \n");
    }else {
//SI la pipe est bien ouvert on ecris dedans
        write(pipe, str, strlen(str) + 1);
    }
    //close(pipe);
}

//endois qui recois les message et les affiche
void receive(Node *node) {

    char buf[255];
    //chemain pour savoir ou on ecoute
    char * fitoPath = getPipeFromId(node->id);

    //Ouverte de la pipe en mode ON list et i ya rien je part
    int pipe = open(fitoPath,O_RDONLY | O_NONBLOCK);
    if(pipe!=0) {
        printf("isOpen for %s \n", fitoPath);
        //lecture
        read(pipe, buf, 255);
        close(pipe);


        printf("read : %s \n", buf);
    }
}

//set a demende un id
void *askId(Node *node,char *dest) {
    umask(0);

    //  char *fitoPath = getPipeFromId(node->id);
    char *fitoPath = dest;
    printf("write into %s  \n ", fitoPath);

    int pipe = -1;
//On ouvre le pipe et on atten que quelun ecoute
    if ((pipe = open(fitoPath, O_WRONLY )) == -1) {

        printf("impossible de decrire \n");
        sleep(1);
    } else {
        //creation du paket sous la forme : ASK_ID monId
        char id=ASK_ID;

        write(pipe, &id  ,1); //On commence par ecrire le type de message que on vas envoyer
        write(pipe,&node->id,sizeof(node->id[0])*IDLENGTH_INT); //on ecris son id pour savoir qui a envoye le msg
        //  write(pipe,&val,sizeof(val));
        printf("endWrite %d \n",pipe);
        //close(pipe);
        sleep(0.1); //on atten un peux (si non sa cause des pbr dans les pipe)
    }


}

//Renvois son id
/*
 * Inpt : la node qui envois son id , dest : lendoris ou elle envois son id (la pipe)
 *
 */
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
        char id=ASK_ID_REP;//On commence par dire que lon repond

        write(pipe, &id  ,1);
        write(pipe,&node->id,sizeof(node->id[0])*IDLENGTH_INT);//on note son id pour la reponce
        //  write(pipe,&val,sizeof(val));
        printf("endWrite %d \n",pipe);
        //close(pipe);
        sleep(0.1);
    }


}

/*
 * Set a demende les voidin d'une node
 * INput : la ode qui demende , dest: lendrois ou la on vas demende (la pipe)
 */
void *askVoisin(Node *node,char *dest) {
    printf("Ask voisin \n");
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
/*
 * Fonction qui est apple dans le recivne
 * Elle sert a recevoir la reponce quand on lui envois ne liste de voisin
 * Elle a pour but de mettre a jour la liste de voisin recus
 * Input : Node : la node qui recois les voin , pipe : id de la pipe ou il faut lire les voisn recus
 */
void reciveVoisin(Node * node , int pipe){


    u_int32_t *tab = malloc(sizeof(u_int32_t)*IDLENGTH_INT);

        read(pipe,tab,sizeof(u_int32_t)*IDLENGTH_INT);
        node->idRessu = tab; //Lorsque lon revois un id on vas le metre dans la node pour le passez a un autre processuce
        printf("Voisin recssu %s \n",getPipeFromId(tab));


}
/*
 * Evois le voin le plus proche au destinataire
 */
void sendVoisin(Node * node,int * idDest){
    umask(0);
    char * dest = getPipeFromId(idDest);
    //  char *fitoPath = getPipeFromId(node->id);
    char *fitoPath = dest;
    printf("write into %s  \n ", fitoPath);

    int pipe = -1;

    if ((pipe = open(fitoPath, O_WRONLY )) == -1) {

        printf("impossible de decrire \n");
        sleep(1);
    } else {
        char type=REP_VOISIN;//on dit que lon envois des voisn

        write(pipe, &type  ,1);//on eris le typ de requette
        Node * proche=   nodeLaPlusProche(node,idDest);

        write(pipe,proche->id,sizeof(u_int32_t)*IDLENGTH_INT);//on ecris chaque voin


        printf("endWrite %d \n",pipe);
        //close(pipe);
        sleep(0.1);//On atten un peux
    }


}
/*Input : la node en question , valleur de comparaison
 * Renvois la node la plus proche de la valleur
 * Cela revien a fair un rechsse de min
 */


Node *nodeLaPlusProche(Node *node, int *valleur) {

    int length = node->nbVoisin;

    if(length>0) {
        int *min = xordistanceTableau(node->voisin[0], valleur, IDLENGTH_INT);
        Node *nodeMin = node->voisin[0];

        for (int i = 1; i < length; i++) {
            int *delta = xordistanceTableau(node->voisin[i], valleur, IDLENGTH_INT);
            //SI la node actelle est plus pete que la node min , elle devien le nvx min
            if (GreatOrEqueals(min, delta, IDLENGTH_INT) > 0) {
                free(min);
                min = delta;
                nodeMin = node->voisin[i];
            }
            free(delta);
        }
    //    free(min);

        return nodeMin;
    }else{
        return node;
    }
}


/*
 * Fonction daisse pour evnoye une string via une pipe
 */
void *testSend(Node *node, char *dest, char *str) {
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
/*
 * /!\ Cette foncton est apple dans un theard dedier
 *
 * Le principe de cette fonction est decoute les demende de ses voisin , elle permet de simulle une demende envoye par le reseau .
 *
 * Cette fonction ecoute a trave une pipe , lorsque quelle recsoin une demende elle revois la bonne reponce a cette node
 */
void *testReceive(Node * node){
    printf("testicive\n");

    char* buf[255];
    char type ;
    u_int32_t id[IDLENGTH_INT];

    char * fitoPath = getPipeFromId(node->id);//chemin sur la quelle je vais ecoute
    printf("avant read \n");
    sleep(1);
    int pipe = open(fitoPath,O_RDONLY ); //ouerture de la pipe
    printf("pipe : %d \n ",pipe);
    if(pipe!=-1) {
        printf("isOpen for %s \n", fitoPath);
        int i = 0;
        while(i<10) { //on ait 10  aissai pour ne pas toune en round pdt les test
            //sleep(1);

            //on list le premier caractre , celui si vas nous permetre de savoir quelle type e messsage on a recus

            read(pipe, buf, sizeof(char));

            printf("type = %d\n",buf[0]);
            type = buf[0];

            //Si le type de message est egalle a ASK id cest que lon nous dmende un id
            if(type==ASK_ID) {
                u_int32_t val = -1;
                read(pipe, id, sizeof(node->id[0] )* IDLENGTH_INT);

                printf(" id : %s \n",getPipeFromId(id));

                //On lui repond

//SI le message est de type ASK voin cest uqe lon nous demende d envoye nos voisn
            }else if(type==ASK_VOISIN){
                //on list qui nous a fait la demende
                read(pipe, id, sizeof(node->id[0] )* IDLENGTH_INT);
                //et on lui repond
                sendVoisin(node,id);

                //Si il est de type REP voisin cest que lon revois la reponce au voisin
            }else if(type==REP_VOISIN){
                //On traite ici la reception de voisin
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