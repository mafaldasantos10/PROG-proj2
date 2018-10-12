#include "BoardPlay.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h> 
#include "dictionaryPlay.h"
#include <iomanip>
#include <windows.h>

using namespace std;

//function for changing color of the board
void setcolor(unsigned int color) 
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color); 
}

//constructor
BoardPlay::BoardPlay(unsigned int rows, unsigned int columns)
{
	//the variable rows and columns from main are the same for the class
	this->rows = rows;
	this->columns = columns;
}

//makes a new empty board with the indicated size
void BoardPlay::make()
{
	//resized the vector in order to have the correct size according to the rows and columns specified
	xy.resize(rows, vector<char>(columns, '.'));
}

//shows the current board
void BoardPlay::show()
{
	setcolor(7);
	cout << "   ";

	setcolor(12);

	//increases the alphabet till the specified number of columns is reached
	for (unsigned int i = 'a'; i < 'a' + columns; i++)
	{
		cout << char(i) << ' ';
		
	}
	setcolor(7);
	cout << endl;

	//increases the alphabet till the specified number of rows is reached
	for (unsigned int k = 0; k < rows; k++)
	{
		setcolor(12);
		cout << char(k + 'A') << ' ';
		setcolor(7);

		//prints the contents of the vector and therefore of the board
		for (unsigned int j = 0; j < columns; j++)
		{
			
			if (xy.at(k).at(j) == ' ')
			{
				setcolor(15);
				cout << "  ";
			}
			else
			{
				setcolor(112);
				cout << ' ';
				cout << xy.at(k).at(j);	
			}

		}

		cout << ' ' << endl;
	}

	setcolor(15);
}

//puts the words on the board
void BoardPlay::insert(string position, string word)
{
	char upperCase = position.at(0), lowerCase = position.at(1), orientation = position.at(2); //each letter is stored in each variable
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

//checks if the word is not being used again
bool BoardPlay::notUsedWord(string word)
{
	this->placedWords;

	bool notUsed = true; //true if the word being compared is in the vector that contains the placed words

	for (unsigned int i = 0; i < placedWords.size(); i++)
	{
		//if that word is in the vector, it means it has been used before
		if (placedWords.at(i) == word)
		{

			notUsed = false; //it has already been used
			cout << endl << "----------------------------------------" << endl << endl;
			cout << endl << "You already used that word. Try another!" << endl << endl;
			break;
		}
	}

	return notUsed;
}

//keeps track of all words and positions
void BoardPlay::track(string position, string word)
{
	wordCoordinates.push_back(position); //vector that stores the positions of the respective words on the board
	placedWords.push_back(word); //vector that stores all the words placed on the board
}

//gets a string of the contents of the indicated position of the word
string BoardPlay::getWord(string position, string word)
{
	char upperCase = position.at(0), lowerCase = position.at(1), orientation = position.at(2); //each letter is stored in each variable
	unsigned int uC = (upperCase - 'A'), lC = (lowerCase - 'a');
	vector<char> temp;

	if (orientation == 'V')
	{
		for (unsigned int i = uC, k = 0, j = lC; k < word.length(); i++, k++)
		{
			temp.push_back(xy.at(i).at(j)); //the contents are stored in a temporary vector
		}

		string newWord(temp.begin(), temp.end()); //makes the string out of the chars in the temp vector
		return newWord;
	}
	else
	{
		for (unsigned int i = uC, k = 0, j = lC; k < word.length(); j++, k++)
		{
			temp.push_back(xy.at(i).at(j)); //the contents are stored in a temporary vector
		}

		string newWord(temp.begin(), temp.end()); //makes the string out of the chars in the temp vector
		return newWord;
	}

}

//returns true if the word fits the wildcard
bool BoardPlay::wildcardMatch(const char *str, const char *strWild)
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

//checks if the indicated position is valid for the word the user wants to place
bool BoardPlay::validPosition(string word, string position)
{
	bool present = false; //true if the word can be placed~in that position

	//complete row/line of the wanted position
	string newWord = getWord(position, word);

	//changes the '.'to '?'
	for (unsigned int i = 0; i < newWord.length(); i++)
	{
		if (newWord.at(i) == '.')
		{
			newWord.at(i) = '?';
		}
	}

	//calls the wildcard function to check
	if (wildcardMatch(word.c_str(), newWord.c_str()))
		present = true; //if the wildcardFunction return true, it means the position is valid

	return present;
}

//removes the word in the coordinate given by the user
void BoardPlay::remove(string position,vector<string>coordinates, vector<string> words)
{
	bool present = false;
	this->wordCoordinates;
	this->placedWords;

	//finds the index both in the coordinates vector and the word vector and deletes it
	for (unsigned int i = 0; i < wordCoordinates.size(); i++)
	{
		//finds the index of the vector where position is
		if (wordCoordinates.at(i) == position)
		{
			//erases the word from the vector
			placedWords.erase(placedWords.begin() + i);
			//erases the position from the vector
			wordCoordinates.erase(wordCoordinates.begin() + i);
			//returns true when the position is valid
			present = true;
			break;
		}
	}

	//clears the board and resizes it
	xy.clear();
	make();

	//if the position exists in the wordCoordinates vec
	if (present)
	{
		for (unsigned int j = 0; j < words.size(); j++)
		{
			//rewrites the words that are left in the vector with the inicial words
			insert(coordinates.at(j), words.at(j));
		}

		cout << endl;
		//hides the words
		fillSpaces();
		//displays the board

		for (unsigned int j = 0; j < placedWords.size(); j++)
		{
			//rewrites the words that are left in the vector with the words the user wrote
			insert(wordCoordinates.at(j), placedWords.at(j));
		}

		//shows the board
		show();
	}
	else
	{
		cout << "That word doesn't exist!" << endl;
	}
}

//hides the words from the board
void BoardPlay::fillSpaces()
{
	this->xy;
	this->rows;
	this->columns;
	//to be able to search position by position of the vector<vector<string>>
	for (unsigned int r = 0; r < rows; r++)
	{
		for (unsigned int c = 0; c < columns; c++)
		{
			//searches for letters
			if (isalpha(xy.at(r).at(c)))
			{
				//places a "." in that space
				xy.at(r).at(c) = '.';
			}
			else
			{
				//places a blank space
				xy.at(r).at(c) = ' ';
			}
		}
	}
}

//checks if the words on the board are the right ones
bool BoardPlay::checkAnswers(vector<string> &coordinates, vector<string> &words)
{
	this->wordCoordinates; //vector with the coordinates of the words writen in the board by the user
	this->placedWords;//vecto withe the words writen in the board by the user 

	//checks if the words used by the user match the words in the file
	bool correct = true;

	//searches in the wordCoordinates vector 
	for (unsigned int i = 0; i < wordCoordinates.size(); i++)
	{
		for (unsigned int j = 0; j < coordinates.size(); j++)
		{
			//finds in the wordcoordinates vector the positions present in the coordinates vec
			if (coordinates.at(j) == wordCoordinates.at(i))
			{
				//if at the same index the words of both words vector and placed Words vector are different that word isnt correct
				if (words.at(j) != placedWords.at(i))
				{
					correct = false;
					break;
				}
				
			}
		}
	}

	return correct;
}

//saves the board
void BoardPlay::saveFile(string thesaurusFile, vector<string>words, vector<string> coordinates, string savedFile)
{
	ofstream fout;

	//opens the file that will be used to store
	fout.open(savedFile);

	//name of the thesaurusFile used
	fout << thesaurusFile << endl << endl;

	//saves the current board into a file
	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
		{
			fout << xy.at(i).at(j) << " ";
		}

		fout << endl;
	}

	fout << endl;

	//saves the respective positions and words on the board
	for (unsigned i = 0; i < wordCoordinates.size(); i++)
	{
		//so that it doesn't place a space at the end of the last word
		if (i == 0)
		{
			fout << wordCoordinates.at(i) << "  " << placedWords.at(i);
		}
		else
		{
			fout << endl << wordCoordinates.at(i) << "  " << placedWords.at(i);
		}
	}

	//closes the output file used
	fout.close();

	cout << " Saved to file: " << savedFile << endl << endl; //tells the user the name of the file where it was saved
}

