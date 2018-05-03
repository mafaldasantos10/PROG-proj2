#include "dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

Dictionary::Dictionary(string thesaurusFile)
{
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

	string next;

	while (!fin.eof())
	{
		getline(fin, next);

		for (unsigned int i = 0; i < next.length(); i++)
		{
			if (next.at(i) == ':')
			{
				validWords.push_back(next.substr(0, i));
				break;
			}
		}
	}

	for (unsigned int i = 0; i < validWords.size(); i++)
		cout << validWords.at(i) << endl;
    
	fin.close();
}

bool Dictionary::isValid(string word)
{
	bool present = false;
    this->validWords;

	for (unsigned int i = 0; i < validWords.size(); i++)
	{
		//case insensitive comparison
		if (_strcmpi(word.c_str(), validWords.at(i).c_str()) == 0)
		{
			present = true;
			break;
		}
	}

    return present;
}