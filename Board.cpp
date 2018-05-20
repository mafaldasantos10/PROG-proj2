#include "Board.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h> 
#include "dictionary.h"
#include <iomanip>
#include <windows.h>
#include <algorithm>

using namespace std;

//function for changing color of the board
void setcolor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

//changes the color of hashtags and letters
void setColor2(char a)
{
	//finds if it is a letter or a # 
	if (isalpha(a) || a == ' ' || a == '.')
	{
		//changes the color to black whith white background
		setcolor(112);
	}
	else if (a == '#')
	{
		//changes the color to white with black background
		setcolor(7);
	}
}

//board constructor
Board::Board(unsigned int rows, unsigned int columns)
{
	//the variable rows and columns from main are the same for the class
	this->rows = rows;
	this->columns = columns;
}

//makes a new empty board with the indicated size
void Board::make()
{
	//resized the vector in order to have the correct size according to the rows and columns specified
	xy.resize(rows, vector<char>(columns, '.'));
}

//shows the current board state
void Board::show()
{
	cout << "   ";

	setcolor(12);

	//increases the alphabet till the specified number of columns is reached
	for (unsigned int i = 'a'; i < 'a' + columns; i++)
	{
		cout << char(i) << ' ';
	}

	cout << endl;

	//increases the alphabet till the specified number of rows is reached
	for (unsigned int k = 0; k < rows; k++)
	{
		setcolor(12);
		cout << char(k + 'A') << ' ';

		//prints the contents of the vector and therefore of the board
		for (unsigned int j = 0; j < columns; j++)
		{
			setcolor(112);
			cout << ' ';
			setColor2(xy.at(k).at(j));
			cout << xy.at(k).at(j);
		}

		cout << ' ' << endl;
	}

	setcolor(15);
}

//allows MAIN to use the vector that contains the already placed words
vector<string> Board::Words()
{
	//returns the class vector
	return placedWords;
}

//checks if the given word has not been used in that board before
bool Board::notUsedWord(string word, vector<string> &placedWords)
{
	bool notUsed = true; //true if the word being compared is in the vector that contains the placed words

	for (unsigned int i = 0; i < placedWords.size(); i++)
	{
		//if that word is in the vector, it means it has been used before
		if (placedWords.at(i) == word)
		{
			notUsed = false; //it has been used
			break;
		}
	}

	return notUsed;
}

//keeps track of all words and positions
void Board::track(string position, string word)
{
	wordCoordinates.push_back(position); //vector that stores the positions of the respective words on the board
	placedWords.push_back(word); //vector that stores all the words placed on the board
}

//determines the name of the first available (empty) file usign the name format BXXX.txt
string Board::isEmpty()
{
	string warningMessage = "full", //warning for cases where all 999 available file names were used
		   fileName = "b"; //the file will be saved always in a file starting with a "b"

	ifstream fin;
	ofstream fout;

	//cycle to find what's the first available number
	for (unsigned i = 1; i < 999; i++)
	{
		if (i < 10)
		{
			fileName = fileName + "00" + to_string(i) + ".txt";
			fin.open(fileName);
		}
		else if (i < 100)
		{
			fileName = fileName + "0" + to_string(i) + ".txt";
			fin.open(fileName);
		}
		else
		{
			fileName = fileName + to_string(i) + ".txt";
			fin.open(fileName);
		}

		//returns true if empty
		if (fin.peek() == EOF)
		{
			return fileName;
		}

		fin.close();
		fileName = "b"; //resets the name after each attempt
	}

	//if no available name was found, it returns a warning message
	return warningMessage;
}

//saves the board
void Board::saveFile(string thesaurusFile, bool resumedBoard, string savedFile)
{
	this->placedWords; //vector that stores the positions of the respective words on the board
	this->wordCoordinates; //vector that stores all the words placed on the board

	string fileName, //name of the file that will be used to store all the contents
		   readyToContinue; //allows the user to continue if he already cleaned an old file by pressing any key

	ofstream fout;

	if (resumedBoard)
	{
		fileName = savedFile; //if the board is resumed, it is saved in the same file
	}
	else
	{
		fileName = isEmpty(); //otherwise it will search for the next empty file name
	}

	//when all files are full, isEmpty() return the warning message that contained the string "full"
	while (fileName == "full")
	{
		cout << "---------------------------------------------------------------";
		cout << endl << "But wait! All file slots are full, try to clean some old stuff!" << endl;
		cout << endl << "Press any letter to continue if you've cleaned the clutter." << endl << endl;

		cin >> readyToContinue; //just to press any key

		fileName = isEmpty(); //it'll find the first available file if it has new names available
	}
	
	//opens the file that will will be written
	fout.open(fileName);

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

	cout << endl << " Saved to file: " << fileName << endl << endl; //tells the user the name of the file where it was saved
}

