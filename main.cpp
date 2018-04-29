#include "dictionary.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	//variables
	string thesaurusFile; //file that contains the dictionary
		   //wordFile; //file that will store the processed word list

	cout << "Thesaurus file? ";
	cin >> thesaurusFile;

	//class
	Dictionary dict(thesaurusFile);

	cout << dict.isValid("antonio");

	return 0;
}


/*
cwcreator
main.cpp
Extraction of a word list from a synonym dictionary

@author Diogo & Mafalda
@version 1.0 29/04/2018
*/