#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>



/* Transforms string into an argv-style vector of strings */
void parse (char *buf, char *args[]) {
  int i;

  for (i = 0; buf[i]!='\0'; i++) {
    if (buf[i] == '\n')
      buf[i] = '\0';
  } //chop off trailing '\n'

    while (*buf != 0) {
        while (*buf == ' ' || *buf == '\t')
             *buf++ = '\0';
        *args++ = buf;
        while (*buf != '\0' && *buf != ' ' && *buf != '\t')
            buf++;
    }
    *args = 0;
}


/* Fork, exec, and (maybe) wait */
int execute (char *args[], int wait) {
  int status;
  int pid = fork();
    switch (pid) {
    case -1: 
      printf("fork failed!\n");
      return -1;                
    case 0: /* child */
/*       printf("child: fork OK\n"); */
/*       printf("launching \"%s\"",args[0]); */
      if (execvp (args[0], args) == -1) {
        perror("execvp failed");
      }
      _exit (1);
    default: /* parent */
/*       printf("parent: fork OK\n"); */
      if (wait) {
        int status;
        return waitpid(-1, &status, 0);
      }
    }
    return 0;
}


#define BUFSIZE 1024

int main (int argc, char *argv[]) {

  char prompt[] = "command: ";
  int wait = 1;
  if (argc >= 2 && *argv[1] == 'b') 
    wait = 0;

    for (;;) {
        char buf[BUFSIZE];
        char *args[64];
        fputs(prompt, stdout);
        if (fgets(buf, sizeof (buf), stdin) == 0) 
            exit (0);
        parse(buf, args);
        if (execute(args, wait) < 0)
            perror(argv[0]);
    }
}
