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
	vector<string> clues(vector<string> &words, vector<string> &coordinates);
	void synonymHelp(string position,vector<string> &words, vector<string> &coordinates);
	void showClues(vector<string> &words, vector<string> &coordinates);
private:
	
	vector<string> synonyms,
		tempCoord,
		tempWord;
};
#endif