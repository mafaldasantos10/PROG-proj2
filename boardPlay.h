 #ifndef BoardPlay_h
#define BoardPlay_h

#include <iostream>
#include <vector>
#include <string>
#include <istream>
#include "dictionaryPlay.h"

using namespace std;

class BoardPlay
{
public:
	BoardPlay(unsigned int rows, unsigned int columns);
	void show(); //shows the current board
	void make(); //creates a board
	void insert(string position, string word); //inserts new words on the board
	bool notUsedWord(string word);
	void track(string position, string word);
	//void occupied(string position, string word);
	string getWord(string position, string word);
	void remove(string position,vector<string>coordinates,vector<string> words);
	string isEmpty();
	void saveFile(string name, string thesaurusFile, vector<string> word, vector<string>coordinates);
	DictionaryPlay* newDict;
	bool fit(string position, string word);
	void upload();
	bool wildcardMatch(const char *str, const char *strWild);
	void fillSpaces();
	void checkAnswers(string word, string position, vector<string> coordinates, vector<string>placedwords);
	bool checkIfFull();
	bool validPosition(string word, string position);
	
private:
	vector < vector <char> > xy; //board
	vector<string> wordCoordinates; //vector that stores the positions of the respective words on the board
	vector<string> placedWords; //vector that stores all the words placed on the board
	unsigned int rows, columns;
	string position, word;
	vector<string> validWords;
	vector<string> usedClues;
};
#endif