//checks if all the spaces in the board are filled
bool BoardPlay::checkIfFull()
{
	this->xy;
	this->rows;
	this->columns;
	bool filled = true; //true if the board is full


	for (unsigned int r = 0; r < rows; r++)
	{
		for (unsigned int c = 0; c < columns; c++)
		{
			//searches for empty spaces
			if (xy.at(r).at(c) == '.' )
			{
				filled = false; //if a "." if found, it means it's not full, making "filled" become false
				break;
			}
		}
	}

	return filled;
}

//sees if the word fits in the position
bool BoardPlay::fit(string position, string word)
{
	this->columns;
	this->rows;

	bool fits = false;

	//checks horizontally
	if (position.at(2) == 'H')
	{
		//checks if there is enough space in the column for the word
		if ((columns - ((int)(position.at(1) - 'a'))) >= word.size())
		{
			fits = true;
		}
	}
	//checks vertically
	if (position.at(2) == 'V')
	{
		//checks if there is enough space in the row for the word
		if ((rows - ((int)(position.at(0) - 'A'))) >= word.size())
		{
			fits = true;
		}
	}

	return fits;
}

//double checks if all the words in the board are valid
bool BoardPlay::doubleValidCheck(map<string, vector<string> > &validWords)
{
	this->placedWords;
	this->wordCoordinates;
	bool valid = true;
	//word extracted from the board using the given position and length of the word that is to be placed there
	string newWord;

	for (unsigned int i = 0; i < placedWords.size(); i++)
	{
		//takes the word from the board
		newWord = getWord(wordCoordinates.at(i), placedWords.at(i));
		//uses the disctionary function is valid
		if (!newDict->isValid(newWord, validWords))
		{
			valid = false;
			break;
		}
	}

	return valid;
}
