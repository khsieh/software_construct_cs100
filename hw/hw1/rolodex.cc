/*
* Course: CS 100 Fall 2013
*
* First Name: <Kevin>
* Last Name: <Hsieh>
* Username: <khsie003>
* email address: <khsie003@ucr.edu>
*
*
* Assignment: <Homework #1>
*
* I hereby certify that the contents of this file represent
* my own original individual work. Nowhere herein is there
* code from any outside resources such as another individual,
* a website, or publishings unless specifically designated as
* permissible by the instructor or TA.
*/  

#include <iostream>
#include <cstdlib>
#include <fstream>


using namespace std;

struct File
{
    string first_name;
    string last_name;
    string address;
    string phone;
    File * nextFile;
    File():nextFile(NULL){}
    File(string fn, string ln, string a, string p)
        :first_name(fn), last_name(ln), address(a), phone(p), nextFile(NULL){}
};

class Rolodex
{
    private:
        File * head;
        File * tail;
        bool changed;
    public:
        Rolodex():head(NULL), tail(NULL),changed(false){}//done
        ~Rolodex();//done
        void insert(); //done
        void find() const;//done    
        void deleteAddress();//done
        void print() const;//done   
        void load();//done
        void save();//done
        void quit();//done
    private:
        void insertHelper(string firstN, string lastN, 
                          string newAddress, string newPhone);
};

//destructor
Rolodex::~Rolodex()
{
    File * curFile = head;
    while(curFile != NULL)
    {
        curFile = curFile -> nextFile;
        delete head;
        head = curFile;
    }
}

//helper function to insert
void Rolodex::insertHelper(string firstN, string lastN, 
                            string newAddress, string newPhone)
{
    //create new File object to insert
    File * newFile = new File(firstN,lastN,newAddress,newPhone);
    
    /**find the right place to insert the new File**/
    //edge case: empty list where head and tail are null
    //make new File the head and tail of the list
    if(head == NULL)
    {
        head = newFile;
        tail = newFile;
        //~ cout << "Head's Last Name: " << head -> last_name << endl;
        //~ return;
    }
    else if(head-> last_name > lastN)
    {
        newFile -> nextFile = head;
        head = newFile;
    }
    //edge case: newFile should be the new tail
    else if(tail->last_name <= lastN)
    {
        tail -> nextFile = newFile;
        tail = newFile;
    }
    //list already have some files,
    //traverse through the list to find the right place for newFile
    else
    {
        File * trackerFile = NULL;
        
        for(File * curFile = head; curFile != NULL; curFile = curFile-> nextFile)
        {
            //~ cout << "in here?? " << endl;
            trackerFile = curFile -> nextFile;
            if(curFile->last_name <= lastN && 
                lastN <= trackerFile->last_name && trackerFile != NULL)
            {
                curFile -> nextFile = newFile;
                newFile -> nextFile = trackerFile;
                //~ cout << "hello??" << endl;
                break;
            }
        }
    }
}

//insert a new file into rolodex
void Rolodex::insert()
{
    //get info to insert into the rolodex
    string firstN, lastN, newAddress, newPhone;
    cout << "\nInserting a new address into Rolodex \n"
         << "Please enter the following information.\n";
    cout << "First Name: ";
    cin  >> firstN;
    cout << "Last Name: ";
    cin  >> lastN;
    cout << "Address: ";
    cin.ignore(1000,'\n');
    getline(cin,newAddress);
    cout << "Phone: ";
    getline(cin, newPhone);
    cout << endl;
    
    insertHelper(firstN,lastN,newAddress,newPhone);
    
    cout << "Insert File successfully" << endl;
    changed = true;
    
}

//search for an address by last name
void Rolodex::find() const
{
    string searchName, curName;
    bool fileFound = false;
    cout << "Enter Last Name: ";
    cin  >> searchName;
        
    for(File * curFile = head; curFile != NULL; curFile = curFile-> nextFile)
    {
        curName = curFile-> last_name;
        if(curName == searchName)
        {
            cout << "\nFile Found!\n";
            cout << "Name: " << curFile -> first_name 
                 << " " << curFile -> last_name << endl;
            cout << "Address: " << curFile -> address << endl;
            cout << "Phone: " << curFile -> phone << endl;
            cout << "=======================================" << endl << endl;
            fileFound = true;
        }
    }
    if(!fileFound)    
        cout << "File is not in the Rolodex :c\n\n";
    
}

//delete an existing address by last name
void Rolodex::deleteAddress()
{
    string searchName, curName;
    bool fileFound = false;
    cout << "Enter Last Name: ";
    cin  >> searchName;
    
    //edge case: deleting head or 
    //when head and tail are both pointing to the same object
    if(head -> last_name == searchName)
    {
        if(head == tail)
        {
            File * toBeDelete = head;
            head = NULL;
            tail = NULL;
            delete toBeDelete;
            cout << "File deletion successful!\n" << endl;
        }
        else
        {
            File * toBeDelete = head;
            head = head -> nextFile;
            delete toBeDelete;
            cout << "File deletion successful!\n" << endl;
        }
        fileFound = true;
    }
    
    else
    {
        File * lastFile = head;
        for(File * curFile = head -> nextFile; 
            curFile != NULL; 
            curFile = curFile-> nextFile, lastFile = lastFile -> nextFile)
        {
            curName = curFile-> last_name;
            if(curName == searchName)
            {
                //edge case: if deleting the tail file, re-assign tail
                if(curFile == tail)
                {
                    lastFile -> nextFile = NULL;
                    tail = lastFile;
                    delete curFile;
                    cout << "File deletion successful!\n" << endl;
                }
                //redirecting pointers and then delete found file
                else
                {
                    lastFile -> nextFile = curFile -> nextFile;
                    delete curFile;
                    cout << "File deletion successful!\n" << endl;
                }
                fileFound = true;
                break;
            }
        }
    }
    if(!fileFound)    
        cout << "File is not in the Rolodex. \n\n";
        
    changed = true;
}

