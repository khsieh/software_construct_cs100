/*
 * Course: CS 100 Fall 2013
 *
 * First Name: <Kevin>
 * Last Name: <Hsieh>
 * Username: <khsie003>
 * email address: <khsie003@ucr.edu>
 *
 *
 * Assignment: <Homework #9>
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
#include <pthread.h>

using namespace std;

// struct Thread_Helper{
// 	// long sockfd;
// 	// struct sockaddr_in s_addr;
// 	char * host_cstr;
// 	Thread_Helper(char * temp)
// 	{
// 		strcpy(host_cstr, temp);
// 	}
// };

void client_copyfile(long sockfd, string new_dirname)
{
	char cur_dir[50];
	
	// load content of file with read/write
	while(1){
		//read for filename
		char filename[BUFSIZ];	
		if(read(sockfd, filename, BUFSIZ) == -1){
			cerr << "ERROR: " << errno << " Read()" << endl;
			exit(1);
		}
		else{
			//get basename of filename
			//cat to current dir
			strcpy(cur_dir, new_dirname.c_str());
			char * basep = strdup(filename);
			char * basen = basename(basep);
			strcat(cur_dir, "/");
			strcat(cur_dir, basen);

			if(strcmp(filename,"End_Of_Dir")){

				cout << "Writing file: " << cur_dir << " ... " << endl;
				
				char rw_buf[BUFSIZ] = {};
				strcpy(rw_buf,"");
				int file_fd = open(cur_dir, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
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
			strcpy(cur_dir, "");
		}
		sleep(1);
	}
}

void client_work(long & sockfd, struct sockaddr_in &s_addr)
{
	if(connect(sockfd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr)) == -1){
		cerr << "ERROR: " << errno << " Connect()" << endl;
		exit(1);
	}
	else
		cout << "Connection established!" << endl;

	//setup to make newdir
	string dirname;
	string new_dirname;

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
		
		cout << "Ener name of new Directory: ";
		cin  >> new_dirname;
		mkdir(new_dirname.c_str(), S_IRWXU);
	}
	client_copyfile(sockfd,new_dirname);
}

void* client_setup(void * temp)
{
	char * host_name_str = reinterpret_cast<char*>(temp);
	//set up host name
	struct hostent *host;
	host = gethostbyname(host_name_str);
	if(host == NULL){
		cerr << "ERROR: " << errno << " gethostbyname()" << endl;
		exit(1);
	}
	else
		cout << "Connecting to remote server: " << host_name_str << endl;

	long sockfd;
    // struct hostent *host;
    // connector's address information
    struct sockaddr_in s_addr;
	// the port client will be connecting to
    // SID: 861054367
    int port = 54367;
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
	cout << "Connecting host using port " << port << " ..." << endl;
	s_addr.sin_port = htons(port);
	s_addr.sin_addr = *((struct in_addr *)host->h_addr);
	//zero out the rest of the struct
	memset(&(s_addr.sin_zero), '\0', sizeof(s_addr) );

	client_work(sockfd, s_addr);
	close(sockfd);
	return NULL;
}

const int MAX_THREAD_NUM = 10;
int main(int argc, char *argv[])
{

	//check for command line argument
    //one argument should be pass in, the hostname
	if(argc != 2){
		cerr << "ERROR: Usage: " << argv[0] << " hostname" << endl;
		cerr << "i.e. ./itClient well.cs.ucr.edu" << endl;
		exit(1);
	}

	char temp[50] = {};
	strcpy(temp, argv[1]);
	pthread_t threads[MAX_THREAD_NUM] = {};

	// multithreading here:
	for(int t = 1; t <= 10; ++t){
		cout << "=============================================" << endl;
		cout << "Thread " << t << " Starting..." << endl;
		pthread_create(&threads[t], NULL, client_setup, (void *)& temp);
		//check pthread_create
		pthread_join(threads[t], NULL);
	}

	cout << "\nDisconnecting from server... " << endl
		 << "Bye Bye~" << endl;

	return 0;
}
