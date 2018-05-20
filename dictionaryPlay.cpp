#include "dictionaryPlay.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <stdlib.h>

using namespace std;

//extrats the words from the file and saves the word and synonyms in a map  
DictionaryPlay::DictionaryPlay(string thesaurusFile)
{
	string key; // string of map that will hold the words to put in the board
	ifstream fin;

	//opens the dictionary
	fin.open(thesaurusFile);

	//checks wether the indicated file is valid
	if (!fin.is_open())
	{
		cerr << "Input file not found!\n";
		exit(1);
	}

	string next; //line from the file

				 //header file vector that will save the synonymes for each key taken from the dictionary file
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

			//takes the key from the file 
			if (next.at(i) == ':')
			{
				key = caps(next.substr(0, i));
				//erases the key and the ":"and the space after
				next.erase(next.begin(), next.begin() + (i + 1));
				i = 0;
			}
			//takes the synonyms from the file, they are found by the "," after
			if (next.at(i) == ',')
			{
				synonyms.push_back(caps(next.substr(0, i)));
				//erases the "," and the space after
				next.erase(next.begin(), next.begin() + (i + 1));
				//restores the index in order to also put in vector the synonyms that follow
				i = 0;
			}
			//takes the last word of the line that is also a synonym
			if (i == (next.length() - 1))
			{
				//adds it to the vector
				synonyms.push_back(caps(next));
			}
		}
		// puts bothe synonyms and the key in a map
		validWords.insert(pair <string, vector<string> >(key, synonyms));
		//clears the vector to restart the process in the next line
		synonyms.clear();
	}
	//closes the file
	fin.close();
}

//writes the words in caps
string DictionaryPlay::caps(string word)
{
	//searches in the string word
	for (unsigned int i = 0; i < word.size(); i++)
	{
		//for each position putas te letter in capital letters
		word.at(i) = toupper(word.at(i));
	}
	return word;
}
	
//checks if the word is in the thesaurus file
bool DictionaryPlay::isValid(string word, map<string, vector<string> > &validWords)
{
	//will check if the word is in the synonym dictionary
	bool present = false; 
	//map
	this->validWords;
	//user a previous function to creat a new string that is the word all writen in capitals
	string newWord = caps(word);
	//iterator the validWords map
	map<string, vector<string> >::iterator it;

	//finds the newWord in the map
	 it = validWords.find(word);
	 //if the word is in the map
	 if (it != validWords.end())
	 {
		 //it is present
		 present = true;
	 }

	return present;
}

//gives the user the position and a synonym for the correct word
void DictionaryPlay::clues(vector<string> &words)
{
	this->validWords; // map
	this->tempWord; //stores the synonyms 
	this->SynonymsVec; //stores the synoyms from map

	//map iterator it
	map<string, vector<string> >::iterator it;

	cout << endl;
	//everytime the function is used the vector is empty
	tempWord.clear();

	//writes the horizontal word synonyms
	for (unsigned int i = 0; i < words.size(); i++)
	{
		//looks in the map for the hiden word in that position 
		it = validWords.find(caps(words.at(i)));
		if (it != validWords.end())
		{
			//transfers the vector of the map for another vector
			SynonymsVec = it->second;

			//range for the random index
			int randomIndex = rand() % SynonymsVec.size();

			//random synonym
			string synonym = SynonymsVec.at(randomIndex);

			//stores vertical words and their position
			tempWord.push_back(synonym);

			//erases the synonym that has been saved to the vector so it cant be used again
			SynonymsVec.erase(SynonymsVec.begin() + randomIndex);

			//saves the vector without the synonym in the map
			it->second = SynonymsVec;
			
		}
	}
}
	
//prints the clues 
void DictionaryPlay::showClues(vector<string> &words, vector<string> &coordinates)
{
	vector<string> pos, //saves the position of the vertical words
		vertical; //saves the vertical words 
	
	//synonym vector with the synonyms that where added in the clue function
	this->tempWord;
	
	cout << "Horizontal Words: " << endl;

	for (unsigned int i = 0; i < coordinates.size(); i++)
	{
		//saves the last character (V or H)
		char dir = coordinates.at(i).at(2);

		//checks if the word is horizontal
		if (dir == 'H')
		{
			//saves the first two caracters(row and column)
			string position = coordinates.at(i).substr(0, 2);

			//shows the position and the synonyms of the horizontal words
			cout << position << "   " << tempWord.at(i) << endl;
		}
		//checks if the word is vertical
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

			//shows the position and the synonym
			cout << pos.at(i) << "   " << vertical.at(i) << endl;

	}	
}

//checks if a word has aleady been used
bool DictionaryPlay::notUsedWord (string word, vector<string> &vector)
{
	//checks is the word is in the vector
	bool Present = true;

	//searches in the vector
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		//searches for the word in the vector
		if (vector.at(i) == word)
		{
			//if the word is present it has already been used
			Present = false;
			break;
		}
	}

	return Present;
}

//when the user asks for help prints a new synonym for the word in the given position
void DictionaryPlay::synonymHelp(string position, vector<string> &words, vector<string> &coordinates)
{
	//vector that will store the synonyms in map
	this->SynonymsVec;

	//map iterator
	map<string, vector<string> >::iterator it;

	//searches in the xoordinates vector
		for (unsigned int i = 0; i < coordinates.size(); i++)
		{
			if (position == coordinates.at(i))
			{
				
					//looks in the map for the hiden word in that position 
					it = validWords.find(caps(words.at(i)));
					//if the hiden word is there
					if (it != validWords.end())
					{
						//transfers the vector of the map for another vector
						SynonymsVec = it->second;

						//checks if it is empty
						if (SynonymsVec.empty())
						{
							//doent show a synonym
							cout << endl << "There aren't more clues to show!" << endl;
							break;	
						}
						else
						{
							//returns a random index not over the amount od synonyms in the vector
							int randomIndex = rand() % SynonymsVec.size(); 

							//random synonym acquired with the random index
							string synonym = SynonymsVec.at(randomIndex);

							//shows the synonym
							cout << endl << "Another synonym for the hiden word: " << synonym << endl;

							//erases the shown synonym from the vector so it cant be used again
							SynonymsVec.erase(SynonymsVec.begin() + randomIndex);
							//puts the synonymsVec back on the map
							it->second = SynonymsVec;
							break;
						}
	
					}
				
			}
		}
		
	
}