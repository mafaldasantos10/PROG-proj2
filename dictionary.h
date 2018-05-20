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
	- the synonym file
	RETRURNS;
	- doesnt return anything
	*/
	Dictionary(string thesaurusFile); //constructor of the vector with the valid words from the thesaurus

	/*
	PURPOSE:
	-  validates the word inputed by the user by checking if it's in the map containin the valid words
	PARAMETERS:
	- the word given by the user and the map with the valid words
	RETRURNS;
	- true if the word is in the map, false if it isnt
	*/
	bool isValid(string word, map<string, vector<string> > validWords); 

	map<string, vector<string> > validWords;

	/*
	PURPOSE:
	-  puts all the letters of the word in capital letters
	PARAMETERS:
	- the word to put in capital letters
	RETRURNS;
	- the word in capital letters
	*/
	string caps(string word);

private:

	vector<string> synonyms; //saves the synonyms of the word in question
};
#endif