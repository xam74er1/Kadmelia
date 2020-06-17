#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#define SA struct sockaddr
#define port 8080
#define Nbuff 2
int main(int argc,char**argv)
{
    char * name = "serveur.txt";
    printf("Start clinet \n");
    int sockfd;
    char fname[25];
    int len;
    size_t bytesRead = 0;
    struct sockaddr_in servaddr,cliaddr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(1);
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);

    inet_pton(AF_INET,"8080",&servaddr.sin_addr);
    connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
int size = strlen(name)+1;
    write(sockfd,name,size);
    close(sockfd);
    /*
    char buffer[Nbuff];
    FILE *f=NULL;
    f=fopen("client.txt","r");


    if (f != NULL)
    {
        // read up to sizeof(buffer) bytes
        while ((bytesRead = fread(buffer, 1, Nbuff, f)) > 0)
        {
            // process bytesRead worth of data in buffer
            printf("%d\n",buffer[0]);
            write(sockfd, buffer, Nbuff);
        }
    }
    //fscanf(f,"%s",buffer);

    printf("the file was sent successfully \n");
    close(f);

     */
}

