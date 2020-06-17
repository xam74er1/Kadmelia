#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#define SA struct sockaddr
#define LISTENQ 5
#define port 8080
#define Nbuff 255
int main(int argc,char**argv)
{    int retread;
    unsigned char buffer[Nbuff];
    int fd,sockfd,listenfd,connfd;
    pid_t childpid;
    socklen_t client;
    struct sockaddr_in servaddr,cliaddr;
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);


    bind(listenfd,(SA*)&servaddr,sizeof(servaddr));
    listen(listenfd,LISTENQ);


    client=sizeof(cliaddr);
    connfd=accept(listenfd,(SA*)&cliaddr,&client);


    retread=read(connfd,buffer,Nbuff);

    printf("nb bit read : %d\n",retread);

/*
    FILE *write_ptr;

    write_ptr = fopen("serveur.txt","wb");  // w for write, b for binary
    if (write_ptr == NULL) {
        printf("Error \n");
    }else{
        printf("ok \n");
    }

    while ( (retread=read(connfd,buffer,Nbuff)) > 0){
       //  fprintf(fp,"%d",97);
        printf("%c-\n",buffer[0]);
        char * str = "ntm";
//
        fwrite(buffer,Nbuff,1,write_ptr); // write 10 bytes from our buffer
     // printf("nbw %d \n",nbW);
    }
    printf("the file was received successfully \n");
    printf("the new file created is add1.txt \n");

    close( write_ptr);
*/

}
