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
	 - rows and columns that are asked to the user in main
	RETRURNS;
	 - doesnt return anything
	*/
	Board(unsigned int rows, unsigned int columns);

	/*
	PURPOSE:
	-creates a board
	PARAMETERS:
	- no parameters
	RETRURNS;
	- doesnt return anything
	*/
	void make();

	/*
	PURPOSE:
	- shows the current board state
	PARAMETERS:
	- no parameters
	RETRURNS;
	- doesnt return anything
	*/
	void show();

	/*
	PURPOSE:
	- inserts new words on the board 
	PARAMETERS:
	- position given by the user (where the word will be written) and the word to write
	RETRURNS;
	- doesnt return anything
	*/
	void insert(string position, string word); 

	/*
	PURPOSE:
	-  checks if the given word has not been used in that board before
	PARAMETERS:
	- a word (the word writen by the user) and a vector where the previously placed words have been saved
	RETRURNS;
	- true if the word still wasnt used, false it has been used
	*/
	bool notUsedWord(string word, vector<string> &placedWords); 

	/*
	PURPOSE:
	- keeps track of all words and positions, saves the coordenatates and words writen by the user in two diferent vectors
	PARAMETERS:
	- the position and word to be saved
	RETRURNS;
	- doesnt return anything
	*/
	void track(string position, string word);

	/*
	PURPOSE:
	- saves the board
	PARAMETERS:
	- the dictionary file, a bool from main, the name of the file where the board will be saved
	RETRURNS;
	- doesnt return anything
	*/
	void saveFile(string thesaurusFile, bool resumedBoard, string savedFile);

	/*
	PURPOSE:
	- sees if the word matches with the wild card
	PARAMETERS:
	- the word and the wildcard
	RETRURNS;
	- returns a bool if it fits
	*/
	bool wildcardMatch(const char *str, const char *strWild);

	/*
	PURPOSE:
	- gets a string of the contents of the indicated position of the word
	PARAMETERS:
	- word and position writen by the user
	RETRURNS;
	- string that is the line where the word could be
	*/
	string getWord(string position, string word); 

	/*
	PURPOSE:
	-  checks if the indicated position is valid for the word the user wants to place
	PARAMETERS:
	- word and position writen by the user
	RETRURNS;
	- true if the position is valid, false if it isnt
	*/
	bool validPosition(string word, string position); 

	/*
	PURPOSE:
	-  removes the word in the coordinate given by the user
	PARAMETERS:
	- position of the word given by the user to delete
	RETRURNS;
	-  doesnt return anything
	*/
	void remove(string position);

	/*
	PURPOSE:
	-  Gives the user a list of 10 words that fit in the position given
	PARAMETERS:
	- position where the user asks for help and the map where all the words are
	RETRURNS;
	-  doesnt return anything
	*/
	void help(string postion, map<string, vector<string> > &validWords); 

	/*
	PURPOSE:
	-  sees if the word fits in the position
	PARAMETERS:
	- position and word given by the user
	RETRURNS;
	- true if the word fits in the position, false if it doesnt
	*/
	bool fit(string position, string word); 

	/*
	PURPOSE:
	-  checks if all the spaces in the board are filled
	PARAMETERS:
	- no parameters
	RETRURNS;
	- true if the board is full, false if it isnt
	*/
	bool checkIfFull();

	/*
	PURPOSE:
	-  fills the empty spaces with #
	PARAMETERS:
	- no parameters
	RETRURNS;
	- doesnt return anything
	*/
	void fillSpaces();

	/*
	PURPOSE:
	-  double checks if all the words in the board are valid
	PARAMETERS:
	- the map with allthe words
	RETRURNS;
	- true if the words are correct, false if they arent
	*/
	bool doubleValidCheck(map<string, vector<string> >&validWords); 

	/*
	PURPOSE:
	-  determines the name of the first available (empty) file usign the name format BXXX.txt
	PARAMETERS:
	- no parameters
	RETRURNS;
	- a string with the file name
	*/
	string isEmpty(); 

	/*
	PURPOSE:
	-  passes the vector placedWords to main
	PARAMETERS:
	- no parameters
	RETRURNS;
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