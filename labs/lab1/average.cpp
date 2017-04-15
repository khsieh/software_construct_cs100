// Kevin Hsieh SID: 861054367
// Kevin Do SID: 861069832
//section 22

/* ex1
 * This program reads in a list of grades, calculates the average, and prints it to the terminal. 
 * Create your own inputs to test the program and make sure it runs correctly.
*/

#include <iostream>
#include <iomanip>
#include <fstream>

int main()
{
   int grade;
   int numberOfGrades = 0;   // number of grades set to zero
   int totalGrades = 0; //total grades set to zero
   float averageGrade;
   std::ifstream inputFile;

   const int SENTINEL = -999;

//  open the input file
   inputFile.open("gradesen.dat");

//  read in the grades, total them, and count how many grades there are
//  stop the loop when the sentinel is read
   inputFile >> grade;
   while (grade != SENTINEL)
   {
      std::cout << "Grade is:  " << grade << std::endl;
      totalGrades = totalGrades + grade;
      numberOfGrades = numberOfGrades + 1;
      inputFile >> grade;
   }

//  calculate and print the average
   averageGrade = static_cast<float>(totalGrades) / numberOfGrades; 
                //static cast one of the values so it does not get truncated
   std::cout << std::setiosflags(std::ios::fixed);
   std::cout << std::setiosflags(std::ios::showpoint);
   std::cout << std::setprecision(1);
   std::cout << "The average grade for the exam is :  " << averageGrade 
             << std::endl;
        //added std:: to objects because there is no namespace declared
}
