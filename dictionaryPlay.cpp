#include "dictionaryPlay.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

DictionaryPlay::DictionaryPlay(string thesaurusFile)
{
	string key;
	ifstream fin;
	int index;
	fin.open(thesaurusFile);

	//checks wether the indicated file is valid
	if (!fin.is_open())
	{
		cerr << "Input file not found!\n";
		exit(1);
	}

	string next;
	string words;


	//extracts the header words to a vector
	while (!fin.eof())
	{
		getline(fin, next);
		index = 0;
		for (unsigned int i = 0; i < next.length(); i++)
		{
			if (next.at(i) == ':')
			{
				//validWords.push_back(next.substr(0, i));
				key = next.substr(0, i);
				index = i + 2;
				break;
			}
			if (next.at(i) == ',')
			{
				mapped.push_back(next.substr(index, (next.find_first_of(',') - index)));
				index = i + 2;
			}


		}
		if (synonyms.count(key) != 0)
		{
			for (size_t i = 0; i < mapped.size(); i++)
				synonyms[key].push_back(mapped[i]);
		}
		else
		{
			synonyms.insert(pair <string, vector<string> >(key, mapped));

		}
		mapped.clear();

	}

	fin.close();
}

/*bool DictionaryPlay::isValid(string word, vector<string> validWords)
{
	bool present = false;
	// this->validWords;

	for (unsigned int i = 0; i < validWords.size(); i++)
	{
		//case insensitive comparison
		if (_strcmpi(word.c_str(), validWords.at(i).c_str()) == 0)
		{
			present = true;
			break;
		}
	}

	return present;
}*/