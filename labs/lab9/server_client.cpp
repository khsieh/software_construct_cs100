//Kevin Hsieh
//Calvin Deng

#include <pthread.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <fstream>

using namespace std;

const int TCOUNT = 10;
int new_fd;
ifstream in;
ofstream out;
pthread_mutex_t x;

void *readFile ( void * tid)
{
    pthread_mutex_lock(&x);
    string buf;
    while(getline(in,buf)){
        if(write(new_fd, buf.c_str(), strlen(buf.c_str())) == -1)
        {
            cerr << "ERROR: Write()" << endl;
            exit(1);
        }
        else
            cout << "writing into client..." << endl;
    }
    pthread_mutex_unlock(&x);
    pthread_exit(NULL);
}

void *writeFile ( void * tid)
{
    pthread_mutex_lock(&x);
    char* buf[255];
    read(new_fd,buf,300);
    out << buf << endl;
    pthread_mutex_unlock(&x);
    pthread_exit(NULL);
}


void server(char* name){
    int sock_fd, thread_num;
    struct sockaddr_un addr, client_addr;
    pthread_t threads[TCOUNT];
    //~ bzero(&addr,BUFSIZ);
    char pathName[108] = "test";
    int sun_size;
    
    strcpy(addr.sun_path, pathName);
    addr.sun_family = AF_UNIX;
    sock_fd = socket(AF_UNIX, SOCK_STREAM,0);
    
    if(sock_fd == -1){
        cerr << "ERROR: Socket()" << endl; 
        exit(1);
    }
    else
        cout << "Socket Success!" << endl;  
    
    
    if(bind(sock_fd, (struct sockaddr *)&addr, sizeof(sockaddr) ) == -1){
        cerr << "ERROR: Bind() " <<  errno << endl;
        exit(1);
    }
    else
        cout << "Binding successful!" << endl;
    
    if(listen(sock_fd, 10) == -1){
        cerr << "ERROR: Listen()" << endl;
        exit(1);
    }
    else
        cout << "Listen Success!" << endl;
    
    sun_size = sizeof(struct sockaddr_un);
    //~ for(int i = 0; i < TCOUNT; ++i)
    int i = 0;
    while(1)
    {
        
        new_fd = accept(sock_fd, (struct sockaddr *)&addr, (socklen_t *)&sun_size);
        if(new_fd == -1)
            cerr << "ERROR: Accept()" << endl;
        else
            cout << "Accept Success!" << endl;
       char opt[2];
       sleep(1);
       read(new_fd,opt,300);
       if(!strcmp(opt,"w")){
            out.open(name);
            thread_num = pthread_create(&threads[i], NULL, writeFile, (void *)i);
            out.close();
        }
       else if(!strcmp(opt,"r")){
           in.open(name);
       thread_num = pthread_create(&threads[i], NULL, readFile, (void *)i);
       in.close();
       }
       if (thread_num)
       {
            cerr << "Error threading!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
            exit(-1);
       }
       sleep(2);
       cout << "done writing for " << i << endl;
       ++i;
    }
    
    
    sleep(1);
    close(sock_fd);
    cout << "Server shutting down." << endl;

}


int main(int argc, char* argv[] ){
    
    
    server(argv[1]);
    unlink("test");
    in.close();
    return 0;
}
