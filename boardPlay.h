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
	- rows and columns that are asked to the user in main
	RETRURNS;
	- doesnt return anything
	*/
	BoardPlay(unsigned int rows, unsigned int columns);

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
	-creates a board
	PARAMETERS:
	- no parameters
	RETRURNS;
	- doesnt return anything
	*/
	void make();

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
	- a word (the word writen by the user) 
	RETRURNS;
	- true if the word still wasnt used, false it has been used
	*/
	bool notUsedWord(string word);

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
	- gets a string of the contents of the indicated position of the word
	PARAMETERS:
	- word and position writen by the user
	RETRURNS;
	- string that is the line where the word could be
	*/
	string getWord(string position, string word);

	/*
	PURPOSE:
	-  removes the word in the coordinate given by the user
	PARAMETERS:
	- position of the word given by the user to delete, vectors with the words and position taken from the file with the board
	RETRURNS;
	-  doesnt return anything
	*/
	void remove(string position,vector<string>coordinates,vector<string> words);

	/*
	PURPOSE:
	- saves the board
	PARAMETERS:
	- the dictionary file, a bool from main, the name of the file where the board will be saved
	RETRURNS;
	- doesnt return anything
	*/
	void saveFile(string thesaurusFile, vector<string> word, vector<string>coordinates, string savedFile);

	//dictionary class
	DictionaryPlay* newDict;


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
	- sees if the word matches with the wild card
	PARAMETERS:
	- the word and the wildcard
	RETRURNS;
	- returns a tue bool if it fits
	*/
	bool wildcardMatch(const char *str, const char *strWild);

	/*
	PURPOSE:
	-  where ther is a word it puts "." if it ia a # it puts " "
	PARAMETERS:
	- no parameters
	RETRURNS;
	- doesnt return anything
	*/
	void fillSpaces();

	/*
	PURPOSE:
	- sees if all the words in the board are correct
	PARAMETERS:
	- the vectors with the position and words the where in the board file
	RETRURNS;
	- returns a bool if it fits
	*/
	bool checkAnswers(vector<string> &coordinates, vector<string> &placedwords);

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
	-  checks if the indicated position is valid for the word the user wants to place
	PARAMETERS:
	- word and position writen by the user
	RETRURNS;
	- true if the position is valid, false if it isnt
	*/
	bool validPosition(string word, string position);

	/*
	PURPOSE:
	-  double checks if all the words in the board are valid
	PARAMETERS:
	- the map with allthe words
	RETRURNS;
	- true if the words are correct, false if they arent
	*/
	bool doubleValidCheck(map<string, vector<string> > &validWords);
	
private:
	vector < vector <char> > xy; //board
	vector<string> wordCoordinates; //vector that stores the positions of the respective words on the board
	vector<string> placedWords; //vector that stores all the words placed on the board
	unsigned int rows, columns; //rows and columns of the board
	string position, word; //position and word of the board
};
#endif