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
void DictionaryPlay::clues(vector<string> &words)
{
	this->validWords;
	this->tempWord; //stores the synonyms 

	cout << endl;
	tempWord.clear();
	//writes the horizontal word synonyms
	for (unsigned int i = 0; i < words.size(); i++)
	{
		//range for the random index
		int randomIndex = rand() % validWords[caps(words.at(i))].size();

		//random synonym
		string synonym = validWords[caps(words.at(i))].at(randomIndex);

		//stores vertical words and their position
		tempWord.push_back(synonym);
		usedSynonym.push_back(synonym);
	}
}
	
//prints the clues 
void DictionaryPlay::showClues(vector<string> &words, vector<string> &coordinates)
{
	vector<string> pos, //saves the position of the vertical words
		vertical; //saves the vertical words

	//clues(words); 
	
	this->tempWord;

	cout << "Horizontal Words: " << endl;

	for (unsigned int i = 0; i < coordinates.size(); i++)
	{
		//saves the last character (V or H)
		char dir = coordinates.at(i).at(2);

		if (dir == 'H')
		{
			//saves the first two caracters(row and column)
			string position = coordinates.at(i).substr(0, 2);
			cout << position << "   " << tempWord.at(i) << endl;
		}
		else if (dir == 'V')
		{
			//saves the first two caracters(row and column)
			string position = coordinates.at(i).substr(0, 2);

			//saves in a temporary vector with the vertical words synonyms
			vertical.push_back(tempWord.at(i));
			//saves in a temporary vector with the vertical words positions
			pos.push_back(position);
		}
		
	}

	cout << "Vertical words: " << endl;

	//the words that were stored in a temporary vector are now displayed in the vertical words

	for (unsigned int i = 0; i < vertical.size(); i++)
	{
		//using the temporary vectors prints the positio and the synonyms
        	string position = coordinates.at(i).substr(2, 1);
			cout << pos.at(i) << "   " << vertical.at(i) << endl;

	}	
}

//checks if a word has aleady been used
bool DictionaryPlay::notUsedWord (string word, vector<string> &vector)
{
	bool Present = true;

	for (unsigned int i = 0; i < vector.size(); i++)
	{
		//finds the word in the vector
		if (vector.at(i) == word)
		{
			Present = false;
			break;
		}
	}

	return Present;
}

//when the user asks for help prints a new synonym for the word in the given position
void DictionaryPlay::synonymHelp(string position, vector<string> &words, vector<string> &coordinates)
{
	this->usedSynonym;
	for (unsigned int i = 0; i < words.size(); i++)
	{
		//looks in the vector that has the hiden words the index of the writen position
		if (position == coordinates.at(i))
		{
			    int randomIndex = rand() % validWords[caps(words.at(i))].size(); //returns a random index

		         //random synonym acquired with the random index
				string synonym = validWords[caps(words.at(i))].at(randomIndex); 

				    //checks if it has been previously used
					while (notUsedWord(synonym, usedSynonym)) 
					{
						cout << "Another synonym for the hiden word: " << synonym << endl;
						//checks if it has been previously used
						usedSynonym.push_back(synonym);
						break;
					}
					
		}
		
	}
}