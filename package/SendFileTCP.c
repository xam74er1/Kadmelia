//
// Created by bng on 12/06/2020.
//

#include "SendFileTCP.h"
#include "bdd.h"

void send_tcp_file(Node * from,int sock, char * path){
    printf("Send tcp file\n");
    //int sendto(int socket, char *buffer, int length, int flags,struct sockaddr *address, int address_len);
    //ssize_t send(int s, const void *buf, size_t len, int flags);
    char buff[Nmax];
    size_t bytesRead = 0;
    FILE *f=NULL;
    f=fopen(path,"r");

    if (f != NULL) {
        while ((bytesRead = fread(buff, 1, Nmax, f)) > 0) {
            write(sock, buff, bytesRead);
        }
    }
    close(sock);
}
//int accept(int sockfd, struct sockaddr *adresse, socklen_t *longueur);
void write_file(Node *from, int sock, char *path){
    printf("\nwrite file\n");
    char buff[Nmax];
    size_t bytesRead = 0;
    FILE *fp=NULL;
    fp=fopen(path,"wb");
    int retread;
    int count = 0;


    char * str = "ntm";



    while ((retread=read(sock, buff, Nmax)) > 0){
        printf("%d data recus \n",retread);

        int lentght = strlen(str)+1;

      int nbw =  fwrite(buff,retread,1,fp);


      printf("nbw %d\n",nbw);
        count++;
    }
    printf("the file was received successfully \n");
    printf("the new file created is add1.txt \n");
    fclose(fp);
close(sock);



    if(count!=0){
        printf("Fichier recus ");

    }else{
        printf("Aucun fichier recus ");
    }


}

void accecpt_to_send_file(Node * from){
    printf("accpt send file\n");
    struct sockaddr_in cli;
    int length = sizeof(from->addr_ip);
    //on accepte la conncetion
    int confd=accept(from->sock_tcp,(SA*)&cli,&length);
    int retread;

 char * buff[255];

    if(confd==-1){
        perror("Erreur lors de la connextion B... \n");
     //   exit(1);
    }else{
printf("connextion ok \n");

        //on as lire les donne envoyer
        retread=read(confd,buff,255);
        printf("data recus\n");
        //si on a bien lus les donne
        if(retread!=0){
            char * str ;

            strcpy(str,buff);
            char * path = getfilepath(from,buff);
            //on verifie que le chemain existe bien
            if(path!=0){
            send_tcp_file(from,confd,path);
            }else{
                //Si non on ferme la connextion
                close(from->sock_tcp);
            }

        }
    }

}

void requeste_file(Node * from,Node * to,char * fileName){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("requete file\n");
    //on commence par ce connexte au pair qui possede la donne
    int connexion=connect(sockfd,&to->addr_ip,sizeof(to->addr_ip));

    if(connexion==-1){
        perror("Erreur de connexion...");
    }else {
        printf("connection succe requete file \n");

        sleep(1);
        int size = strlen(fileName) + 1;
//Je luis envois le chemin
printf("end sleep\n");


    write(sockfd, fileName, size);



        printf("tcp envoyer\n");
        char *loc = getPipeFromId(from->id);

        char *tmp = concat(loc, "/");

        char *path = concat(tmp, fileName);
        sleep(1);
        write_file(from, sockfd, path);

    }

}

void testTCP(Node * from,Node * to){
    sleep(0.1);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("requete file\n");
    printNode(to);
    //on commence par ce connexte au pair qui possede la donne
    int connexion=connect(sockfd,&to->addr_ip,sizeof(to->addr_ip));

    if(connexion==-1) {
        perror("Erreur de connexion A...");
    }else{
        printf("sucesse\n");
        char * str = "hello world";
        int size = strlen(str)+1;
        printf("beforewrite\n");
        sleep(0.1);
        write(sockfd, str, size);
        printf("ned");
     //   close(sockfd);
    }
}
#define Nbuff 255
void testRecoisTCP(Node * from){
    unsigned char buffer[Nbuff];
    int retread;
    struct sockaddr_in servaddr,cliaddr;
    int client,connfd;
    client=sizeof(cliaddr);
    connfd=accept(from->sock_tcp,(SA*)&cliaddr,&client);
    retread=read(connfd,buffer,Nbuff);
    printf("nb bit read : %d\n",retread);
}