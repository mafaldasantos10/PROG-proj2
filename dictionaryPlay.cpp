#include "dictionaryPlay.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <stdlib.h>

using namespace std;

DictionaryPlay::DictionaryPlay(string thesaurusFile)
{
	string key;
	ifstream fin;
	int index;
	fin.open(thesaurusFile);

	//checks wether the indicated file is valid
	if (!fin.is_open())
	{
		cerr << "Input file not found!\n";
		exit(1);
	}

	string next;
	string words;

	this->synonymes;


	//extracts the header words to a vector
	while (!fin.eof())
	{
		getline(fin, next);

		for (unsigned int i = 0; i < next.length(); i++)
		{
			//deletes the space in the beggining of the word
			if (next.at(0) == ' ')
			{
				next.erase(0, 1);
			}

			if (next.at(i) == ':')
			{
				key = caps(next.substr(0, i));
				next.erase(next.begin(), next.begin() + (i + 1));
				i = 0;
			}
			if (next.at(i) == ',')
			{
				synonymes.push_back(caps(next.substr(0, i)));
				next.erase(next.begin(), next.begin() + (i + 1));
				i = 0;
			}
			if (i == (next.length() - 1))
			{
				synonymes.push_back(caps(next));
			}
		}

		cout << synonymes.size() << endl;

		if (validWords.count(key) != 0)
		{
			for (unsigned int i = 0; i < synonymes.size(); i++)
				validWords[key].push_back(synonymes[i]);

		}
		else
		{
			validWords.insert(pair <string, vector<string> >(key, synonymes));

		}
		synonymes.clear();

	}

	fin.close();
}

string DictionaryPlay::caps(string word)
{

	for (unsigned int i = 0; i < word.size(); i++)
	{
		word.at(i) = toupper(word.at(i));
	}
	return word;
}
	

bool DictionaryPlay::isValid(string word, map<string, vector<string> > validWords)
{
	bool present = false;
	this->validWords;
	string newWord = caps(word);
	map<string, vector<string> >::iterator it;

	 it = validWords.find(word);
	 if (it != validWords.end())
	 {
		 present = true;
	 }


	return present;
}


void DictionaryPlay::clues(vector<string> words, vector<string> coordinates)
{
	this->validWords;

	for (unsigned int i = 0; i < words.size(); i++)
	{
		if (coordinates.at(i).at(2) == 'V')
		{
			int randomIndex = rand() % words.size();
			cout << "Vertical words: " << endl;

			cout << coordinates.at(i) << "   " << (validWords[words.at(i)]).at(randomIndex) << endl;


		}
		else if (coordinates.at(i).at(2) == 'H')
		{
			int randomIndex = rand() % words.size();
			cout << "Horizontal words: " << endl;
			cout << coordinates.at(i) << "   " << (validWords[words.at(i)]).at(randomIndex) << endl;

		}
	}
}