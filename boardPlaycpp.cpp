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
void setcolor(unsigned int color) 
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color); 

}
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

void paint(char a)
{
	if (isalpha(a) || a == ' ' || a == '.')
		setcolor(112);
	else if (a == '#')
		setcolor(7);
	else
		setcolor(200);
}

//shows the current board
void BoardPlay::show()
{
	cout << "   ";

	setcolor(12);

	for (unsigned int i = 97; i < 97 + columns; i++)
	{
		cout << char(i) << ' ';
	}

	cout << endl;

	for (unsigned int k = 0; k < rows; k++)
	{
		setcolor(12);
		cout << char(k + 65) << ' ';

		for (unsigned int j = 0; j < columns; j++)
		{
			//setcolor(112);
			cout << ' ';
			//paint(xy.at(k).at(j));
			cout << xy.at(k).at(j);
		}

		cout << ' ' << endl;
	}

	//setcolor(15);
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
			if (isalpha(xy.at(r).at(c)))
			{
				//places a % in that space
				setcolor(112);
				xy.at(r).at(c) = '%';
			}
			else
			{
				setcolor(15);
				xy.at(r).at(c) = ' ';
			}
			
		}
		//setcolor(15);	
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


void BoardPlay::checkAnswer(string word, string position, vector<string> coordinates, vector<string>words)
{
	bool present = false;

	for (unsigned int i = 0; i < coordinates.size(); i++)
	{
		if (word == words.at(i) && position == coordinates.at(i))
		{
				insert(position, word);
				show();
				cout << endl;
				cout << "You got it right! That's the word!";
				cout << endl;
				present = true;
				break;
		}
	}

	if (!present)
	{
		cout << "it's wrong." << endl;
	}
}

//checks in witch file to save the board 
string BoardPlay::isEmpty()
{
	string fileName = "b";

	ifstream fin;
	ofstream fout;

	//cycle
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
		fileName = "b";
	}
}

//saves the board
void BoardPlay::saveFile(string name, string thesaurusFile, vector<string>words, vector<string> coordinates)
{
	ofstream fout;

	//if the file is empty, it is written
	//string fileName = isEmpty();

	fout.open(name);

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
		//trying not to place a space at the end
		if (i == 0)
		{
			fout << wordCoordinates.at(i) << "  " << placedWords.at(i);
		}
		else
		{
			fout << endl << wordCoordinates.at(i) << "  " << placedWords.at(i);
		}
	}

	fout.close();

	cout << "Saved to file: " << name << endl << endl;
}
//checks if all the spaces in the board are filled
bool BoardPlay::checkIfFull()
{
	this->xy;
	this->rows;
	this->columns;
	bool filled = true;

	for (unsigned int r = 0; r < rows; r++)
	{
		for (unsigned int c = 0; c < columns; c++)
		{
			//searches for empty spaces
			if (xy.at(r).at(c) == '.')
			{
				filled = false;
				break;
			}
		}
	}

	if (filled)
	{
		cout << endl << "-----------------------------" << endl;
		cout << endl << "The board is full. Well done!" << endl << endl;
	}

	return filled;
}

