/*
 * Course: CS 100 Fall 2013
 *
 * First Name: <Kevin>
 * Last Name: <Hsieh>
 * Username: <khsie003>
 * email address: <khsie003@ucr.edu>
 *
 *
 * Assignment: <Homework #8>
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */
 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

using namespace std;

// max amount of bytes to get at once
// const int MAXDATASIZE = 300;
// how many pending connections queue will hold
const int BACKLOG = 10;

int main()
{
	// listen on sock_fd, save connection on c_fd
    int sockfd, c_fd;
    // my address information, address that's running this program
    struct sockaddr_in my_addr;
    // client address information
    struct sockaddr_in client_addr;
    int sin_size;

    //SID: 861054367
    long int port = 54367;

  	sockfd = socket(AF_INET, SOCK_STREAM  , 0);  

	if(sockfd == -1)
	{
		cerr << "ERROR: " << errno << "Socket()" << endl;
		exit(1);
	}
	else
		cout << "Socket setup successful." << endl;

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);

    // zero the rest of the struct
    memset(&(my_addr.sin_zero), 0, sizeof(my_addr));

    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
    	cerr << "ERROR: " << errno << " Bind()" << endl;
		exit(1);
    }
    else
    	cout << "Binding successful." << endl;

    if(listen(sockfd, BACKLOG) == -1)
    {
    	cerr << "ERROR: " << errno << " Listen()" << endl;
		exit(1);
    }
    
    sin_size = sizeof(struct sockaddr_in);

    cout << "Blocking untill accept..." << endl;
    c_fd = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *)&sin_size);
	
	if(c_fd == -1)
		cerr << "ERROR: " << errno << "Accept()" << endl;
	else
		cout << "Accept successful" << endl;
	
	// cout << "seg fault here??";
	//setup "ls -l"
	char * arg = new char[BUFSIZ];
	char * cmd0 = new char [5];
	char * cmd1 = new char[5];
	char * cmds[10];
	strcpy(cmd0, "ls");
	strcpy(cmd1, "-l");
	cmds[0] = cmd0;
	cmds[1] = cmd1;
	// cmds[2] = arg;
	cmds[3] = 0;
	//Read from client until
	int read_val = -1;
	int exec_check = -1;
	while(1)
	{
		read_val = read(c_fd, arg, BUFSIZ);
		if(!strcmp(arg,"end"))
			break;
		if(read_val == -1){
			cerr << "ERROR: " << errno << " Read()" << endl;
			break;
		}
		else{
			cout << "\nChecking for directory: " << arg << " ...\n" << endl;
			cmds[2] = arg;
			int pid = fork();
			switch(pid){
				case -1:// error for fork
					cerr << "ERROR: " << errno << " Fork()" << endl;
					break;

				case 0://child process
					// use dup2 to change stdout to Client's stdout				
					dup2(c_fd,1);
					exec_check = execvp(cmds[0],cmds);
					if(exec_check == -1)
						cerr << "ERROR: " << errno << " Execvp()" << endl;
					exit(0);

				default://parent, do nothing
					break;
			}
		}
		//clear arg
		cout << "\nARG:: " << arg << endl;
		strcpy(arg,"");
	}

	//clean up
	delete arg;
	delete cmds[0];
	delete cmds[1];
	close(c_fd);
	close(sockfd);

	cout << "\nShutting down server..." << endl
		 << "Bye Bye~" << endl;
	
	return 0;
}
