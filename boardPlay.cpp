#include "BoardPlay.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h> 
#include "dictionaryPlay.h"
#include <iomanip>

using namespace std;

//constructor
BoardPlay::BoardPlay(unsigned int rows, unsigned int columns)
{
	this->rows = rows;
	this->columns = columns;
}

//makes a new empty board with the indicated size
void BoardPlay::make()
{
	xy.resize(rows, vector<char>(columns, '.'));
}

//shows the current board
void BoardPlay::show()
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
			cout << ' ' << xy.at(k).at(j);
		}

		cout << ' ' << endl;
	}
}

void BoardPlay::insert(string position, string word)
{
	char upperCase = position.at(0), lowerCase = position.at(1), orientation = position.at(2);
	unsigned int uC = ((int)upperCase - 'A'), lC = ((int)lowerCase - 'a');

	//vertically
	if (orientation == 'V')
	{
		for (unsigned int i = uC, k = 0, j = lC; k < word.length(); i++, k++)
		{
			xy.at(i).at(j) = toupper(word.at(k)); //capitalizes the string
		}

		//places a # before
		if ((uC != 0) && (xy.at(uC - 1).at(lC) == '.'))
			xy.at(uC - 1).at(lC) = '#';
		//places a # after
		if (((uC + word.length()) < rows) && (xy.at(uC + word.length()).at(lC) = '.'))
			xy.at(uC + word.length()).at(lC) = '#';
	}
	//horizontally
	else
	{
		for (unsigned int i = uC, k = 0, j = lC; k < word.length(); j++, k++)
		{
			xy.at(i).at(j) = toupper(word.at(k)); //capitalizes the string
		}

		//places a # before
		if ((lC != 0) && (xy.at(uC).at(lC - 1) == '.'))
			xy.at(uC).at(lC - 1) = '#';
		//places a # after
		if (((lC + word.length()) < columns) && (xy.at(uC).at(lC + word.length()) == '.'))
			xy.at(uC).at(lC + word.length()) = '#';
	}
}

void BoardPlay::fillSpaces()
{
	this->xy;
	this->rows;
	this->columns;

	for (unsigned int r = 0; r < rows; r++)
	{
		for (unsigned int c = 0; c < columns; c++)
		{
			//searches for empty spaces
			if (xy.at(r).at(c) <= 'Z' && xy.at(r).at(c) >= 'A')
			{
				//places a % in that space
				xy.at(r).at(c) = '%';
			}

			else
			{
				xy.at(r).at(c) = '.';
			}

		}
	}
}

void BoardPlay::upload()
{
	this->wordCoordinates;
	this->placedWords;

	xy.clear();
	make();

	for (unsigned int j = 0; j < placedWords.size(); j++)
	{
		//rewrites the words that are left in the vector in the board
		insert(wordCoordinates.at(j), placedWords.at(j));
	}
	cout << endl;
	cout << endl;

	fillSpaces();
	//displays the board
	show();

}