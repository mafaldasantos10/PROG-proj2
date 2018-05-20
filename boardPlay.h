 #ifndef BoardPlay_h
#define BoardPlay_h

#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include "dictionaryPlay.h"

using namespace std;

class BoardPlay
{
public:
	/*
	PURPOSE:
	- board constructor
	PARAMETERS:
	- unsigned int rows: amount of rows indicated by the user
	- unsigned int columns: amount of columns indicated by the user
	*/
	BoardPlay(unsigned int rows, unsigned int columns);

	/*
	PURPOSE:
	- creates a board
	*/
	void make();

	/*
	PURPOSE:
	- shows the current board state
	*/
	void show();

	/*
	/*
	PURPOSE:
	- inserts new words on the board
	PARAMETERS:
	- string position: position given by the user (where the word will be written)
	- string word: word to write
	*/
	void insert(string position, string word); 

	/*
	PURPOSE:
	-  checks if the given word has not been used in that board before
	PARAMETERS:
	- string word: the word writen by the user)
	- vector<string> &placedWords: vector where the previously placed words have been saved (passed by reference
	RETURNS:
	- true if the word still wasn't used, false if it has been used
	*/
	bool notUsedWord(string word);

	/*
	PURPOSE:
	- keeps track of all words and positions, saves the coordenates and words writen by the user in two diferent vectors
	PARAMETERS:
	- string position: the position
	- string word: to be saved
	*/
	void track(string position, string word);

	/*
	PURPOSE:
	- gets a string of the contents of the indicated position of the word
	PARAMETERS:
	- string position: position given by the user (where the word will be written)
	- string word: word to write
	RETURNS:
	- string that is the line extracted from the board where the word will potentially be
	*/
	string getWord(string position, string word);

	/*
	PURPOSE:
	-  removes the word in the coordinate given by the user
	PARAMETERS:
	- string position: position of the word given by the user to delete
	*/
	void remove(string position,vector<string>coordinates,vector<string> words);


	/*
	PURPOSE:
	- saves the board to a text file
	PARAMETERS:
	- string thesaurusFile: the thesaurus file used
	- vector<string> word: vector with the placed words
	- vector<string>coordinates: vector with the coordinates of each placed word
	- string savedFile: the name of the file where the board will be saved
	*/
	void saveFile(string thesaurusFile, vector<string> word, vector<string>coordinates, string savedFile);

	//dictionary class
	DictionaryPlay* newDict;

	/*
	PURPOSE:
	-  sees if the word fits in the position
	PARAMETERS:
	- string position: position given by the user (where the word will be written)
	- string word: word to write
	RETURNS:
	- true if the word fits in the position, false if it doesn't
	*/
	bool fit(string position, string word);

	/*
	PURPOSE:
	- sees if the word matches with the wild card
	PARAMETERS:
	- the word and the wildcard
	RETRURNS;
	- returns a tue bool if it fits
	*/
	bool wildcardMatch(const char *str, const char *strWild);

	/*
	PURPOSE:
	-  where there is a word it puts "." if it ia a # it puts " "
	*/
	void fillSpaces();

	/*
	PURPOSE:
	- sees if all the words in the board are correct
	PARAMETERS:
	- vector<string> &coordinates: vector with the positions of the words that were in the original board
	- vector<string> &placedwords: vector with the words that were in the original board
	RETRURNS;
	- returns true if all words are correct
	*/
	bool checkAnswers(vector<string> &coordinates, vector<string> &placedwords);

	/*
	PURPOSE:
	-  checks if all the spaces in the board are filled
	RETURNS:
	- true if the board is full, false if it isn't
	*/
	bool checkIfFull();

	/*
	PURPOSE:
	-  checks if the indicated position is valid for the word the user wants to place
	PARAMETERS:
	- string position: position given by the user (where the word will be written)
	- string word: word to write
	RETURNS:
	- true if the position is valid, false if it isnt
	*/
	bool validPosition(string word, string position);

	/*
	PURPOSE:
	-  double checks if all the words in the board are valid
	PARAMETERS:
	- map<string, vector<string> > &validWords: the map with all the words
	RETURNS:
	- true if the words are correct, false if they aren't
	*/
	bool doubleValidCheck(map<string, vector<string> > &validWords);
	
private:
	vector < vector <char> > xy; //board

	vector<string> wordCoordinates, //vector that stores the positions of the respective words on the board
	               placedWords; //vector that stores all the words placed on the board

	unsigned int rows, columns; //rows and columns of the board

	string position, word; //position and word of the board
};
#endif