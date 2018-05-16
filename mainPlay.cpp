#include "dictionaryPlay.h"
#include "boardPlay.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

int main()
{
	//variables
	string thesaurusFile, name,  savedFile, word, position, option2; //file that contains the dictionary
    vector<string> validWords, wordCoordinates, placedWords;
	int rows = 0, columns;
	ifstream fin;

	//OPTION 1
	//--------------------------------------------------------------------------------------------------------------

	cout << endl
		<< "-------------------------" << endl
		<< "          PLAY" << endl
		<< "-------------------------" << endl;

	cout << "Player name: ";
	cin >> name;

	cout << endl << "File that cointains a saved board? ";
	cin >> savedFile;

	//--------------------------------------------------------------------------------------------------------------
	fin.open(savedFile);

	//checks wether the indicated file is valid
	if (!fin.is_open())
	{
		cerr << "Input file not found!\n" << endl;
		exit(1);
	}

	string next;

	//gets the thesaurus file
	getline(fin, thesaurusFile);

	//extracts the header words to a vector
	getline(fin, next);
	getline(fin, next);

	columns = (next.length() / 2);

	//computes the number of rows of the saved board
	while (next.length() != 0)
	{
		rows++;
		getline(fin, next);
	}

	//extracts the words and its coordinates to vectors
	while (!fin.eof())
	{
		getline(fin, next);

		wordCoordinates.push_back(next.substr(0, 3));
		placedWords.push_back(next.substr(5, (next.length() - 5)));
	}

	fin.close();

	fin.open(thesaurusFile);

	//checks wether the indicated file is valid
	if (!fin.is_open())
	{
		cerr << "Input file not found!" << endl << endl;
		exit(1);
	}

	DictionaryPlay dict(thesaurusFile);

	BoardPlay brd(rows, columns);

	brd.make();

	//builds the board
	for (unsigned int j = 0; j < placedWords.size(); j++)
	{
		//rewrites the words that are left in the vector in the board
		brd.insert(wordCoordinates.at(j), placedWords.at(j));
	}

	cout << endl;
	cout << endl;

	brd.fillSpaces();

	brd.show();
	validWords = dict.validWords;

	while (!brd.checkIfFull())
	{
		cout << endl;
		cout << "Position ( RCD / CTRL-Z = stop ) ? ";
		cin >> position;
		if (cin.eof())
		{
			{
				cout << endl << "-----------------------------------------------------------------" << endl;
				cout << endl << "Do you want to save the current state of the board in order "
					<< endl << "to resume later  or do you want to finish it now? (save / finish)" << endl << endl;

				cin.clear(); // clear error state
							 //cin.ignore(1000, '\n');

				cin >> option2;

				if (option2 == "save")
				{
					cout << endl << "GOOD GAME! It will be saved for you to came back! " << endl << endl;
					brd.saveFile(name, thesaurusFile, wordCoordinates, placedWords);
					return 0;
				}
				else if (option2 == "finish")
				{
					cout << endl << "GOOD GAME!" << endl << endl;
					brd.fillSpaces();
					brd.saveFile(name, thesaurusFile, wordCoordinates, placedWords);
					return 0;
				}
			}
		}

		cout << "Word ( - = remove / ? = help ) ? ";
		cin >> word;
		if (word == "-")
		{

		}
		else
		{
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

				//cout << endl;
				//brd.checkAnswer(word, position, wordCoordinates, placedWords);
			}
		}
	}
	brd.saveFile(name, thesaurusFile, wordCoordinates, placedWords);

	return 0;
}