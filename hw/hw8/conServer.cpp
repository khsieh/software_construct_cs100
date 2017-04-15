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
#include <sys/stat.h>
#include <dirent.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <sys/wait.h> 

using namespace std;

// max amount of bytes to get at once
// const int MAXDATASIZE = 300;
// how many pending connections queue will hold
const int BACKLOG = 10;

const int client_count = 3;

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
    sin_size = sizeof(struct sockaddr_in);

    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
    	cerr << "ERROR: " << errno << " Bind()" << endl;
		exit(1);
    }
    else
    	cout << "Binding successful." << endl;

    //LISTEN
    if(listen(sockfd, BACKLOG) == -1)
    {
    	cerr << "ERROR: " << errno << " Listen()" << endl;
		exit(1);
    }
    
    for(int count = 0; count < client_count; ++count){

	    cout << "Blocking untill accept..." << endl;
	    //ACCEPT
	    c_fd = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *)&sin_size);
		
		if(c_fd == -1)
			cerr << "ERROR: " << errno << "Accept()" << endl;
		else
			cout << "Accept successful" << endl;
		
		//setup Directory name to copy
		char * dirname = new char[BUFSIZ];
		

		int read_val = -1;
		//reads for dirname
		cout << "READING FOR DIRNAME..." << endl;
		read_val = read(c_fd, dirname, BUFSIZ);
		if(read_val == -1){
			cerr << "ERROR: " << errno << " Read()" << endl;
			exit(1);
		}

		cout << "\nChecking for directory: " << dirname << " ...\n" << endl;
		
		struct stat st;
		if(stat(dirname, &st) == 0){
		    if( (st.st_mode & S_IFDIR) == 0){
		    	cerr << "directory does not exist! :C" << endl;
		    	//write to client dir doesn't exist
		    	char no_exist[10];
		    	strcpy(no_exist, "-1");
		    	write(c_fd, no_exist, BUFSIZ);
		    	exit(1);
		    	// continue;
		    }
		    else{
			    //write to client dir exists
			    char exist[10];
			    strcpy(exist,"1");
				write(c_fd, exist, BUFSIZ);
			}
		}

		//fork, child process copys the directory's files to client
		int pid = fork();
		switch(pid){
			case -1:// error for fork
				cerr << "ERROR: " << errno << " Fork()" << endl;
				break;

			case 0:{
				//child process
				//call "mkdir dirname"
				//loop through dirname and copy files
				DIR *dirp;
			    if(!(dirp = opendir(dirname)))
			    {
			        cerr << "ERROR(" << errno << ") opening " << dirname << endl;
			        return errno;
			    }

			    dirent * direntp;
			    while((direntp = readdir(dirp))){
			    	//if d_name is "." or ".." skip
			    	if(direntp -> d_name[0] == '.')
	        			continue;
	        		struct stat file_buf;
	        		if ( stat(dirname, & file_buf) != -1)
			        {
			            if( S_ISREG(file_buf.st_mode) == -1){
			            	cerr << "ERROR: " << errno << " S_ISREG()" << endl;
			            }
			            else{
			            	//write filename to client
			            	sleep(1);
			            	char filename[64];
			            	strcpy(filename,dirname);
			            	strcat(filename, "/");
			            	strcat(filename,direntp -> d_name);
			            	
			            	cout << "FILENAME: " << filename << endl;
			            	sleep(1);

			            	write(c_fd, filename, BUFSIZ);
			            	int file_fd = open(filename, O_RDWR);
			            	if(file_fd == -1)
								cerr << "ERROR: " << errno << " Open()" << endl;
							sendfile(c_fd, file_fd, NULL, 40000);
							close(file_fd);
							//reset filename
							strcpy(filename,"");
						}
			        }
				}
				closedir(dirp);
				sleep(3);
				//send end of dir signal
				char EOD[10];
				strcpy(EOD,"End_Of_Dir");
				write(c_fd, EOD, BUFSIZ );
				exit(0);
			}	
			default://parent, do nothing??
				wait(0);
				break;
		}
		delete dirname;
	}
	
	//clean up
	close(c_fd);
	close(sockfd);

	cout << "\nShutting down server..." << endl
		 << "Bye Bye~" << endl;
	
	return 0;
}
