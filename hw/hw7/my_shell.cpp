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
 * Assignment: <Homework #7>
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

bool iRedir, oRedir;
bool ifPipe;
bool background;

void parse_arg(string &allArg, char * args[]){

	stringstream ss(allArg);
    char par_arg[BUFSIZ];
    while(ss >> par_arg){

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

        char * cur_par = new char[BUFSIZ];

        unsigned i = 0;
        for(i = 0; par_arg[i] != '\0'; ++i){
            cur_par[i] = par_arg[i];
        }
        cur_par[i] = '\0';
        *args++ = cur_par;
    }
    *args = 0;
}

void par_Path(char *paths[], char * path_buf){
    unsigned i;
    for(i = 0; path_buf[i] != '\0'; ++i){
        if(path_buf[i] == ':')
            path_buf[i] = '\0';  
    }
    path_buf[i] = 0;

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

void par_pipe(char *args[], char **cmds[] ){
    cmds[0] = &(args[0]);
    
    unsigned j = 1;
    for(unsigned i = 0; args[i]; ++i){
        // cout << "args[" << i << "] " << args[i] << endl;
        if(args[i][0] == '|'){
            args[i] = 0;
            cmds[j] = &(args[i + 1]);
            ++j;
        }
    }
    cmds[j] = 0;
}

char * check_paths(char* paths[], char * des_path, const char * command){

    //check for all possible paths
    for(unsigned i = 0; paths[i]; ++i){
        strcpy(des_path,paths[i]);
        strcat(des_path,"/");
        strcat(des_path,command);
        if(access(des_path,F_OK) == 0){
            return des_path;
        }
    }

    //check current directory
    strcpy(des_path,"./");
    strcat(des_path,command);
    if(access(des_path,F_OK) == 0)
            return des_path;
    else  //return NULL if no path found
        des_path = 0;
    return des_path;
}

/* setting file descriptors
 * according to the characters '<' '>'
 * '<' + 1 is input file, '>' + 1 is outputfile*/
void set_file_descriptors(char* args[]){  
	int inFd = -1;
	int outFd = -1;
    for(unsigned i = 0; args[i]; ++i){
    	if(args[i][0] == '<'){
    		inFd = open(args[i+1], O_RDWR);
    		if(inFd < 0){
    			cerr << "ERROR: opening file: " 
    				 << args[i+1] 
                     << " Errno: " << errno << endl;
			}
            else{
    			dup2(inFd,0);
    			close(inFd);
            }
		}

    	if(args[i][0] == '>'){
    		outFd = open(args[i+1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    		if(outFd < 0){
    			cerr << "ERROR: opening file: " 
    				 << args[i+1] 
                     << " Errno: " << errno << endl;
			}
            else{
    			dup2(outFd,1);
    			close(outFd);
            }
    	}
    }
}

//change arguments to only the comand and necessary arguments
void mod_args(char* args[]){
    for(unsigned i = 1; args[i]; ++i){
		if(i == 1 && (args[i][0] == '<' || args[i][0] == '>') ){
            delete args[i];
			args[i] = 0;
		}
        else if(i == 1)
            continue;
		else
			delete args[i];
	}
	args[2] = 0;
}

//executing argument by path
int exec_arg(char* args[]){
    //set up path
    char * paths[64];
    char * des_path = new char [BUFSIZ];
    char * path_buf = new char [BUFSIZ];

    //get all possible path from $PATH
    char * temp = getenv("PATH");
    strcpy(path_buf,temp);
    //parse each possible path into paths
    par_Path(paths,path_buf);

	///fork and execute
    int pid = fork();

    switch(pid){
    	case -1://error on fork
    		cerr << errno << " Fork Failed!\n";
    		return -1;
    	case 0://child process
    		if(background)
    			setsid();
            //set file descriptors if necessary.
    		if((iRedir || oRedir) && !ifPipe){
	    		set_file_descriptors(args);
	    		mod_args(args);
                iRedir = false;
                oRedir = false;
    		}
            if(ifPipe)
            {
                mod_args(args);
            }
            //check for correct path
            if( (des_path = check_paths(paths, des_path, args[0]) ) == 0){
                cerr << "ERROR: PATH NOT FOUND!" 
                     << "\nErrno: " << errno << endl;
            }
            //execute command
    		 if(execv(des_path,args) == -1){
                cerr << args[0] << " failed!" 
                     << " Errno: " << errno<< endl;
             } 
            _exit(1);
    		break;

    	default://parent process
            delete [] des_path;
            delete [] path_buf;
    		if(!background){
    			return wait(0);
    		}
            else{
                background = false;
                return 0;
            }
    }
}

void exec_pipe(char **cmds[], int pipefd[]){

    int cmdSize = 0;
    for(unsigned i = 0; cmds[i]; ++i){
        cmdSize++;
    }

    if(cmdSize == 1){
        close(pipefd[0]); // close write end of pipe
        exec_arg(cmds[0]);
    }
    else{
        char ** cmd2[64];
        unsigned j = 0;
        for(unsigned i = 1; cmds[i]; ++i){
            cmd2[j] = cmds[i]; 
            j++;
        }
        cmd2[j] = 0;
        pipe(pipefd);
        close(pipefd[1]); // close read end of pipe
        exec_arg(cmds[0]);
        exec_pipe(cmd2,pipefd);
    }
}

void signal_handlers(int sigInt){
    switch(sigInt){
        case SIGINT:
            cout << "\nChild process receive SIGINT" << endl;
            cout << "> " << flush;
            break;
        default:
            break;
    }
}

int main(){
    
	if (signal(SIGINT, signal_handlers) == SIG_ERR )
        cerr << "SIGNAL ERROR " << errno << endl;

	string allArg;
    char *args[64];
    char **cmds[64];
	while(1){
		cout << "> " << flush;
		getline(cin,allArg);
		parse_arg(allArg,args);

        if(ifPipe){
            int pipefd[2]; 
            par_pipe(args,cmds);
            exec_pipe(cmds,pipefd);
            ifPipe = false;
        }
        // for(unsigned k = 0; cmds[k]; ++k)
        // cout << "cmds[" << k << "] " << *(cmds[k]) << endl;
        else{
    		int ex;
    		if((ex = exec_arg(args)) < 0)
                cerr << "Error: " << args[0] << " Errno: " << errno << endl;
            if(ex > 0)
                usleep(20);
        }
		//destructor to prevent memory leak
        for(unsigned i = 0; args[i]; ++i){
            delete args[i];
        }
	}		
	return 0;
}
