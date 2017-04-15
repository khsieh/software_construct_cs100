//my_shell.cpp
/*
 * Course: CS 100 Fall 2013
 *
 * First Name: <Kevin>
 * Last Name: <Hsieh>
 * Username: <khsie003>
 * email address: <khsie003@ucr.edu>
 *
 *
 * Assignment: <Homework #6>
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */  

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sstream>
#include <iostream>

using namespace std;

bool iRedir;
bool oRedir;
bool ifPipe;
bool background;

void parse_arg(string & buf, char*args[]){
    
    stringstream ss(buf);
    char par_arg[BUFSIZ];
    while(ss >> par_arg){
        char * cur_par = new char[BUFSIZ];
        
        if(par_arg[0] == '<')
            iRedir = true;
        if(par_arg[0] == '>')
            oRedir = true;
        if(par_arg[0] == '|')
            ifPipe = true;
        if(par_arg[0] == '&'){ 
            background = true;
            continue;
        }
            
        unsigned i = 0;
        for(i = 0; par_arg[i] != '\0'; ++i){
            cur_par[i] = par_arg[i];
        }
        cur_par[i] = '\0';
        *args++ = cur_par;
    }
    *args = 0;
}

void modArgs(char * args[]){
    //mod args to get only the first arg
    for(unsigned i = 1; args[i]; ++i){
            delete args[i];
    }
    args[1] = 0;
}

void modTee(char * args[], char * newargs[], char * inFile){
    
    for(unsigned i = 0; args[i]; ++i){
        if(args[i][0] == '<'){
            unsigned x;
            for(x = 0; args[i+1][x] != '\0'; ++x){
                inFile[x] = args[i+1][x];
            }
            inFile[x] = '\0';
        }
    }
    
    //take out every < and > and "<+1"
    unsigned k, j;
    for(k = 0, j = 0; args[k]; ++k){
        if(args[k][0] == '<' || args[k][0] == '>'){
            if(args[k][0] == '<')
                k++;
            continue;
        }
        
        char * temp = new char [BUFSIZ];
        
        unsigned x;
        for(x = 0; args[k][x] != '\0';++x){
            temp[x] = args[k][x];
        }
        temp[x] = '\0';
        newargs[j] = temp;
        ++j;
    }
    newargs[j] = 0;
    
    //delete args
    for(unsigned i = 0; args[i]; ++i){
        delete args[i];
    }
    
    //set args  = newargs
    unsigned l;
    for(l = 0; newargs[l]; ++l){
        args[l] = newargs[l];
    }
    args[l] = 0;
}

void getFileNames(char * args[], char * inFile, char * outFile){
    
    if(iRedir && strcmp(args[0], "tee")){ //'<' infile: i + 1, outfile i - 1
        for(unsigned i = 0; args[i]; ++i){
            if(args[i][0] == '<'){ // get input filename
                //get infile name
                unsigned p;
                for(p = 0; args[i+1][p] != '\0'; ++p){
                    inFile[p] = args[i + 1][p];
                }
                inFile[p] = '\0';
                
                //get outfile name
                unsigned q;
                for(q = 0; args[i -1][q] != '\0'; ++q){
                    outFile[q] = args[i-1][q];
                }
                outFile[q] = '\0';                
            }
        }
    }
    
    if(oRedir && strcmp(args[0], "tee")){ //'>' infile: i -1, outfile: i + 1
        for(unsigned i = 0; args[i]; ++i){
            if(args[i][0] == '>'){
                //get infile name
                unsigned p;
                for(p = 0; args[i-1][p] != '\0'; ++p){
                    inFile[p] = args[i - 1][p];
                    //~ cout << "in[p]: " << inFile[p] << endl;
                }
                inFile[p] = '\0';
                
                //get outfile name
                unsigned q;
                for(q = 0; args[i+1][q] != '\0'; ++q){
                    outFile[q] = args[i+1][q];
                }
                outFile[q] = '\0';
                
            }
        }
    }
    
    if((iRedir || oRedir) && strcmp(args[0], "tee"))
        modArgs(args);
        
    if((iRedir||oRedir) && !strcmp(args[0], "tee")){
        char *newargs[64];
        modTee(args, newargs, inFile);
    }
    
}

