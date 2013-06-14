﻿/**
 * Este aplicacion representa a una entidad crediticia la cual
 * concentra todos los creditos otorgados a los clientes de
 * diferentes entidades.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#include <unistd.h>

#define PORT 3550 /* El puerto que será abierto */
#define BACKLOG 2 /* El número de conexiones permitidas */

void doprocessing (int sock)
{
    int i;
	char x[2] = {'%','%'};
    char buffer[100];
	char rfc[100],*aux,myString[100];
	FILE *file;
	int length;
	

    memset(buffer, 0, sizeof(buffer));
    int recvMsgSize;
    
    /* Receive message from client */
    if ((recvMsgSize = recv(sock, buffer, 256, 0)) < 0)
        perror("ERROR reading to socket");
		
	for(i=0; i< sizeof(buffer); i++)
	{
		rfc[i]=buffer[i]; 
		
	}
		printf("Checkig RFC retrieved:  %s\n",rfc);
	


	file=fopen("C:\\Users\\usuario\\Documents\\GitHub\\GDL\\workshop-gdl\\workshop\\credit-bureau\\src\\c\\Loans.txt","r");
	
	if(file == NULL)
		perror("Error Opening File");

	else{
		while(!feof(file))
	{
		aux=fgets(myString,sizeof(myString),file);//retrieves a line from Loans.txt and reads as string
		length=strlen(myString); //Calculates line length retrieved from Loans.txt
		if(strstr(myString,rfc)) //fetch rfc string into myString string
		{
			puts(aux); //just for test lines retrieved
			send(sock,aux,length,0); // sends line retrieved to socket buffer
			}
			memset(myString,0,sizeof(myString)); //clean up myString string to be ready for retreive a new line
	}
		send(sock,x,sizeof(x),0); // send to socket buffer a char sequence '%%'
		fclose(file);
		}
	

    /* Send received string and receive again until end of transmission */
    while (recvMsgSize > 0)      /* zero indicates end of transmission */
    {
	fflush(stdin);
		if(send(sock,"Si llego",8,0) > 0)
			//printf();
		
        /* Echo message back to client 
        if (send(sock, buffer, recvMsgSize, 0) != recvMsgSize)
            perror("ERROR writing to socket");

	/*int x;
	x=1;
	for(x=1;x<recvMsgSize;x++)
	{
	printf("THe count in \n %d %c", x,buffer[x]);
	}*/

        /* See if there is more data to receive */
        if ((recvMsgSize = recv(sock, buffer, 256, 0)) < 0)
            perror("ERROR reading to socket");
    }

    closesocket(sock);    /* Close client socket */
}

BOOL initW32() 
{
		WSADATA wsaData;
		WORD version;
		int error;
		
		version = MAKEWORD( 2, 0 );
		
		error = WSAStartup( version, &wsaData );
		
		/* check for error */
		if ( error != 0 )
		{
		    /* error occured */
		    return FALSE;
		}
		
		/* check for correct version */
		if ( LOBYTE( wsaData.wVersion ) != 2 ||
		     HIBYTE( wsaData.wVersion ) != 0 )
		{
		    /* incorrect WinSock version */
		    WSACleanup();
		    return FALSE;
		}	
}

int main()
{

	 initW32(); /* Necesaria para compilar en Windows */ 
	 	
   int fd, fd2; /* los descriptores de archivos */
   //char buff[100];

   /* para la información de la dirección del servidor */
   struct sockaddr_in server;

   /* para la información de la dirección del cliente */
   struct sockaddr_in client;

   unsigned int sin_size;

   pid_t pid;

   /* A continuación la llamada a socket() */
   if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
      printf("error en socket()\n");
      exit(-1);
   }

   server.sin_family = AF_INET;

   server.sin_port = htons(PORT);

   server.sin_addr.s_addr = INADDR_ANY;
   /* INADDR_ANY coloca nuestra dirección IP automáticamente */

   //bzero(&(server.sin_zero),8);
   memset(&(server.sin_zero), '0', 8);
   /* escribimos ceros en el reto de la estructura */


   /* A continuación la llamada a bind() */
   if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1) {
      printf("error en bind() \n");
      exit(-1);
   }

   if(listen(fd,BACKLOG) == -1) {  /* llamada a listen() */
      printf("error en listen()\n");
      exit(-1);
   }

   while(1) {
      sin_size=sizeof(struct sockaddr_in);
      /* A continuación la llamada a accept() */
      if ((fd2 = accept(fd,(struct sockaddr *)&client, &sin_size))==-1) {
         printf("error en accept()\n");
         exit(-1);
      }

      printf("Se obtuvo una conexión desde %s\n", inet_ntoa(client.sin_addr) );
      /* que mostrará la IP del cliente */
		
      send(fd2,"Bienvenido a mi servidor.\n",256,0);
      /* que enviará el mensaje de bienvenida al cliente */
      //recv(fd2, buff, 100, 0);
	  //printf("Checiking buff:   %s", buff);
      doprocessing(fd2);

   } /* end while */
}

