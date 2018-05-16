#ifndef Board_h
#define Board_h

#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include "dictionary.h"

using namespace std;

class Board
{
public:
	Board(unsigned int rows, unsigned int columns); //board constructor
	void make(); //creates a board
	void show(); //shows the current board state
	void insert(string position, string word); //inserts new words on the board using the given position and word
	bool notUsedWord(string word); //checks if the given word has not been used in that board before
	void track(string position, string word); //keeps track of all words and positions
	void saveFile(string thesaurusFile); //saves the board
	bool wildcardMatch(const char *str, const char *strWild);
	string getWord(string position, string word); //gets a string of the contents of the indicated position of the word
	bool validPosition(string word, string position); //checks if the indicated position is valid for the word the user wants to place
	void remove(string position); //removes the word in the coordinate given by the user
	void help(string postion, vector<string> &validWords); //Gives the user a list of 10 words that fit in the position given
	bool fit(string position, string word); //sees if the word fits in the position
	bool checkIfFull(); //checks if all the spaces in the board are filled
	void fillSpaces(); //fills the empty spaces
	bool doubleValidCheck(vector<string> &validWords); //double checks if all the words in the board are valid
	string isEmpty(); //determines the name of the first available (empty) file usign the name format BXXX.txt
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