#ifndef Board_h
#define Board_h

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Board
{
public:

	Board(unsigned int rows, unsigned int columns);
	void show(); //shows the current board
	void make(); //creates a board
	void insert(string position, string word); //inserts new words on the board
	
private:
    vector < vector <char> > xy;
	unsigned int rows, columns;
	string position, word;
};
#endif