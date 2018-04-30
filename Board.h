#ifndef Board_h
#define Board_h

#include <iostream>
#include <vector>


class Board
{
public:

	Board(unsigned int rows, unsigned int columns);
	void show();
	void make();
	
private:
    std::vector < std::vector <char> > xy;
	unsigned int rows, columns;
	
};
#endif