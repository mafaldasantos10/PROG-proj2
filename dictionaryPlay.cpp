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

//gives the user the position and a synonym for the correct word
void DictionaryPlay::clues(vector<string> words, vector<string> coordinates)
{
	this->validWords;
	vector<string> tempCoord;
	vector<string> tempWord;

	cout << endl;
	//writes the horizontal word synonyms
	cout << "Horizontal words: " << endl;

	for (unsigned int i = 0; i < words.size(); i++)
	{
		int randomIndex = rand() % words.size();
	
		if (coordinates.at(i).at(2) == 'V')
		{
			string position = coordinates.at(i).erase(2,1);
			//stores vertical words and their position
			tempCoord.push_back(position);
		    tempWord.push_back(validWords[caps(words.at(i))].at(randomIndex));

		}
		else if (coordinates.at(i).at(2) == 'H')
			
		{
			string position = coordinates.at(i).erase(2,1);
			int randomIndex = rand() % words.size();
			//shows the user the synonyms for the horizontal words
			cout << position << "   " << (validWords[caps(words.at(i))]).at(randomIndex) << endl;
		}
	}
	cout << endl;
	//writes the vertical word synonyms
	cout << "Vertical words: " << endl;
	//the words that were stored in a temporary vector are now displayed in the vertical words
	for (unsigned int i = 0; i < tempCoord.size(); i++)
	{
		cout << tempCoord.at(i).at(0) << tempCoord.at(i).at(1) << "   " << tempWord.at(i) << endl;
	}
}