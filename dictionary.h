#ifndef dictionary_h
#define dictionary_h

#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Dictionary
{
public:
	/*
	PURPOSE:
	-  constructor, saves the words from the file in a map and checks if the file is valid
	PARAMETERS:
	- string thesaurusFile: file that contains the thesaurus
	*/
	Dictionary(string thesaurusFile);

	/*
	PURPOSE:
	-  validates the word inputed by the user by checking if it's in the map containing the valid words
	PARAMETERS:
	- string word: the word given by the user
	- map<string, vector<string> > validWords): the map with the valid words
	RETURNS:
	- true if the word is in the map, false if it isn't
	*/
	bool isValid(string word, map<string, vector<string> > validWords); 

	map<string, vector<string> > validWords;

	/*
	PURPOSE:
	-  puts all the letters of the word in capital letters
	PARAMETERS:
	- string word: the word to put in capital letters
	RETURNS:
	- the word in capital letters
	*/
	string caps(string word);

private:
	vector<string> synonyms; //saves the synonyms of the word in question
};
#endif