//inserts new words on the board using the given position and word
void Board::insert(string position, string word)
{
	char upperCase = position.at(0), lowerCase = position.at(1), orientation = position.at(2); //each letter is stored in each variable
	unsigned int uC = (upperCase - 'A'), lC = (lowerCase - 'a');

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
		if (((uC + word.length()) < rows) && (xy.at(lC + word.length()).at(uC) = '.'))
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

//returns true if the word fitsthe wildcard
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

//checks if the indicated position is valid for the word the user wants to place
bool Board::validPosition(string word, string position)
{
	bool present = false; //true if the word can be placed in that position

	//complete row/line of the wanted position
	string newWord = getWord(position, word);

	//changes the '.' to '?'
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
void Board::remove(string position)
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
		for (unsigned int j = 0; j < placedWords.size(); j++)
		{
			//rewrites the words that are left in the vector in the board
			insert(wordCoordinates.at(j), placedWords.at(j));
		}

		cout << endl;

		//displays the board
		show();
	}
	else
	{
		//if the position isnt found
		cout << endl << "----------------------------------------------------" << endl;
		cout << endl << "There is no word placed in that position. Try again!" << endl;
	}
}

//sees if the word fits in the position
bool Board::fit(string position, string word)
{
	this->columns;
	this->rows;

	//becomes true if the word fits the place
	bool fits = false;

	//checks horizontally
	if (position.at(2) == 'H')
	{
		//checks if there is enough space in the column for the word
		if ((columns - (position.at(1) - 'a')) >= word.size())
		{
			fits = true;
		}
	}
	//checks vertically
	if (position.at(2) == 'V')
	{
		//checks if there is enough space in the row for the word
		if ((rows - (position.at(0) - 'A')) >= word.size())
		{
			fits = true;
		}
	}

	return fits;
}

//Gives the user a list of 10 words that fit in the position given
void Board::help(string position, map<string, vector<string> > &validWords)
{
	vector<string> helpVec; //saves all the words that fit the place
	int j = 0;
	vector<string> usedwords; //stores the words that have already been given by clues
	bool hashtag = false;
	bool notfit = false;
	int counter = 0;
	cout << endl;
	
	for (map<string, vector<string> >::iterator it = validWords.begin(); it != validWords.end(); ++it)
	{
		if (fit(position, it->first))
		{
			//complete row/line of the wanted position
			newWord = getWord(position, it->first); 

			//changes the '.'to '*'
			
			//searches in the string
			for (unsigned int i = 0; i < newWord.length(); i++)
			{
				//if there is a hashtag in the 1st or 2nd position
				if (newWord.at(0) == '#' || newWord.at(1) == '#')
				{
					hashtag = true;
					break;
				}

				//change "." to "*" in order to send the string to the function wildcardmatch
				if (newWord.at(i) == '.')
				{
					newWord.at(i) = '*';
				}
			}
			//sends the string with the "*"
			if (wildcardMatch(it->first.c_str(), newWord.c_str())) 
			{
				//sends the string with "?" to the wilscard function and avaliates if the word can be used in the position (true)
				if (validPosition(it->first, position))
				{
					//saves the words that can be used in a vector
					helpVec.push_back(it->first);

					// sees if the vector is empty
					if (helpVec.empty())
					{
						notfit = true;
						break;
					}
				}
			}
		}
		//if there isnt a single word that fits the position
		else
		{
			counter++;
			if (counter == validWords.size())
			{
				notfit = true;
				break;
			}
		}
	}

	//if there isnt a 
	if(notfit)
	{
		cout << "no word fits there" << endl;
	}

	if (hashtag)//if there is a hashtag in the given coordinates
	{
		cout << "You cant overwrite a #! " << endl;
	}
	else
	{
		//gives a list of 10 random words that fit or if there only fits less than 10 it shows those
		while ((j != helpVec.size()) && (j < 10))
		{

				//random selection of the words to show
				int randomIndex = rand() % helpVec.size();
				string clue = helpVec.at(randomIndex); //stores one of the clues

				if (notUsedWord(clue, usedwords))//checks if it has been used
				{
					if (notUsedWord(clue, placedWords)) //sees if the word is already on the board
					{
						cout << "- " << clue << endl;
						//stores the clues in the usedwords vec
						usedwords.push_back(clue);
						j++;
					}
					else
					{
						//erases the clue from the vector
						helpVec.erase(helpVec.begin() + randomIndex);
					}
				}
			
		}

		//clears the vector for when the function is called again
		usedwords.clear();
	}
}

//checks if all the spaces in the board are filled
bool Board::checkIfFull()
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
			if (xy.at(r).at(c) == '.')
			{
				filled = false; //if a "." if found, it means it's not full, making "filled" become false
				break;
			}
		}
	}

	//if there arent spaced missing
	if (filled)
	{
		cout << endl << "-------------------------------------------------------------------------------" << endl;
		cout <<	"The board is full and all words are correctly placed. Do you want to finish it?" << endl;
	}

	return filled;
}

//fills the empty spaces
void Board::fillSpaces()
{
	this->xy;
	this->rows;
	this->columns;

	for (unsigned int r = 0; r < rows; r++)
	{
		for (unsigned int c = 0; c < columns; c++)
		{
			//searches for empty spaces
			if (xy.at(r).at(c) == '.')
			{
				//places a # in that space
				xy.at(r).at(c) = '#';
			}
		}
	}
}

//double checks if all the words in the board are valid
bool Board::doubleValidCheck(map<string, vector<string> > &validWords)
{
	this->placedWords;
	this->wordCoordinates;
	bool valid = true;

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