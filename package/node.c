#include "node.h"
#include "bdd.h"


/*
 * Input : id de la node
 * Out : le chemin ou ce situe la pipe de cette node au format nodespace/id en exa
 * Cela resemble a un forma du tuype "nodespace/f802b07-3bd8dd1d-31d33872-30b23a63-6324665b"
 */
static int portNum = 8080;

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


    return retour;
}


void ini(Node *node) {
iniID(node);
    iniCommun(node);

}

void iniIDSimple(Node * node,int id){
    setNodeIdSimple(node,id);
iniCommun(node);


}

void iniCommun(Node * node){
    for(int i = 0 ;i<NBBUCKET;i++){
        Bucket * b = malloc(sizeof(Bucket));
        b->nbVoisin=0;
        node->listBucket[i] = b;
    }

    iniAddr(node);
    iniFolder(node);
    createDatabase(node);
}

//inilise id
int iniID(Node * node) {

    for (int i = 0; i < IDLENGTH_INT; ++i) {
        node->id[i] = rand();
    }
}

//Set id d'une node
void setNodeId(Node *fromNode, int id[IDLENGTH_INT]){
    for (int i = 0; i < IDLENGTH_INT; ++i) {
        fromNode->id[i] = id[i];
    }
}


//Met une un id simple au node , uttilise pour les test
void setNodeIdSimple(Node *fromNode, int id){
    fromNode->id[0] =id;
    for (int i = 1; i < IDLENGTH_INT; ++i) {
        fromNode->id[i] = 0;
    }
}

//Ajoute un voisin a une node
void addVoisin(Node *original, Node *voisin){
  addNodeToBukket(original,voisin);
}

void iniAddr(Node * node){

    // Creating socket file descriptor
    if ( (node->sock_udp = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    if ( (node->sock_tcp = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }



    memset(&node->addr_ip, 0, sizeof(node->addr_ip));
    node->addr_ip.sin_family    = AF_INET; // IPv4
    node->addr_ip.sin_addr.s_addr = htonl (INADDR_ANY);//Adresse ip
     node->addr_ip.sin_port = htons(portNum); //On le set a 0 pour lui dire de prendre un port par defaut pour la communication
     portNum++;
}

void * addNodeToBukket(Node * from,Node * toAdd){

printf("%s a un nvx voisin %s \n",getPipeFromId(from->id),getPipeFromId(toAdd->id));
    Bucket * bucket = find_Bucket(from,toAdd);
    if(!bucket){
        fprintf(stderr, "Erreur : de bukket pour %s il ne peux pas insere : %s \n",getPipeFromId(from->id),getPipeFromId(toAdd->id));
    }
    add_node_to_bukket(toAdd,bucket);
    //ajout a la base de donne
    setNode(from,toAdd);
}

void * iniFolder(Node * node){
    struct stat st = {0};
    struct stat stB = {0};
//Si le dossie n'exite pas on le cree
    if (stat(DIRECTORYTEST, &st) == -1) {
        mkdir(DIRECTORYTEST, 0700);
    }

    char * folderNode = getPipeFromId(node->id);

    if(stat(folderNode,&stB)==-1){
        mkdir(folderNode, 0700);
    }
}

