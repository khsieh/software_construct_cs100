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

using namespace std;

int main()
{
    //~ for (int i = 0; i < 10; ++i)
    //~ {
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
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        char opt;
        
        cout << "R/W: ";
        cin >> opt;
        //~ if (i%2 == 0)
            //~ opt = 'r';
        //~ else
            //~ opt = 'w';
        write(sock_fd, &opt, 300);
        sleep(1);
        
        if(opt == 'r')
        {
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
        }
        else if(opt == 'w')
        {
            string line;
            getline(cin,line);          
            char buf[300];
            strcpy(buf,line.c_str());
            write(sock_fd, buf, 300);
        }
        close(sock_fd);
        cout << "Client shutting down." << endl;
    //~ }
    
    return 0;
}
