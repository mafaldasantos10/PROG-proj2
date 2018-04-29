#include "Board.h"
#include <iostream>
#include<vector>

using namespace std;

Board::Board(unsigned int rows, unsigned int columns)
{

	this-> rows = rows;
	this-> columns = columns;

	/* boardxy.resize(rows, vector<char>(columns ".");
	
	for (int i = 0; i < rows; i++)

		for (int k = 0; k < columns; k++)

			boardxy[i][k].push_back('.');
			
			*/
}

void Board::make()
{

	xy.resize(rows, vector<char>(columns, '.'));

}

void Board::show()
{
	cout << "    ";
	for (int i = 96; i < 96 + columns; i++)
	{
		cout << char(i) << ' ';
	}

	for (int k = 0; k < rows; k++)
	{
		for (int i = 48; i < 48 + rows; i++)
		{
			cout << char(i) << ' ';

		}

		for (int j = 0; j < columns; j++)
		{
			cout << ' ' << xy[k][j];
		}

		cout << ' ' << endl;
	}
		
}