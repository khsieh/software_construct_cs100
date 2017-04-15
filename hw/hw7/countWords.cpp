//countWords.cpp
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

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <iterator>

using namespace std;

void make_exlcue_set(set<string> & s){
	string word, excludeFileName;
	ifstream in;
	cout << "Please enter the Exclude Words file name: ";
	cin >> excludeFileName;
	in.open(excludeFileName.c_str());
	while(in){
		in >> word;
		s.insert(word);
	}
	in.close();

}

void make_map(map<string,int> & m, const set<string> & s){
	cout << "Please enter the file name: ";
	string inFileName, input;
	cin >> inFileName;
	ifstream in;
	in.open(inFileName.c_str());

	while(in >> input){
		if(s.find(input) == s.end()){
			map<string, int>::iterator index = m.find(input);
			if( index == m.end()){
				pair<string, int> newpair;
				newpair = make_pair(input, 1);
				m.insert(newpair); //insert new pair in map
			}
			else{ //already exist in map, increment counter
				(index -> second)++;
			}
		} 
	}

	in.close();
}

ostream & operator << ( ostream &out, const set<string> & s){
	for(set<string>::iterator i = s.begin(); i != s.end(); ++i){
		out << *i << " ";
	}
	return out;
}

ostream & operator << ( ostream &out, const map<string, int> & m){
	// for(map<string,int>::iterator i = m.begin(); i != m.end(); ++i){
	for(map<string,int>::const_iterator i = m.begin(); i != m.end(); ++i){
		out << "\""<< i -> first << "\" appeared " 
			<< i -> second << " time(s)" << endl;
	}
	return out;
}

int main(){
	
	set<string> excludedWords;
	make_exlcue_set(excludedWords);

	map<string,int> wordsFrequency;
	make_map(wordsFrequency, excludedWords);
	cout << "Words Counted, Words: Frequency\n";
	cout << wordsFrequency;

	return 0;
}
