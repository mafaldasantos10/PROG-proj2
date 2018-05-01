#include "dictionary.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	//variables
	string thesaurusFile; //file that contains the dictionary
		   //wordFile; //file that will store the processed word list
	int rows, columns, option;

	//INTERFACE
	//-----------------------------------------------------------------

	cout << "CROSSWORDS PUZZLE CREATOR" << endl
		<< "=========================" << endl << endl
		<< "Position (RCD / CTRL-Z = STOP)" << endl
		<< " -RCD stands for Row, Column and Direction" << endl << endl
		<< "-------------------------" << endl
		<< "OPTIONS:" << endl
		<< " 1 -  Create Puzzle" << endl
		<< " 2 - Resume Puzzle" << endl
		<< " 0 - Exit" << endl << endl
		<< "Option? ";

	cin >> option;

	cout << endl
		 << "-------------------------" << endl
		 << "CREATE PUZZLE" << endl
		 << "-------------------------" << endl;

	//-----------------------------------------------------------------

	cout << "Thesaurus file name? ";
	cin >> thesaurusFile;

	Dictionary dict(thesaurusFile);

	//test
	cout << dict.isValid("antonio") << endl;

	cout << "Board size (rows, columns)? ";
	cin >> rows >> columns;

	Board brd(rows, columns);
	brd.make();
	brd.show();

	return 0;
}

/*
cwcreator
main.cpp
Extraction of a word list from a synonym dictionary

@author Diogo & Mafalda
@version 1.0 29/04/2018
*/