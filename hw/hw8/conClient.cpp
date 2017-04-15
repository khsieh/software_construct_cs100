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

using namespace std;

int main(int argc, char *argv[])
{
	int sockfd;
    struct hostent *host;
    // connector's address information
    struct sockaddr_in s_addr;

	// the port client will be connecting to
    //SID: 861054367
    int port = 54367;
	
	//cstring to hold hostname
	char *hostname = new char[BUFSIZ];

    //check for command line argument
    //one argument should be pass in, the hostname
	if(argc != 2){
		cerr << "ERROR: Usage: " << argv[0] << " hostname" << endl;
		cerr << "i.e. ./itClient well.cs.ucr.edu" << endl;
		exit(1);
	}

	strcpy(hostname,argv[1]);

	//set up host name
	host = gethostbyname(argv[1]);
	if(host == NULL){
		cerr << "ERROR: " << errno << " gethostbyname()" << endl;
		exit(1);
	}
	else
		cout << "Connecting to remote server: " << hostname << endl;

	//set up socket
	if( ( sockfd = socket(AF_INET, SOCK_STREAM, 0) ) == -1 ){
		cerr << "ERROR: " << errno << " Socket()" << endl;
		exit(1);
	}
	else
		cout << "Socket setup successful." << endl;

	// host byte order
	s_addr.sin_family = AF_INET;
	// short, network byte order
	cout << "Connecting to " << hostname
		 << " using port " << port << " ..." << endl;
	s_addr.sin_port = htons(port);
	s_addr.sin_addr = *((struct in_addr *)host->h_addr);
	//zero out the rest of the struct
	memset(&(s_addr.sin_zero), '\0', sizeof(s_addr) );

	if(connect(sockfd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr)) == -1){
		cerr << "ERROR: " << errno << " Connect()" << endl;
		exit(1);
	}
	else
		cout << "Connection established!" << endl;

	//setup to make newdir
	string dirname;

	cout << "\nEnter the directory name you wish to copy: ";
	cin  >> dirname;

	int write_val = write(sockfd, dirname.c_str(), BUFSIZ);
	if(write_val == -1){
		cerr << "ERROR: " << errno << " Write()" << endl; 
		exit(1);
	}

	char if_exist[BUFSIZ];
	if(read(sockfd, if_exist, BUFSIZ) == -1){
		cerr << "ERROR: " << errno << " Read()" << endl;
		exit(1);
	}
	if(!strcmp(if_exist,"-1")){
		cerr << "directory does not exist :C\n"
			 << "existing program..." << endl;
		exit(1);
	}
	else if(!strcmp(if_exist,"1")){
		cout << "making new directory named: " << dirname << endl;
		mkdir(dirname.c_str(), S_IRWXU);
	}

	// load content of file with read/write
	while(1){
		//read for filename
		char filename[BUFSIZ];	
		if(read(sockfd, filename, BUFSIZ) == -1){
			cerr << "ERROR: " << errno << " Read()" << endl;
			exit(1);
		}
		else{
			cout << "Writing file: " << filename << "... " << endl;
			if(strcmp(filename,"End_Of_Dir")){
				
				char rw_buf[BUFSIZ] = {};
				strcpy(rw_buf,"");
				int file_fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
				if(file_fd == -1)
					cerr << "ERROR: " << errno << " Open()" << endl;
				
				int last_byte = read(sockfd,rw_buf, BUFSIZ);
				rw_buf[last_byte] = '\0';
				usleep(500);
				write(file_fd,rw_buf,BUFSIZ);
				usleep(500);
				
				close(file_fd);
				strcpy(rw_buf,"");
			}
			else
				break;
		}
		sleep(1);
	}

	//clean up
	delete hostname;
	close(sockfd);

	cout << "\nDisconnecting from server... " << endl
		 << "Bye Bye~" << endl;

	return 0;
}
