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

int my_rm_f(const char * path){
    
    DIR *dirp = opendir(path);
    
    dirent * direntp;
    
    while((direntp = readdir(dirp))){
        if(direntp -> d_name[0] == '.')
            continue;
        struct stat dir_buf;
        
        string str = direntp -> d_name;
        string str2 = path;
        str2 += str;
        
        if (stat(str2.c_str(), & dir_buf) != -1)
        {
            if(!S_ISDIR(dir_buf.st_mode))
                my_rm(str2.c_str());
        }
    }
}

int my_rm_R(const char * path){
    
    DIR *dirp = opendir(path);
    
    dirent * direntp;
    
    while((direntp = readdir(dirp)))
    {
        //~ cout << "do you have files\n";
        if(direntp -> d_name[0] == '.')
            continue;
        
        //~ for(unsigned i = 0; i < indents; ++i)
            //~ cout << "  ";
            
        //~ cout << direntp -> d_name << endl;
        
        struct stat dir_buf;
        
        string str = path;
        string str2 = direntp -> d_name;
        str += "/";
        str += str2;
        
        if (stat(str.c_str(), & dir_buf) != -1)
        {
            if(S_ISDIR(dir_buf.st_mode))
                my_rm_R(str.c_str());
            if(my_rm(str.c_str()) == -1){
            }
                //my_readdir(str.c_str(),indents+1);
        }
    }
    rmdir(path);
    
    closedir(dirp);
    
    return 0;
}

int main(int argc, char **argv){
    
    if(argc < 2){
        cerr << "missing operand\n" << endl;
    }
    
    else{
        string option = argv[1];
        
            //~ 
        //~ DIR * dirp;
        //~ char * sorc = argv[2];
        //~ char path[100] = "";
        //~ strcat(path, "./");
        //~ strcat(path, sorc);
        //~ cout << path << endl;
        
        //~ dirp = opendir(path);
        
        if(option == "-r"){
            DIR * dirp;
            char * sorc = argv[2];
            char path[100] = "";
            strcat(path, "./");
            strcat(path, sorc);
            dirp = opendir(path);
            my_rm_R(path);
        }
        if(option == "-f"){
            DIR * dirp;
            char * sorc = argv[2];
            char path[100] = "";
            strcat(path, "./");
            strcat(path, sorc);
            dirp = opendir(path);
            my_rm_f(path);
        }
        else{
            DIR * dirp;
            char * sorc = argv[1];
            char path[100] = "";
            strcat(path, "./");
            strcat(path, sorc);
            dirp = opendir(path);
            cout << path << endl;
            my_rm(path);
        }
    }
    return 0;
}
