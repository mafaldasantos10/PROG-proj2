#include "dictionary.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

int main()
{
	//variables
	string thesaurusFile, //file that contains the dictionary
		   position, //position of the word
		   word, //word to insert
		   option2;
	int rows, columns, option;
	vector<string> validWords;

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

	cout << endl
		 << "-------------------------" << endl
		 << "CREATE PUZZLE" << endl
		 << "-------------------------" << endl;

	//-----------------------------------------------------------------
	//END of INTERFACE

	cout << "Thesaurus file name? ";
	cin >> thesaurusFile;

	//vector with the valid words from the thesaurus
	Dictionary dict(thesaurusFile);
	validWords = dict.validWords;

	cout << "Board size (rows, columns)? ";
	cin >> rows >> columns;

	//OPTION 1
	//--------------------------------------------------------------------------------------------------------------
	Board brd(rows, columns);
	brd.make();

	cout << endl;
	cout << endl;

	brd.show();

	do
	{
		cout << endl << "Position ( RCD / CTRL-Z = stop ) ? ";
		cin >> position;

		//ctrl-z
		if (cin.eof())
		{

			cout << endl << "-------------------------------------------------------" << endl;
			cout << endl << "Do you want to save the current state of the board in order "
				 << endl << "to resume later  or do you want to finish it now? (save / finish)" << endl << endl;

			cin.clear(); // clear error state
						 //cin.ignore(1000, '\n');

			cin >> option2;

			if (option2 == "save")
			{
				cout << endl << "GOOD GAME! It will be saved for you to came back! " << endl << endl;
				brd.saveFile(thesaurusFile);
				return 0;
			}
			else
			{
				cout << endl << "GOOD GAME!" << endl << endl;
				brd.fillSpaces();
				brd.saveFile(thesaurusFile);
				return 0;
			}


		}

		//+3 letras, erro
		//ordem MmV
		//ver casos mmv
		cout << endl;

		cout << "Word ( - = remove / ? = help ) ? ";
		cin >> word;

		//finishes
		if (word == "idk")
		{
			cout << "GOOD GAME!" << endl << endl;
			brd.saveFile(thesaurusFile);
			break;
		}
		else if (word == "help")
		{
			cout << "These are some words that can fit in that position!" << endl << endl;
			brd.help(position, validWords);

		}
		else if (word == "-")
		{
			brd.remove(position);
		}
		else
		{
			//checks whether the chosen word is valid
			if (!dict.isValid(word, validWords))
			{
				cerr << "Invalid word. Try again!" << endl << endl;
				exit(1);
			}
			else
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
							cout << endl << "You can't overwrite previously placed words. Try again!" << endl << endl;
						}
					}
					else
					{
						cout << endl << "--------------------------------------------------------" << endl;
						cout << endl << "That word does not fit in the place you want. Try again!" << endl << endl;
					}
				}
				cout << endl;
				brd.show();
			}
		}
	} while (!brd.checkIfFull() && brd.doubleValidCheck(validWords));
	//--------------------------------------------------------------------------------------------------------------
	//END of OPTION 1

	return 0;
}

/*
cwcreator
main.cpp
Extraction of a word list from a synonym dictionary
@author Diogo & Mafalda
@version 1.0 29/04/2018
*/