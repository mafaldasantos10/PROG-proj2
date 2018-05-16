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
	string thesaurusFile, name,  savedFile, word, position; //file that contains the dictionary
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
	while (true)
	{
		cout << endl;
		cout << "position: ";
		cout << endl;
		cin >> position;

		cout << "word: ";
		cout << endl;
		cin >> word;
		cout << endl;
		brd.checkAnswer(word, position, wordCoordinates, placedWords);
	}
	
	return 0;
}