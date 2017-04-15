#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
 

#define MAXDATASIZE 300

/* how many pending connections queue will hold */
#define BACKLOG 10
 
int main(int argc, char *argv[])
{
    /* listen on sock_fd, new connection on new_fd */
    int sockfd, new_fd;
    /* my address information, address where I run this program */
    struct sockaddr_in my_addr;
    /* remote address information */
    struct sockaddr_in their_addr;
    int sin_size;
    int port;


    if(argc != 2)
    {
        fprintf(stderr, "Server-Usage: %s  port\n", argv[0]);
        // just exit
        exit(1);
    }
    
    port = strtol(argv[1], (char **)NULL, 10);
    if(port < 1024)
    {
        fprintf(stderr, "bad port, must be integer >= 1024");
        exit(1);
    }
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
      perror("socket() error!");
      exit(1);
    }
    else
      printf("socket() is OK...\n");
     
    /* host byte order */
    my_addr.sin_family = AF_INET;
    /* short, network byte order */
    my_addr.sin_port = htons(port);
    /* auto-fill with my IP */
    my_addr.sin_addr.s_addr = INADDR_ANY;
     
    /* zero the rest of the struct */
    memset(&(my_addr.sin_zero), 0, 8);
     
    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
      perror("bind() error!");
      exit(1);
    }
    else
      printf("bind() is OK...\n");
     
    if(listen(sockfd, BACKLOG) == -1)
    {
      perror("listen() error!");
      exit(1);
    }
    else
      printf("listen() is OK...\n");
     
    /* ...other codes to read the received data... */
     
    sin_size = sizeof(struct sockaddr_in);
    /*
      int accept(int socket, struct sockaddr *restrict address,
            socklen_t *restrict address_len);
    */
    printf("going to block via accept ()...\n");
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t *)&sin_size);
     
    if(new_fd == -1)
      perror("accept() error!");
    else
      printf("accept() is OK...\n");
     
    char *msg[5] = {
      "This is the server, hello!",
      "Going once",
      "Going twice",
      "Going thrice",
      "This is the server, good bye!"};

    int i;
    for (i=0; i< 5; i++) {

      if(write(new_fd,msg[i], strlen(msg[i])) == -1)
        {
          perror("write() error!");
          exit(1);
        }
      else
        printf("write() is OK...\n");
      sleep(1);
    }


    /*.....other code.......*/
     
    close(new_fd);
    close(sockfd);
    printf("Server exiting.\n");
    return 0;
}
