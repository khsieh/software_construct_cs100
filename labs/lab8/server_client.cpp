//Kevin Hsieh
//Trent Callan

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <iostream>
#include <errno.h>

using namespace std;

void server(){
    int sock_fd, new_fd;
    struct sockaddr_un addr, client_addr;
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
    new_fd = accept(sock_fd, (struct sockaddr *)&addr, (socklen_t *)&sun_size);
    if(new_fd == -1)
        cerr << "ERROR: Accept()" << endl;
    else
        cout << "Accept Success!" << endl;
    
    char* buf[1]= {"1 2 3 4 5"};
    if(write(new_fd, buf[0], strlen(buf[0])) == -1){
        cerr << "ERROR: Write()" << endl;
        exit(1);
    }
    else{
        cout << "writing into client..." << endl;
    }
    sleep(1);
    close(sock_fd);
    cout << "Server shutting down." << endl;
}

void client(){
    int sock_fd;
    struct sockaddr_un server_addr;
    //~ bzero(&server_addr,BUFSIZ);
    char pathName[108] = "test";
    
    strcpy(server_addr.sun_path,pathName);
    server_addr.sun_family = AF_UNIX;
    sock_fd = socket(AF_UNIX, SOCK_STREAM,0);
    
    if(sock_fd == -1){
        cerr << "ERROR: Socket()" << endl; 
        exit(1);
    }
    else
        cout << "Socket Success!" << endl;
    
    if(connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1){
        cerr << "ERROR: Connect" << endl;
        exit(1);
    }
    else 
        cout << "Connecting to server..." << endl;
    
    sleep(1);
    char buf[5];
    int r_check = read(sock_fd, buf, 300);

    if( r_check == -1){
        cerr << "ERROR: Read()" << endl;
        exit(1);
    }
    else{
        cout << "Reading from Server..." << endl;
        buf[r_check] = '\0';
        cout << buf << endl;
    }
    sleep(1);
    
    close(sock_fd);
    cout << "Client shutting down." << endl;
}

int main(){
    int pid;
    pid = fork();
    
    switch(pid){
        case -1://fork error
            cerr << "Fork Failed!" << endl;
            break;
        case 0://chiild process: client
            sleep(2);
            client();
            break;
        default://parent process: server
            server();
            wait(0);
            break;
    }
    unlink("test");
    
    return 0;
}
