#include "dictionaryPlay.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

int main()
{
	//variables
	string thesaurusFile; //file that contains the dictionary
		
	cout << endl
		 << "-------------------------" << endl
		 << "CREATE PUZZLE" << endl
		 << "-------------------------" << endl;

	//-----------------------------------------------------------------
	//END of INTERFACE

	cout << "Thesaurus file name? ";
	cin >> thesaurusFile;

	//vector with the valid words from the thesaurus
	DictionaryPlay dict(thesaurusFile);
	dict.show();
	system("pause");

	return 0;
}

/*
cwcreator
main.cpp
Extraction of a word list from a synonym dictionary
@author Diogo & Mafalda
@version 1.0 29/04/2018
*/