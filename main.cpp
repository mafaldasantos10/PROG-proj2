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
		word; //word to insert
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
	//-----------------------------------------------------------------
	Board brd(rows, columns);
	brd.make();

	cout << endl;
	cout << endl;

	brd.show();

	//temporario!!!!!!!!!!!!!!
	//while (word != "idk")
	//{
	
	do
	{
		cout << endl << "Position ( RCD / CTRL-Z = stop ) ? ";
		cin >> position;

		if (cin.eof())
		{
				return 0;
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
			//brd.occupied(position, word);
			//checks whether the chosen word is valid
			if (!dict.isValid(word,validWords))
			{
				cerr << "Invalid word. Try again!" << endl << endl;
				exit(1);
			}
			else
			{
				if (brd.notUsedWord(word))
				{
					if (brd.fit(position, word))
					{
						if (brd.validPosition(word, position))
						{

							brd.insert(position, word);
							brd.track(position, word);
														
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
	//}
	//----------------------------------------------------------------------------------------
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