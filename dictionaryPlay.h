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
	bool isValid(string word, vector<string> validWords);
	vector<string> validWords;

private:
	map<string, vector<string> > synonyms;
	vector<string> mapped;
};
#endif