#include "Board.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//constructor
Board::Board(unsigned int rows, unsigned int columns)
{
	this->rows = rows;
	this->columns = columns;
}

//makes a new empty board with the indicated size
void Board::make()
{
	xy.resize(rows, vector<char>(columns, '.'));
}

//shows the current board
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
			cout << ' ' << xy.at(k).at(j);
		}

		cout << ' ' << endl;
	}
}

//checks if the word is not being used again
bool Board::notUsedWord(string word)
{
	this->placedWords;

	bool Present = true;

	for (unsigned int i = 0; i < placedWords.size(); i++)
	{
		if (placedWords.at(i) == word)
		{
			Present = false;
			cout << "----------------------------------------" << endl << endl;
			cout << endl << "You already used that word. Try another!" << endl << endl;
			break;
		}
	}

	return Present;
}

//keeps track of all words and positions
void Board::track(string position, string word)
{
	wordCoordinates.push_back(position);
	placedWords.push_back(word);
}

//saves the board
void Board::saveFile(string thesaurusFile)
{
	this->placedWords;
	this->wordCoordinates;

	ofstream fout; //fout
	fout.open("b001.txt");

	fout << thesaurusFile << endl << endl;

	for (unsigned i = 0, j= 0; i < wordCoordinates.size(), j < placedWords.size(); i++, j++)
	{
		fout << wordCoordinates.at(i) << "  " << placedWords.at(j) << endl;
	}

	fout.close();
}

//inserts words in the board
void Board::insert(string position, string word)
{
	// stop
	//if (word == crtl-z)

	char upperCase = position.at(0), lowerCase = position.at(1), orientation = position.at(2);
	unsigned int uC = ((int)upperCase - 'A'), lC = ((int)lowerCase - 'a');

	/////create function just for this
	//verify size
	if ( ((uC + word.length()) > rows) || (( lC + word.length()) > columns) )
	{
		cerr << endl << "That word does not fit in the place you want. Try again!" << endl << endl;
		exit(1);
	}
	//valid size
	else
	{
		if (orientation == 'V')
		{
			for (unsigned int i = uC, k = 0, j = lC; k < word.length(); i++, k++)
			{
				xy.at(i).at(j) = toupper(word.at(k)); //capitalizes the string
			}
		}
		else
		{
			for (unsigned int i = uC, k = 0, j = lC; k < word.length(); j++, k++)
			{
				xy.at(i).at(j) = toupper(word.at(k)); //capitalizes the string
			}
		}
	}
}