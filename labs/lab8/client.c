#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

// max number of bytes we can get at once
#define MAXDATASIZE 300
 
int main(int argc, char *argv[])
{

    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    // connector's address information
    struct sockaddr_in their_addr;

    // the port client will be connecting to
    int port;
     
    // if no command line argument supplied
    if(argc != 3)
    {
        fprintf(stderr, "Client-Usage: %s the_client_hostname port\n", argv[0]);
        // just exit
        exit(1);
    }

    port = strtol(argv[2], (char **)NULL, 10);
    if(port < 1024)
    {
        fprintf(stderr, "bad port, must be integer >= 1024");
        exit(1);
    }
    

    // get the host info
    if((he=gethostbyname(argv[1])) == NULL)
    {
        perror("gethostbyname()");
        exit(1);
    }
    else
        printf("Client-The remote host is: %s\n", argv[1]);
     
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket()");
        exit(1);
    }
    else
        printf("Client-The socket() sockfd is OK...\n");
     
    // host byte order
    their_addr.sin_family = AF_INET;
    // short, network byte order
    printf("Server-Using %s and port %d...\n", argv[1], port);
    their_addr.sin_port = htons(port);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    // zero the rest of the struct
    memset(&(their_addr.sin_zero), '\0', 8);
     
    if(connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect()");
        exit(1);
    }
    else
        printf("Client-The connect() is OK...\n");

    int i;
    for (i=0; i< 5; i++) {

      numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0);
      if (numbytes == -1)    
        {
          perror("recv()");
          exit(1);
        }
      else {
        printf("Client-The recv() is OK...\n");
        buf[numbytes] = '\0';
        printf("Client-Received %d bytes: %s\n", numbytes, buf);
      }
      sleep(1);
    }
    printf("Client-Closing sockfd\n");
    close(sockfd);
    printf("Client exiting.\n");
    return 0;
}
