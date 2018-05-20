#ifndef dictionaryPlay_h
#define dictionaryPlay_h

#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class DictionaryPlay
{
public:
	/*
	PURPOSE:
	-  constructor, saves the words from the file in a map and checks if the file is valid
	PARAMETERS:
	- string thesaurusFile: file that contains the thesaurus
	*/
	DictionaryPlay(string thesaurusFile);

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

	/*
	PURPOSE:
	-  puts all the letters of the word in capital letters
	PARAMETERS:
	- string word: the word to put in capital letters
	RETURNS:
	- the word in capital letters
	*/
	string caps(string word);

	/*
	PURPOSE:
	- gives clues (synonyms) of the words in the board
	PARAMETERS:
	- vector<string> &words: vector with the words on the board
	*/
	void clues(vector<string> &words);

	/*
	PURPOSE:
	- helps the user by giving another synonym of the word on the board
	PARAMETERS:
	- string position: position of the word that the user wants some help to find
	- vector<string> &words: vector with the words on the board
	- vector<string> &coordinates: vector with the coordinates of the words on the board
	*/
	void synonymHelp(string position,vector<string> &words, vector<string> &coordinates);

	/*
	PURPOSE:
	- shows the clues of the words on the board
	PARAMETERS:
	- vector<string> &words: vector with the words on the board
	- vector<string> &coordinates: vector with the coordinates of the words on the board
	*/
	void showClues(vector<string> &words, vector<string> &coordinates);

	/*
	PURPOSE:
	- checks if that specific clue wan't already given
	PARAMETERS:
	- string word: time when the user started playing
	- vector<string> &vector: time when the user finished playing //////////////////////////////////////// this one help

	*/
	bool notUsedWord(string word, vector<string> &vector);

	map<string, vector<string> > validWords;

private:
	vector<string> synonyms, // vector that saves all tthe synonymes from the class to put in map
		           tempWord, // saves a random synonym of the words stores in the mains vector placed Words
		           SynonymsVec; // stores the synonyms that have already been used
};
#endif