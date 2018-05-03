#ifndef Board_h
#define Board_h

#include <iostream>
#include <vector>
#include <string>
#include "dictionary.h"

using namespace std;

class Board
{
public:

	Board(unsigned int rows, unsigned int columns);
	void show(); //shows the current board
	void make(); //creates a board
	void insert(string position, string word); //inserts new words on the board
	bool notUsedWord(string word);
	void track(string position, string word);
	void saveFile(string thesaurusFile);
	//void occupied(string position, string word);
	bool wildcardMatch(const char *str, const char *strWild);
	Dictionary* newDict;
	string getWord(string position, string word);
	bool validPosition(string word, string position);
	void remove(string word);

private:
	vector < vector <char> > xy; //board
	vector<string> wordCoordinates; //vector that stores the positions of the respective words on the board
	vector<string> placedWords; //vector that stores all the words placed on the board
	unsigned int rows, columns;
	string position, word;
	string newWord;
};
#endif