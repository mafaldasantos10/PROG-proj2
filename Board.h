#ifndef Board_h
#define Board_h

#include <iostream>
#include <vector>

using namespace std;

class Board
{
public:

	Board(unsigned int rows, unsigned int columns);
	void show();
	void make();
	void insert();
	
private:
    vector < std::vector <char> > xy;
	unsigned int rows, columns;
};
#endif