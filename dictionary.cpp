#include "dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void Dictionary::dictionary(ifstream &thesaurus)
{
	string next;
	vector<string> validWords;

	while (!thesaurus.eof())
	{
		getline(thesaurus, next);

		for (unsigned int i = 0; i < next.length(); i++)
		{
			if (next.at(i) == ":")//idk
			{
				validWords.push_back(next.substr(0, (i - 1)));
				break;
			}
		}
	}

	for (unsigned int i = 0; i < validWords.size(); i++)
		cout << validWords.at(i);
}