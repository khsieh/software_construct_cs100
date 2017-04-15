#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  if (argc > 1) {
    char *path = argv[1];
    struct stat buf;
    if ( stat(path, &buf) != -1 ) {
      cout << "Stat for `/': Links " << buf.st_nlink <<", Size " << buf.st_size << endl;
    }
    else 
      cerr << "Error " << errno << " opening" << path<< endl;
  }
  else
    cerr << "Usage: " << argv[0] << "<path_to_dir>" << endl;
}
