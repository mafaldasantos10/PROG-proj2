#include "Board.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
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

	for (unsigned i = 0, j= 0; i < wordCoordinates.size(), j < placedWords.size(); i++, j++)
	{
		fout << wordCoordinates.at(i) << "  " << placedWords.at(j) << endl;
	}

	fout.close();
}

//inserts words in the board
//inserts words in the board
void Board::insert(string position, string word)
{
	// stop
	//if (word == crtl-z)

	char upperCase = position.at(0), lowerCase = position.at(1), orientation = position.at(2);
	unsigned int uC = ((int)upperCase - 'A'), lC = ((int)lowerCase - 'a');

	/////create function just for this
	//verify size
	if (((uC + word.length()) > rows) || ((lC + word.length()) > columns))
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
	//string nW;

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

bool Board::validPosition(string word, string position)
{
	bool present = false;
	
	newWord = getWord(position, word);

	for (unsigned int i = 0; i < newWord.length(); i++)
	{
		if (newWord.at(i) == '.')
		{
			newWord.at(i) = '?';
		}
	}

	if (wildcardMatch(word.c_str(), newWord.c_str()))
		present = true;


	//if (!present)
	//	cout << "No words found" << endl;

	return present;
}

void Board::remove(string word)
{
	bool present = false;
	this->wordCoordinates;
	this->placedWords;
	
	for (int i = 0; i < placedWords.size(); i++)
	{
		cout << placedWords.at(i) << endl;
	}

	for (unsigned int i = 0, j = 0; i < wordCoordinates.size(), j < placedWords.size(); i++, j++)
	{
		if (placedWords.at(j) == word)
		{
			placedWords.erase(placedWords.begin() + i);
			wordCoordinates.erase(wordCoordinates.begin() + i);
			present = true;
			break;
		}
		
	}
	

	for (int i = 0; i < placedWords.size(); i++)
	{
		cout << placedWords.at(i) << endl;
	}
	xy.clear();
	make();

	if (present)
	{
		for (unsigned int i = 0, j = 0; i < wordCoordinates.size(), j < placedWords.size(); i++, j++)
		{
			
			insert(wordCoordinates.at(i), placedWords.at(j));
			
		}
		show();
	}

	else
		cout << "That word doesn't exist" << endl;
	
}
