#ifndef Board_h
#define Board_h
#include<vector>

class Board
{
public:

	Board(unsigned int rows, unsigned int columns);
	void show();
	void make();
	
private:

	vector <vector <char> > xy;
	unsigned int rows, columns;
	

};
#endif