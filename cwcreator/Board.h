#ifndef Board_h
#define Board_h

#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include "dictionary.h"
#include <map>

using namespace std;

class Board
{
public:
	/*
	PURPOSE:
	 - board constructor
	PARAMETERS:
	 - unsigned int rows: amount of rows indicated by the user
	 - unsigned int columns: amount of columns indicated by the user
	*/
	Board(unsigned int rows, unsigned int columns);

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
	bool notUsedWord(string word, vector<string> &placedWords); 

	/*
	PURPOSE:
	- keeps track of all words and positions, saves the coordinates and words writen by the user in two diferent vectors
	PARAMETERS:
	- string position: the position 
	- string word: to be saved
	*/
	void track(string position, string word);

	/*
	PURPOSE:
	- saves the board to a text file
	PARAMETERS:
	- string thesaurusFile: the thesaurus file used 
	- bool resumedBoard: bool telling wether it has been a previously made and now resumed
	- string savedFile: the name of the file where the board will be saved
	*/
	void saveFile(string thesaurusFile, bool resumedBoard, string savedFile);

	/*
	PURPOSE:
	- sees if the word matches with the wild card
	PARAMETERS:
	- the word and the wildcard
	RETURNS:
	- returns a bool if it fits
	*/
	bool wildcardMatch(const char *str, const char *strWild);

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
	-  removes the word in the coordinate given by the user
	PARAMETERS:
	- string position: position of the word given by the user to delete
	*/
	void remove(string position);

	/*
	PURPOSE:
	-  Gives the user a list of 10 words that fit in the position given
	PARAMETERS:
	- string position: position given by the user (where the user wants help)
	- vector<string> > &validWords: map where all the words are
	*/
	void help(string postion, map<string, vector<string> > &validWords); 

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
	-  checks if all the spaces in the board are filled
	RETURNS:
	- true if the board is full, false if it isn't
	*/
	bool checkIfFull();

	/*
	PURPOSE:
	-  fills the empty spaces with #
	*/
	void fillSpaces();

	/*
	PURPOSE:
	-  double checks if all the words in the board are valid
	PARAMETERS:
	- map<string, vector<string> > &validWords: the map with all the words
	RETURNS:
	- true if the words are correct, false if they aren't
	*/
	bool doubleValidCheck(map<string, vector<string> > &validWords); 

	/*
	PURPOSE:
	-  determines the name of the first available (empty) file usign the name format BXXX.txt
	RETURNS:
	- a string with the file name or a warning
	*/
	string isEmpty(); 

	/*
	PURPOSE:
	-  passes the vector placedWords to MAIN
	RETURNS:
	- the placedWords vector
	*/
	vector<string> Words();

	Dictionary* newDict;
	
private:
	vector < vector <char> > xy; //board

	vector<string> wordCoordinates, //vector that stores the positions of the respective words on the board
	               placedWords, //vector that stores all the words placed on the board
				   validWords;

	unsigned int rows, //rows of the board
		         columns; //columns of the board

	string position, //position of the word
		   word, //given word
		   newWord; //word extracted from the board using the given position and length of the word that is to be placed there
};
#endif
