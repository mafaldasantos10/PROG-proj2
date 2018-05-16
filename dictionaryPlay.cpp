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


	//extracts the header words to a vector
	while (!fin.eof())
	{
		getline(fin, next);
		index = 0;
		for (unsigned int i = 0; i < next.length(); i++)
		{
			if (next.at(i) == ':')
			{
				//validWords.push_back(next.substr(0, i));
				key = caps(next.substr(0, i));
				index = i + 2;
				break;
			}
			if (next.at(i) == ',')
			{
				synonymes.push_back(next.substr(index, (next.find_first_of(',') - index)));
				index = i + 2;
			}
		}
		if (validWords.count(key) != 0)
		{
			for (size_t i = 0; i < synonymes.size(); i++)
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