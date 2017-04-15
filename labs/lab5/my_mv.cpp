//Rachel Law
//Kevin Hsieh

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <string.h>

using namespace std;

int my_rm(const char * sorc){
    int i = unlink(sorc);
    if( i == -1){
        cerr << "ERROR (" << errno << ") " << endl;
        return -1;
    }
    else{
        return 0;
    }
}

void my_rename(char * dest, char * sorc){
    link(sorc, dest);
    my_rm(sorc);
}

//~ void my_mv(char * sorc, char * dest){
    //~ 
//~ }

int main(int argc, char **argv)
{
    DIR * dirp;
    if(argc == 1){
        cerr << "missing destination file operand after '" << argv[0] 
             << "'" << endl;
             exit(1);
    }
    
    if(argc == 3){
        char * path = argv[2];
        if(!(dirp = opendir(path))){
            my_rename(path, argv[1]);
        }
        else{
            //~ string str = "./";
            //~ str += path;
            //~ my_mv(str)
        }
    }
        
    return 0;
}
