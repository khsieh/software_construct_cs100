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

	string buf;
	cout << "Enter a Directory name you wish to check with ls -l\n";
	cout << "(type \"end\" to stop) " << endl;
	//loop for write
	int write_val = -1;
	char lines[BUFSIZ];
	while(1){
		cout << "> ";
		cin  >> buf;

		write_val = write(sockfd, buf.c_str(), BUFSIZ);
		if(buf == "end")
			break;

		if(write_val == -1){
			cerr << "ERROR: " << errno << " Write()" << endl;
			exit(1);
		}
		else{
			sleep(1);
			cout << "========================================" << endl;
			read(sockfd, lines, BUFSIZ);
			cout << lines << endl;
			memset(lines, 0, BUFSIZ);
			cout << "========================================" << endl;
		}

		
	}
	
	//clean up
	delete hostname;
	close(sockfd);

	cout << "Disconnecting from server... " << endl
		 << "Bye Bye~" << endl;

	return 0;
}
