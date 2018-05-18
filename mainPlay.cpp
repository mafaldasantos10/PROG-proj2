#include "dictionaryPlay.h"
#include "boardPlay.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <map>

using namespace std;

int main()
{
	//variables
	string thesaurusFile, //file that contains the dictionary
		   position, //position where the user wants to insert the word
		   word, //word to insert in the board
		   option, //which game option the user chooses
		   option2, //decision between saving or finishing the current board contrction after ctrl-z
		   savedFile, //file to use in the game option 2
		   name, //name of the player
		   wantsToFinish; //user might decide between yes or no when the board is filled


	vector<string> wordCoordinates, //vector that contains the words that have been placed in the board
				   placedWords; //vector that contains the position of each word placed in the board

	int rows = 0, //rows of the board
		columns, //columns of the board
		time1, //registers the time when the user starts playing
		time2;	//registers the time when the user finishes playing

	map<string, vector<string> > validWords;

	ifstream fin;

	//new random seed
	srand((unsigned int)time(NULL));


	//INTERFACE
	//-----------------------------------------------------------------

	cout << "--------------------" << endl
		 << "------- PLAY -------" << endl
		 << "--------------------" << endl;

	cout << "Player name: ";
	cin >> name;

	Player currentPlayer(name);

	cout << endl 
		 << "File that cointains a saved board? ";

	cin >> savedFile;

	//Board load
	//--------------------------------------------------------------------------------------------------------------
	fin.open(savedFile);

	//checks wether the indicated file is valid
	if (!fin.is_open())
	{
		cerr << "Input file not found!" << endl << endl;
		exit(1);
	}

	string next;

	//gets the thesaurus file
	getline(fin, thesaurusFile);

	//extracts the header words to a vector
	getline(fin, next);
	getline(fin, next);

	columns = (unsigned int)(next.length() / 2);

	//computes the number of rows of the saved board
	while (next.length() != 0)
	{
		rows++;
		getline(fin, next);
	}

	//after the last empty line (that indicates the end of the board) it'll extract the words and their postions
	while (!fin.eof())
	{
		getline(fin, next);

		//covers the case where the file has an empty board saved
		if (next.length() == 0)
		{
			cout << endl
				<< "-----------------------------------" << endl
				<< "That file contained an empty board!";
			break;
		}

		//AaV  example
		wordCoordinates.push_back(next.substr(0, 3));
		placedWords.push_back(next.substr(5, (next.length() - 5)));
	}

	//closes the file where the board was
	fin.close();

	//opens the thesaurus file used to build the loaded board
	fin.open(thesaurusFile);

	//checks wether the indicated file is valid
	if (!fin.is_open())
	{
		cerr << "Input file not found!" << endl << endl;
		exit(1);
	}

	DictionaryPlay dict(thesaurusFile);
	
	//constructs and empty board
	BoardPlay brd(rows, columns);
	brd.make();

	//in case it's used a saved board, it'll add the already placed words in the respective places
	for (unsigned int j = 0; j < placedWords.size(); j++)
	{
		brd.insert(wordCoordinates.at(j), placedWords.at(j));
	}

	cout << endl;
	cout << endl;

	brd.fillSpaces();

	//shows the current state of the board
	brd.show();

	//vector with the valid words from the thesaurus
	validWords = dict.validWords;

	//dict.clues(placedWords, wordCoordinates);

	//registers the time when the user starts playing
	time1 = time(NULL);

	do
	{

		//shows the user the inicial clues
		dict.showClues(placedWords, wordCoordinates);

		do
		{
			cout << endl << "Position ( RCD / CTRL-Z = stop ) ? ";
			cin >> position;

		//format has to be, for instance, AaV
		} while ((position.length() > 3) || (position.at(0) < 'A') || (position.at(0) > ('A' + (rows - 1))) || (position.at(1) < 'a') || (position.at(1) > ('a' + (columns - 1))) || ((position.at(2) != 'H') && (position.at(2) != 'V')));

		cout << endl;

		/*if (cin.eof())
		{
			return 0;
		}*/

		cout << "Word ( - = remove / ? = help ) ? ";
		cin >> word;

		word = dict.caps(word);
		
		if (word == "?") //the user might ask for help
		{
			
			dict.synonymHelp(position,placedWords,wordCoordinates);
		}
		else if (word == "-")
		{
			brd.remove(position,wordCoordinates,placedWords); //the user might want to remove a previously placed word
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

			//cout << endl;
			//brd.checkAnswer(word, position, wordCoordinates, placedWords);
		}

		if (brd.checkIfFull())
			//&& brd.doubleValidCheck(validWords)) //checks if the board is full and double checks the placed words after each iteration
		{
			cout << endl << " yes - validates the board" << endl
						 << " no - you might edit it" << endl;

			do
			{
				cout << endl << " Answer? ";
				cin >> wantsToFinish;

				//only allows "yes" or "no" as an answer
			} while (wantsToFinish != "yes" && wantsToFinish != "no");
		}

	} while (wantsToFinish != "yes"); //keeps doing it till the board is full and the user wants to finish

	//registers the time when the user finishes playing
	time2 = time(NULL);

	//determines the time it takes till the user finishes playing
	currentPlayer.getTime(time1, time2);

	//validates the board by checking the attempt
	brd.checkAnswers(word, position, wordCoordinates, placedWords);

	//saves the file if it's full
	brd.saveFile(name, thesaurusFile, wordCoordinates, placedWords);
	//closes the input file
	fin.close();

	return 0;
}