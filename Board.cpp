#include "Board.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h> 
#include "dictionary.h"

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
			cout << endl << "----------------------------------------" << endl << endl;
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

	//saves the current board into a file
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < rows; j++)
		{
			fout << xy.at(i).at(j) << " ";
		}

		fout << endl;
	}

	fout << endl;

	//saves the respective positions and words on the board
	for (unsigned i = 0; i < wordCoordinates.size(); i++)
	{
		fout << wordCoordinates.at(i) << "  " << placedWords.at(i) << endl;
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

bool Board::wildcardMatch(const char *str, const char *strWild)
{
	// We have a special case where string is empty ("") and the mask is "*".

	while (*strWild)
	{
		// Single wildcard character
		if (*strWild == '?')
		{
			// Matches any character except empty string
			if (!*str)
				return false;
			// OK next
			++str;
			++strWild;
		}
		else if (*strWild == '*')
		{
			// 1. The wildcard * is ignored.
			// So just an empty string matches. This is done by recursion.

			if (wildcardMatch(str, strWild + 1))
				// we have a match and the * replaces no other character
				return true;

			if (*str && wildcardMatch(str + 1, strWild))
				return true;
			// Nothing worked with this wildcard.
			return false;
		}
		else
		{
			// Standard compare of 2 chars. Note that *str might be 0 here,
			// that has always a value while inside this loop.
			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	// Have a match? Only if both are at the end...
	return !*str && !*strWild;
}

//gets a string of the contents of the indicated position of the word
string Board::getWord(string position, string word)
{
	char upperCase = position.at(0), lowerCase = position.at(1), orientation = position.at(2);
	unsigned int uC = ((int)upperCase - 'A'), lC = ((int)lowerCase - 'a');
	vector<char> temp;

	if (orientation == 'V')
	{
		for (unsigned int i = uC, k = 0, j = lC; k < word.length(); i++, k++)
		{
			temp.push_back(xy.at(i).at(j));
		}

		string newWord(temp.begin(), temp.end());
		return newWord;
	}
	else
	{
		for (unsigned int i = uC, k = 0, j = lC; k < word.length(); j++, k++)
		{
			temp.push_back(xy.at(i).at(j));
		}

		string newWord(temp.begin(), temp.end());
		return newWord;
	}
}

//checks if the indicated position is valid for the word the user wants to place
bool Board::validPosition(string word, string position)
{
	bool present = false;

	//complete row/line of the wanted position
	newWord = getWord(position, word);

	//changes the '.'to '?'
	for (unsigned int i = 0; i < newWord.length(); i++)
	{
		if (newWord.at(i) == '.')
		{
			newWord.at(i) = '*';
		}
	}

	//calls the wildcard function to check
	if (wildcardMatch(word.c_str(), newWord.c_str()))
		present = true;

	return present;
}

//removes the word in the coordinate given by the user
void Board::remove(string position)
{
	bool present = false;
	this->wordCoordinates;
	this->placedWords;

	//finds the index both in the coordinates vector and the word vector and deletes it
	for (unsigned int i = 0; i < wordCoordinates.size(); i++)
	{
		if (wordCoordinates.at(i) == position)
		{
			placedWords.erase(placedWords.begin() + i);
			wordCoordinates.erase(wordCoordinates.begin() + i);
			present = true;
			break;
		}
	}

	//clears the board and resizes it
	xy.clear();
	make();

	if (present)
	{
		for (unsigned int j = 0; j < placedWords.size(); j++)
		{
			//rewrites the words that are left in the vector in the board
			insert(wordCoordinates.at(j), placedWords.at(j));
		}

		cout << endl;

		//display of the board
		show();
	}
	else
	{
		cout << "That word doesn't exist!" << endl;
	}
}

//sees if the word fits in the position
bool Board::fit(string position, string word)
{
	this->columns;
	this->rows;

	if (position.at(2) == 'H')
	{
		//checks if there is enough space in the column for the word
		if ((columns - ((int)(position.at(1) - 'a'))) >= word.size())
		{
			return true;
		}
	}
	//checks if there is enough space in the row for the word
	if (position.at(2) == 'V')
	{
		if ((rows - ((int)(position.at(0) - 'A'))) >= word.size())
		{
			return true;
		}
	}
	return false;
}

//Gives the user a list of 10 words that fit in the position given
void Board::help(string position, vector<string> validWords)
{
	this->helpVec;
	bool present = false;
	int j = 0;

	//for every word in the dictionary it checks if it fits in the board
	for (unsigned int i = 0; i < validWords.size(); i++)
	{
		if (fit(position, validWords.at(i)))
		{
			if (validPosition(validWords.at(i), position))
			{
				helpVec.push_back(validWords.at(i));
				present = true;
			}
		}
	}
	//gives a list of 10 random words that fit
	while (j<10)
	{
		int randomIndex = rand() % helpVec.size();
		cout << "- " << helpVec.at(randomIndex) << endl;
		j++;
	}
}


void Board::checkIfFull()
{
	this->xy;
	this->rows;
	this->columns;
	bool filled = true;

	for (unsigned int l = 0; l < rows; l++)
	{
		for (unsigned int c = 0; c < columns; c++)
		{
			if (xy.at(l).at(c) == '.')
			{
				filled = false;
				break;
			}
		}
	}

	if (filled)
	{
		cout << "The board is full,Well done!" << endl;
	}
}