#include "node.h"


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
    node->nbVoisin=0;
    iniID(node);
    iniAddr(node);
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
    int pos = original->nbVoisin;
    original->voisin[pos] = voisin;
    original->nbVoisin++;
}

void iniAddr(Node * node){

    // Creating socket file descriptor
    if ( (node->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&node->addr_ip, 0, sizeof(node->addr_ip));
    node->addr_ip.sin_family    = AF_INET; // IPv4
    node->addr_ip.sin_addr.s_addr = htonl (INADDR_ANY);
     node->addr_ip.sin_port = htons(portNum); //On le set a 0 pour lui dire de prendre un port par defaut pour la communication
     portNum++;
}

void * addNodeToBukket(Node * from,Node * toAdd){
    Bucket * bucket = find_Bucket(from,toAdd);
    add_node_to_bukket(toAdd,bucket);
}