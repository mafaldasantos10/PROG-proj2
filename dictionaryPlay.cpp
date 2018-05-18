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

	this->synonyms;

	
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
				synonyms.push_back(caps(next.substr(0, i)));
				next.erase(next.begin(), next.begin() + (i + 1));
				i = 0;
			}
			if (i == (next.length() - 1))		

			{
				synonyms.push_back(caps(next));
			}
		}

		//cout << synonymes.size() << endl;

		
			validWords.insert(pair <string, vector<string> >(key, synonyms));

		
		synonyms.clear();
		
	}

	fin.close();
}

//writes the words in caps
string DictionaryPlay::caps(string word)
{

	for (unsigned int i = 0; i < word.size(); i++)
	{
		word.at(i) = toupper(word.at(i));
	}
	return word;
}
	
//checks if the word is in the thesaurus file
bool DictionaryPlay::isValid(string word, map<string, vector<string> > &validWords)
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

//gives the user the position and a synonym for the correct word
vector<string> DictionaryPlay::clues(vector<string> &words, vector<string> &coordinates)
{
	this->validWords;
	this->tempCoord;
	this->tempWord;

	cout << endl;
	//writes the horizontal word synonyms
	for (unsigned int i = 0; i < words.size(); i++)
	{
		int randomIndex = rand() % validWords[caps(words.at(i))].size();

		string synonym = validWords[caps(words.at(i))].at(randomIndex);

		//stores vertical words and their position
		tempCoord = coordinates;
		tempWord.push_back(synonym);
	}

	return tempWord;
}
		

		/*
		map<string, vector<string> >::iterator it;
		it = synonym;

		for (unsigned int j = 0; j < validWords[caps(words.at(i))].size(); j++)
		{
			if(validWords[caps(words.at(i))].at(j) == synonym)
			{
			map<string, vector<string> >::iterator it;
			it = validWords.find(caps(words.at(i)));

			validWords.erase(it);
			}

		}*/


void DictionaryPlay::showClues(vector<string> &words, vector<string> &coordinates)
{
	vector<string> synonyms,
		pos,
		vertical;

	synonyms = clues(words,coordinates);

	cout << "Horizontal Words: " << endl;

	for (unsigned int i = 0; i < coordinates.size(); i++)
	{
		char dir = coordinates.at(i).at(2);

		if (dir == 'H')
		{
			string position = coordinates.at(i).erase(2, 1);
			cout << position << "   " << tempWord.at(i) << endl;
		}
		else if (dir == 'V')
		{
			string position = coordinates.at(i).erase(2, 1);
			vertical.push_back(tempWord.at(i));
			pos.push_back(position);
		}
		
	}

	cout << "Vertical words: " << endl;

	//the words that were stored in a temporary vector are now displayed in the vertical words

	for (unsigned int i = 0; i < vertical.size(); i++)
	{
        	string position = coordinates.at(i).erase(2, 1);
			cout << pos.at(i) << "   " << vertical.at(i) << endl;

	}	
}

void DictionaryPlay::synonymHelp(string position, vector<string> &words, vector<string> &coordinates)
{
	for (unsigned int i = 0; i < words.size(); i++)
	{
		int randomIndex = rand() % words.size();

		if (position == coordinates.at(i))
		{
			if (validWords[caps(words.at(i))].size() == 0)
			{
				cout << "There arent any more synonymes for the hiden word" << endl;
			}
			else
			{
				string synonym = validWords[caps(words.at(i))].at(randomIndex);
				cout << "Another synonym for the hiden word: " << synonym << endl;
				validWords.erase(synonym);
				break;
			}
		}
		
	}
}