//print out the rolodex starting from head
void Rolodex::print() const
{
    if(head == tail && head == NULL)
    {
        cout << "Rolodex does not contain any files!\n" << endl;
        return;
    }
    cout << "=======================================" << endl;
    
    File * curFile = NULL;
    for(curFile = head; curFile != NULL; curFile = curFile -> nextFile)
    {
        cout << "Name: " << curFile -> first_name 
             << " " << curFile -> last_name << endl;
        cout << "Address: " << curFile -> address << endl;
        cout << "Phone: " << curFile -> phone << endl;
        cout << "=======================================" << endl << endl;
    }
}

//load an existing rolodex file into the program.
//if current Rolodex is unsaved, ask user to save.
void Rolodex::load()
{
    string fileName;
    string datatype;
    string firstN, lastN, newAddress, newPhone;
    ifstream loadFile;
    
    if(changed)
    {
        string tosave;
        cout << "You have made changes to the Rolodex,"
             << " do you wish to save the Rolodex? (y/n)";
        cin  >> tosave;
        
        while(changed)
        {
            if(tosave == "y" || tosave == "yes")
                save();
            else if (tosave == "n" || tosave == "no")
                break;
            else
                cout << "invalid input" << endl;
        }
    }
    
    cout << "Enter the Name of the file you wish to Load\n";
    cin  >> fileName;
    
    loadFile.open(fileName.c_str() );
    
    //clear current Rolodex
    {
        File * curFile = head;
        while(curFile != NULL)
        {
            curFile = curFile -> nextFile;
            delete head;
            head = curFile;
        }
    }
    
    while(loadFile >> datatype)
    {
        if(datatype == "Name:")
        {
            loadFile >> firstN;
            loadFile >> lastN;
        }
        else if (datatype == "Address:")
            loadFile >> newAddress;
        else if (datatype == "Phone:")
            loadFile >> newPhone;
        else if (datatype == "=======================================")
            insertHelper(firstN,lastN,newAddress,newPhone);
        else if(datatype == "DONE")
        {
            cout << "File load successfully!" << endl;
            return;
        }
    }
    
}

//save the current rolodex into a file
void Rolodex::save()
{
    if(head == NULL)
    {
        cout << "Rolodex is empty, discard attempt to save file" << endl;
        return;
    }
    string fileName;
    cout << "Enter the file name you wish to save Rolodex in: ";
    cin  >> fileName;
    
    ofstream saveFile;
    
    saveFile.open( fileName.c_str() );
    
    for(File * curFile = head; curFile != NULL; curFile = curFile->nextFile )
    {
        saveFile << "Name: " << curFile -> first_name 
                 << " " << curFile -> last_name << endl;
        saveFile << "Address: " << curFile -> address << endl;
        saveFile << "Phone: " << curFile -> phone << endl;
        saveFile << "=======================================" << endl << endl;
    }
    //~ saveFile << "DONE";
    
    saveFile.close();
    
    cout << "File saved successfully!\n" << endl;
    
    changed = false;
}

//exit the program
//ask user to save if there the file is unsaved
void Rolodex::quit()
{
    if(changed)
    {
        string tosave;
        cout << "You have made changes to the Rolodex,"
             << " do you wish to save the Rolodex? (y/n)";
        cin  >> tosave;
        
        while(changed)
        {
            if(tosave == "y" || tosave == "yes")
                save();
            else if (tosave == "n" || tosave == "no")
                break;
            else
                cout << "invalid input" << endl;
        }
        sleep(1);
    }
    cout << "Thank you for using kev's Rolodex!\n"
         << "Have a wonderful day! C:" << endl << endl;
    exit(0);
}



int main()
{
    char command;
    Rolodex rolodex;
    
    cout << "       Welcome to kev's Rolodex" << endl;
    cout << "Please enter a command from the menu\n"
         << "=====================MENU=====================\n"
         << "Insert (i/I)    |   Find (f/F)   |     Delete(d/D)\n"
         << "Print (p/P)     |   Load (l/L)   |     Save(s/S)\n"
         << "Quit (q/Q)" << endl;
    
    while(cin >> command)
    {
        switch(command)
        {
            case 'I' :
            case 'i' :
                rolodex.insert();
                break;
            case 'F' :
            case 'f' :
                rolodex.find();
                break;
            case 'D' :
            case 'd' :
                rolodex.deleteAddress();
                break;
            case 'P' :
            case 'p' :
                rolodex.print();
                break;
            case 'L' :
            case 'l' :
                rolodex.load();
                break;
            case 'S' :
            case 's' :
                rolodex.save();
                break;
            case 'Q' :
            case 'q' :
                rolodex.quit();
                break;
            default :
                cout << "unrecognized command, please enter another\n"
                     << "Insert (i), Find (f), Delete(d), Print(p), Load (l)," 
                     << " Save(s), Quit (q)" << endl;
                break;
        }
        cout << "Please enter a command from the menu\n"
             << "=====================MENU=====================\n"
             << "Insert (i/I)    |   Find (f/F)   |     Delete(d/D)\n"
             << "Print (p/P)     |   Load (l/L)   |     Save(s/S)\n"
             << "Quit (q/Q)" << endl;
    }
    return 0;
}