void setFileDescriptors(char * args[], const char *inFile, const char *outFile){
    int inFD, outFD;
    if(iRedir && strcmp(args[0], "tee")){// '<' redirect
        inFD = open(inFile, O_RDWR);
        if(inFD < 0)
            cerr << "Error: opening input file\n";
        dup2(inFD,0);
        close(inFD);
        
        if(strcmp(outFile,args[0])){
            outFD = open(outFile, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            if(outFD < 0)
                cerr << "Error: opening output file\n";
            dup2(outFD,1);
            close(outFD);
        }
        
    }
            
    if(oRedir && strcmp(args[0], "tee")){// '>' redirect                
        if(strcmp(inFile,args[0])){
            inFD = open(inFile, O_RDWR);
            if(inFD < 0)
                cerr << "Error: opening input file\n";
            dup2(inFD, 0);
            close(inFD);
        }
        
        outFD = open(outFile, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if(outFD < 0)
            cerr << "Error: opening output file\n";
        dup2(outFD,1);
        close(outFD);
        
    }
    
    if( iRedir && !strcmp(args[0], "tee")){
        //dup2 the inFile
        inFD = open(inFile, O_RDWR);
        if(inFD < 0)
            cerr << "Error: opening input file\n";
        dup2(inFD, 0);
        close(inFD);
    }
            
}

void par_Pipe(char *args[], char *args2[]){
    unsigned i;
    for(i = 0; args[i]; ++i){
        if(args[i][0] == '|')
            break;
    }
    // cout << "i: " << i << endl;
    // cout << "args[i]: " << args[i] << endl;
    i++;
    unsigned j;
    for( j = i; args[j]; ++j){
        args2[j-i] = args[j];
        //~ cout << "__args2[" << j-i -1 << "]: " << args2[j-i-1] << endl;
    }
    args2[j] = 0;
    //~ cout << "args[i-1]: " << args[i -1] << endl;
    delete args[i-1];
    args[i - 1] = 0;
}

//prase all paths by ':'
void par_Path(char *paths[], char * path_buf){
    //change each ':' into '\0'
    unsigned i;
    for(i = 0; path_buf[i] != '\0'; ++i){
        if(path_buf[i] == ':')
            path_buf[i] = '\0';
    }
    path_buf[i] = 0;
    
    //paths hold each path in a slot
    paths[0] = path_buf;
    for(unsigned j = 0; j < i; ++j){

        if(*path_buf == '\0'){
            *paths = ++path_buf;
            paths++;
        }
        else
            path_buf++;
    }
    *paths = 0;
}

//check each possible path
char * check_paths(char* paths[], char * des_path, const char * command){
    for(unsigned i = 0; paths[i]; ++i){
        strcpy(des_path,paths[i]);
        strcat(des_path,"/");
        strcat(des_path,command);
        //return des_path if path is accessable
        if(access(des_path,F_OK) == 0){
            return des_path;
        }
    }
    des_path = 0;
    return des_path;
}


int exec_arg(char * args[]){
    int fd[2];
    char * inFile = new char [BUFSIZ]; 
    char * outFile = new char [BUFSIZ];
    char * path_buf = new char [BUFSIZ];
    char * paths[64];
    char * des_path = new char [BUFSIZ];
    
    //if pipe line exists, separate into two commands
    char * args2[64];
    if(ifPipe){
        par_Pipe(args,args2);
        if(pipe(fd) < 0)
            cerr << "Pipe failed!\n";
        // cout << "here?" << endl;
    }

    //set up path
    char * temp = getenv("PATH");
    strcpy(path_buf,temp);
    par_Path(paths,path_buf);

    //fork and execute
    int status;
    int pid = fork();



    switch(pid){
        case -1:
            cerr << errno << " fork failed!\n";
            return -1;
        case 0: // child process
            //check for if I/O redirect is needed
            if(!ifPipe){
                getFileNames(args,inFile,outFile);
                setFileDescriptors(args,inFile,outFile);
            }
            else{
                //piping for child
                getFileNames(args,inFile,outFile);
                dup2(fd[0],0);
                close(fd[1]);
                
            }
            
            //find path 
            if( (des_path = check_paths(paths, des_path, args[0]) ) == 0)
                cerr << "ERROR: PATH NOT FOUND!\n" << flush;
                
            // execute the command
            if(execv(des_path,args) == -1)
                cerr << args[0] << " failed!\n" << flush;
            
            _exit(1);
        default:// parent process
            if(ifPipe){
                for(unsigned o = 0; args2[o]; ++o){
                    cout << "args2[" << o << "]: " << args2[o] << endl;
                }
                //~ piping for parent
                getFileNames(args2, inFile, outFile);
                dup2(fd[1],1);
                close(fd[0]);

                //
                execvp(args2[0],args);
            }
            else{
                //delete inFile and outFile
                delete [] inFile;
                delete [] outFile;
                delete [] des_path;
                delete [] path_buf;
                iRedir = false;
                oRedir = false; 
                ifPipe = false; 
            }
            if(!background){
                background = false;
                return waitpid(-1, &status, 0);
            }
            else
                return 0;
    }
    
    return 0;
}

void signal_handlers(int sigInt){
    switch(sigInt){
        case SIGINT:
            cout << "\nChild process receive SIGINT\n";
            break;
        default:
            break;
    }
}

int main(){
    
    signal(SIGINT, signal_handlers);

    string buf;
    char *args[64];
    while(1){
        cout.flush();
        cout << "~> " << flush;
        getline(cin,buf);
        parse_arg(buf, args);
        int ex;
        if((ex = exec_arg(args)) < 0)
            cerr << "Error: " << args[0] << endl;
        if(ex > 0)
            usleep(20);
        //destructor to prevent memory leak
        for(unsigned i = 0; args[i]; ++i){
            delete args[i];
        }
    }
    return 0;
}
