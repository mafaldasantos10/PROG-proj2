#include "dictionaryPlay.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

DictionaryPlay::DictionaryPlay(string thesaurusFile)
{
	ifstream fin;
	fin.open(thesaurusFile);

	//checks wether the indicated file is valid
	if (!fin.is_open())
	{
		cerr << "Input file not found!\n";
		exit(1);
	}

	string next;

	//extracts the header words to a vector
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

		while (next.find_first_of(",") != -1)
		{
			next.erase(0, next.find(":"));
			synonymes.push_back(next.substr(0, next.find_first_of(",")));
			next.erase(0, next.find_first_of(","));
		}

	}

	fin.close();
}

bool DictionaryPlay::isValid(string word, vector<string> validWords)
{
	bool present = false;
	// this->validWords;

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

void DictionaryPlay::show()
{
	this->synonymes;
	for (unsigned int i = 0; i < synonymes.size(); i++)
	{
		cout << synonymes.at(i) << endl;
	}

}