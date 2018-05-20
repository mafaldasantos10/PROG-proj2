#include "dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <stdlib.h>

using namespace std;

//extrats the words from the file and saves the word and synonyms in a map  
Dictionary::Dictionary(string thesaurusFile)
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
string Dictionary::caps(string word)
{

	for (unsigned int i = 0; i < word.size(); i++)
	{
		word.at(i) = toupper(word.at(i));
	}
	return word;
}

//checks if the word is in the thesaurus file
bool Dictionary::isValid(string word, map<string, vector<string> > validWords)
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
