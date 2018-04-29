#include "dictionary.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	//variables
	string thesaurusFile, //file that contains the dictionary
		   wordFile; //file that will store the processed word list

	cout << "Thesaurus file? ";
	cin >> thesaurusFile;

	ifstream fin;
	fin.open(thesaurusFile);

	//checks wether the indicated file is valid
	if (!fin.is_open())
	{
		cerr << "Input file not found!\n";
		exit(1);
	}

	/////////////////////////////////////////////
	/*
	cout << "Word list file? ";
	cin >> wordFile;

	ofstream fout; //fout
	fout.open(wordFile);

	//checks wether the indicated file is valid
	if (!fout.is_open())
	{
		cerr << "Output file opening failed.\n";
		exit(2);
	}
	*/

	//class
	Dictionary dictionary(fin);

	fin.close();
	//fout.close();

	return 0;
}


/*
cwcreator
main.cpp
Extraction of a word list from a synonym dictionary

@author Diogo & Mafalda
@version 1.0 29/04/2018
*/