#include "dictionary.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

int main()
{
	//variables
	string thesaurusFile, //file that contains the dictionary
		   position, //position where the user wants to insert the word
		   word, //word to insert in the board
		   option, //which game option the user chooses
		   option2, //decision between saving or finishing the current board contrction after ctrl-z
		   savedFile; //file to use in the game option 2

	int rows = 0, //rows of the board
		columns; //columns of the board

	vector<string> validWords, //vector with the header words extracted from the thesaurus file
				   wordCoordinates, //vector that contains the words that have been placed in the board
				   placedWords; //vector that contains the position of each word placed in the board

	ifstream fin;

	//new random seed
	srand(time(NULL));

	//INTERFACE
	//-----------------------------------------------------------------

	cout << "CROSSWORDS PUZZLE CREATOR" << endl
		 << "=========================" << endl << endl
		 << "Position (RCD / CTRL-Z = STOP)" << endl
		 << " -RCD stands for Row, Column and Direction" << endl << endl
		 << "-------------------------" << endl
		 << "OPTIONS:" << endl
		 << " 1 - Create Puzzle" << endl
		 << " 2 - Resume Puzzle" << endl
		 << " 0 - Exit" << endl << endl
		 << "Option? ";

	cin >> option;

	//--------------------------------------------------------------------------------------------------------------
	//END of INTERFACE

	//OPTION 1
	//--------------------------------------------------------------------------------------------------------------
	if (option == "1")
	{
		cout << endl
			 << "-------------------------" << endl
			 << "CREATE PUZZLE" << endl
			 << "-------------------------" << endl;

		cout << "Thesaurus file name? ";
		cin >> thesaurusFile;

		//opens the chosen thesaurus file
		fin.open(thesaurusFile);

		//checks wether the indicated file is valid
		if (!fin.is_open())
		{
			cerr << "Input file not found!\n" << endl;
			exit(1);
		}

		cout << "Board size (rows, columns)? ";
		cin >> rows >> columns;
	}
	//--------------------------------------------------------------------------------------------------------------
	//END of OPTION 1

	//OPTION 2
	//--------------------------------------------------------------------------------------------------------------
	else if (option == "2")
	{
		cout << endl << "File that cointains a saved board? ";
		cin >> savedFile;

		//opens the chosen file that contains the saved board
		fin.open(savedFile);

		//checks wether the indicated file is valid
		if (!fin.is_open())
		{
			cerr << "Input file not found!\n" << endl;
			exit(1);
		}

		string next; //string with each line extracted

		//first line of the file contains the used thesaurus file
		getline(fin, thesaurusFile);

		//empty line
		getline(fin, next);

		//gets the first row of the board
		getline(fin, next);
		columns = (next.length() / 2); //determines the number of columns using its length

		//till it reaches an empty line (end of the board) it'll count the rows
		while (next.length() != 0)
		{
			rows++;
			getline(fin, next);
		}

		//after the last empty line (that indicates the end of the board) it'll extract the words and their postions
		while (!fin.eof())
		{
			getline(fin, next);
			//AaV  example
			wordCoordinates.push_back(next.substr(0, 3));
			placedWords.push_back(next.substr(5, (next.length() - 5)));
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//END of OPTION 2

	else
	//OPTION 3
	//--------------------------------------------------------------------------------------------------------------
	{
		//exits if that option is chosen
		return 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//END of OPTION 3

	//constructs and empty board
	Board brd(rows, columns);
	brd.make();

	//in case it's used a saved board, it'll add the already placed words in the respective places
	for (unsigned int j = 0; j < placedWords.size(); j++)
	{
		brd.insert(wordCoordinates.at(j), placedWords.at(j));
	}

	cout << endl;
	cout << endl;

	//shows the current state of the board
	brd.show();

	//constructs the dictionary vector
	Dictionary dict(thesaurusFile);
	//vector with the valid words from the thesaurus
	validWords = dict.validWords;

	do
	{
		cout << endl << "Position ( RCD / CTRL-Z = stop ) ? ";
		cin >> position;

		//checks for a "ctrl-z" input that will immidiately stop the building of the board
		if (cin.eof())
		{
			cout << endl << "-----------------------------------------------------------------" << endl;
			cout << endl << "Do you want to save the current state of the board in order "
				 << endl << "to resume later  or do you want to finish it now? (save / finish)" << endl << endl;

			cin.clear(); //clears the buffer

			cin >> option2;

			if (option2 == "save")
			{
				cout << endl << "GOOD GAME! It will be saved for you to came back! " << endl << endl;
				brd.saveFile(thesaurusFile); //saves it
				return 0;
			}
			else
			{
				cout << endl << "GOOD GAME!" << endl << endl;
				brd.fillSpaces(); //before saving the board, it completes it by filling the empty spaces ( "." )
				brd.saveFile(thesaurusFile); //saves it
				return 0;
			}
		}

		cout << endl;

		cout << "Word ( - = remove / ? = help ) ? ";
		cin >> word;

		if (word == "?") //the user might ask for help
		{
			cout << "These are some words that can fit in that position!" << endl << endl;
			brd.help(position, validWords);
		}
		else if (word == "-") //the user might want to remove a previously placed word
		{
			brd.remove(position);
		}
		else
		{
			//checks whether the chosen word is valid
			if (dict.isValid(word, validWords))
			{
				//checks if the word was already used
				if (brd.notUsedWord(word))
				{
					//checks if the word fits in the desired postion (size wise)
					if (brd.fit(position, word))
					{
						//checks if the position is valid, i.e., if it won't overwrite other words
						if (brd.validPosition(word, position))
						{
							brd.insert(position, word); //because it's valid, it is placed in the board
							brd.track(position, word); //keeps track of the coordinates and words placed in the board
						}
						else
						{
							cout << endl << "-------------------------------------------------------" << endl;
							cout << endl << "You can't overwrite previously placed words. Try again!" << endl;
						}
					}
					else
					{
						cout << endl << "--------------------------------------------------------" << endl;
						cout << endl << "That word does not fit in the place you want. Try again!" << endl;
					}
				}
			}
			else
			{
				cout << endl << "------------------------" << endl;
				cout << endl << "Invalid word. Try again!" << endl;
			}

			cout << endl;
			brd.show(); //shows the current state of the board
		}
	}
	while (!brd.checkIfFull() && brd.doubleValidCheck(validWords)); //checks if the board is full and double checks the placed words after each iteration

	//saves the file if it's full
	brd.saveFile(thesaurusFile);

	//closes the input file
	fin.close();

	return 0;
}

/*
cwcreator
main.cpp
Creates a playable crossword board.
@author Diogo & Mafalda
@version 1.0 29/04/2018
*/

//board is full when loading
//MvV
//newDict parametro