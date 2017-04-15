//my_ls.cc
/*
 * Course: CS 100 Fall 2013
 *
 * First Name: <Kevin>
 * Last Name: <Hsieh>
 * Username: <khsie003>
 * email address: <khsie003@ucr.edu>
 *
 *
 * Assignment: <Homework #2>
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */  

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>

using namespace std;

void printOctalMode (const struct stat & buf)
{
    cout << "-";
    //checking for user's permission
    if(buf.st_mode & S_IRUSR) cout << "r";
    else cout << "-";
    if(buf.st_mode & S_IWUSR) cout << "w";
    else cout << "-";
    if(buf.st_mode & S_IXUSR) cout << "x";
    else cout << "-";
    //checking for group's permission
    if(buf.st_mode & S_IRGRP) cout << "r";
    else cout << "-";
    if(buf.st_mode & S_IWGRP) cout << "w";
    else cout << "-";
    if(buf.st_mode & S_IXGRP) cout << "x";
    else cout << "-";
    //checking for other's permission
    if(buf.st_mode & S_IROTH) cout << "r";
    else cout << "-";
    if(buf.st_mode & S_IWOTH) cout << "w";
    else cout << "-";
    if(buf.st_mode & S_IXOTH) cout << "x";
    else cout << "-";
    
    //~ buf.st_mode & S_IXOTH ? cout << "x"
    //~ : cout << "-";
}

void printTimeStamp (const struct stat & buf)
{
    time_t t = buf.st_mtime;
    struct tm localT;
    localtime_r(&t, &localT);
    char timestr[40];
    strftime(timestr, sizeof(timestr), "%b %d %R", &localT);
    
    cout << timestr << " ";
}

void print_stat( const char * path, struct stat & buf)
{
    if ( stat(path, &buf) != -1 )  
    {
        printOctalMode(buf);   
        cout << " " << buf.st_nlink << " "
             << buf.st_size << " ";
        printTimeStamp(buf);
             //~ << buf.st_mtime << " "
        cout << path << endl;
    }
}

int my_readdir(const char * path,unsigned indents)
{
    DIR *dirp;
    if(!(dirp = opendir(path)))
    {
        cerr << "ERROR(" << errno << ") opening " << path << endl;
        return errno;
    }
    
    dirent * direntp;
    
    while((direntp = readdir(dirp)))
    {
        if(direntp -> d_name[0] == '.')
            continue;
        
        for(unsigned i = 0; i < indents; ++i)
            cout << "  ";
            
        cout << direntp -> d_name << endl;
        
        struct stat dir_buf;
        
        string str = path;
        string str2 = direntp -> d_name;
        str += "/";
        str += str2;
        
        if (stat(str.c_str(), & dir_buf) != -1)
        {
            if(S_ISDIR(dir_buf.st_mode))
                my_readdir(str.c_str(),indents+1);
        }
    }
    closedir(dirp);
    
    return 0;
}

int main(int argc, char **argv) 
{
    char * path;
    if(argc > 1)
        path = argv[1];
    else
        path = ".";
        
    struct stat buf;
    DIR * dirp;
    //check if it is a dir
    //~ if(!S_ISDIR(buf.st_mode))
    if(!(dirp = opendir(path)))
        print_stat(path,buf);
    //recursive calls for readdir
    else
        my_readdir(path,1);
    
    return 0;
}
