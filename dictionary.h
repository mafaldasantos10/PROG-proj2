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
	void isValid(string word);
private:
	vector<string> validWords;
};

#endif