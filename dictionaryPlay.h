#ifndef dictionaryPlay_h
#define dictionaryPlay_h

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class DictionaryPlay
{
public:
	DictionaryPlay(string thesaurusFile);
	bool isValid(string word, vector<string> validWords);
	vector<string> validWords;
	void show();
private:
	vector<string> synonymes;
};
#endif
