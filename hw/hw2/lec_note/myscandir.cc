#include <dirent.h>
#include <iostream>

using namespace std;

int main() {
 int i;
 char *dirname = "/";
 struct dirent  **namelist;            
 int number_of_entries;
 number_of_entries = scandir(dirname, &namelist, 0, alphasort);

 if (number_of_entries > 0 )
  for (i=0; i<number_of_entries; i++)
    cout << namelist[i]->d_name << endl;
}
