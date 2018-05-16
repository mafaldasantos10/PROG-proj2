#include "dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

Dictionary::Dictionary(string thesaurusFile)
{
	ifstream fin;

	//opens the thesaurus file
	fin.open(thesaurusFile);

	//checks wether the indicated file is valid
	if (!fin.is_open())
	{
		cerr << "Input file not found!\n";
		exit(1);
	}

	//string that will hold each line
	string next;

	//extracts the header words to a vector
	while (!fin.eof())
	{
		getline(fin, next);

		for (unsigned int i = 0; i < next.length(); i++)
		{
			//extracts all words proceeded by " : "
			if (next.at(i) == ':')
			{
				validWords.push_back(next.substr(0, i)); //places it in the vector
				break; //there's only 1 header word per line
			}
		}
	}

	//closes the input file
	fin.close();
}

//checks if the given word is in the vector holding the words from the thesaurus
bool Dictionary::isValid(string word, vector<string> &validWords)
{
	bool present = false;

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