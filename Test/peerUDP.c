/*
 Step 1: start

    Step 2: Read peer one’s IP, Port ID and peer two’s IP and port ID

    Step 3: Create a socket with address family PF_INET type SOCK_DGRAM  and default protocol.

    Step 4: Initialize the socket and set its attribute set required port no.

    Step 5: Connect to server using connect () function to initiate the request.

    Step 6: If command line argument count equal to 4 then send the message to   server.

    Step 7: Receive the string from the server and print it at the console.

    Step 8: stop.
*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

#define MAXBUF		1024
#define MAXIP		16		/* XXX.XXX.XXX.XXX */

char buffer[MAXBUF];

/*--------------------------------------------------------------------*/
/* SetAddress                                                         */
/*                                                                    */
/* Fill Addr with info from XXX.XXX.XXX.XXX:XXXXX format.             */
/*--------------------------------------------------------------------*/
int SetAddress(char* Composite, struct sockaddr_in *Addr)
{	int i;
	char IPAddress[MAXIP];

	bzero(Addr, sizeof(*Addr));
	Addr->sin_family = AF_INET;
	for ( i = 0; Composite[i] != ':'  &&  Composite[i] != 0  &&  i < MAXIP; i++ )
		IPAddress[i] = Composite[i];
	IPAddress[i] = 0;
	if ( Composite[i] == ':' )
		Addr->sin_port = htons(atoi(Composite+i+1));
	else
		Addr->sin_port = 0;
	if ( *IPAddress == 0 )
	{
		Addr->sin_addr.s_addr = INADDR_ANY;
		return 0;
	}
	else
		return ( inet_aton(IPAddress, &Addr->sin_addr) == 0 );
}

/*--------------------------------------------------------------------*/
/* main                                                               */
/*                                                                    */
/* Open socket, connect and receive messages                          */
/*--------------------------------------------------------------------*/
int main(int Count, char *Strings[])
{	int sd;
	struct sockaddr_in addr;

	if ( Count < 3  ||  Count > 4 )
	{
		printf("usage: coupled-peer <my addr:port> <peer addr:port> [<msg>]\n");
		exit(0);
	}
	if ( (sd = socket(PF_INET, SOCK_DGRAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}
	if ( SetAddress(Strings[1], &addr) != 0 )
	{
		perror(Strings[1]);
		exit(errno);
	}
	if ( bind(sd, (struct sockaddr *)&addr, sizeof(addr)) != 0 )
	{
		perror("Bind");
		exit(errno);
	}
	if ( SetAddress(Strings[2], &addr) != 0 )
	{
		perror(Strings[2]);
		exit(errno);
	}
	if ( connect(sd, (struct sockaddr *)&addr, sizeof(addr)) != 0 )
	{
		perror("Connect");
		exit(errno);
	}
	if ( Count == 4 )
		send(sd, Strings[3], strlen(Strings[3]), 0);
	while (1)
	{	int bytes_read;

		bzero(buffer, sizeof(buffer));
		bytes_read = recv(sd, buffer, sizeof(buffer), 0);
		if ( bytes_read > 0 )
		{
			printf("Msg: %s\n", buffer);
			sleep(1);
			send(sd, buffer, bytes_read, 0);
		}
	}
	close(sd);
	return 0;
}
