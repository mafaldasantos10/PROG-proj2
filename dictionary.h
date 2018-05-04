#ifndef dictionary_h
#define dictionary_h

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Dictionary
{
public:
	Dictionary(string thesaurusFile);
	bool isValid(string word);
	vector<string> validWords;
};
#endif