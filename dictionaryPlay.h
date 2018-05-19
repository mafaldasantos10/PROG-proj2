#ifndef dictionaryPlay_h
#define dictionaryPlay_h

#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class DictionaryPlay
{
public:
	DictionaryPlay(string thesaurusFile);
	bool isValid(string word, map<string, vector<string> > &validWords);
	string caps(string word); //capitalizes the first letter of the word given by the user
	map<string, vector<string> > validWords;
	void clues(vector<string> &words);
	void synonymHelp(string position,vector<string> &words, vector<string> &coordinates);
	void showClues(vector<string> &words, vector<string> &coordinates);
	bool notUsedWord(string word, vector<string> &vector);
private:
	
	vector<string>synonyms, // vector that saves all tthe synonymes from the class to put in map
		tempWord, // saves a random synonym of the words stores in the mains vector placed Words
		usedSynonym; // stores the synonyms that have already been used
};
#endif