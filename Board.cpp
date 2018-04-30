#include "Board.h"
#include <iostream>
#include <vector>

using namespace std;

Board::Board(unsigned int rows, unsigned int columns)
{
	this-> rows = rows;
    this-> columns = columns;

}

void Board::make()
{

	xy.resize(rows, vector<char> (columns, '.'));

}

void Board::show()
{
	cout << "   ";
    for (unsigned int i = 97; i < 97 + columns; i++)
    {
        cout << char(i) << ' ';
    }

    cout << endl;

	for (unsigned int k = 0; k < rows; k++)
	{
            cout << char(k + 65) << ' ';

            for (unsigned int j = 0; j < columns; j++)
            {
                cout << ' ' << xy[k][j];
            }
       
		cout << ' ' << endl;
	}   		
}