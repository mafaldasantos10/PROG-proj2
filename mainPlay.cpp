#include "dictionaryPlay.h"
#include "boardPlay.h"
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
	string thesaurusFile, name,  savedFile, word, position, option2; //file that contains the dictionary
    vector<string> wordCoordinates, placedWords;
	int rows = 0, columns;
	ifstream fin;
	map<string, vector<string> > validWords;

	srand(time(NULL));

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

	//cout << validWords["zero"] << endl;
	dict.clues(placedWords, wordCoordinates);
	do
	{
		cout << endl;
		cout << "Position ( RCD / CTRL-Z = stop ) ? ";
		cin >> position;
		if (cin.eof())
		{
			return 0;
		}

		cout << "Word ( - = remove) ? ";
		cin >> word;
		word = dict.caps(word);
		
		if (word == "-")
		{
			brd.remove(position,wordCoordinates,placedWords);
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
							cout << endl << "You can't overwrite previously placed words. Try again!" << endl;
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
	} while (!brd.checkIfFull());

	brd.checkAnswers(word, position, wordCoordinates, placedWords);
	brd.saveFile(name, thesaurusFile, wordCoordinates, placedWords);

	return 0;
}