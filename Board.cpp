#include "Board.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Board::Board(unsigned int rows, unsigned int columns)
{
	this-> rows = rows;
    this-> columns = columns;

}

void Board::make()
{

	xy.resize(rows, vector<char> (columns, '.'));

}

void Board::show()
{
	cout << "   ";
    for (unsigned int i = 97; i < 97 + columns; i++)
    {
        cout << char(i) << ' ';
    }

    cout << endl;

	for (unsigned int k = 0; k < rows; k++)
	{
            cout << char(k + 65) << ' ';

            for (unsigned int j = 0; j < columns; j++)
            {
                cout << ' ' << xy[k][j];
            }
       
		cout << ' ' << endl;
	}   		
}

void Board::insert(string position, string word)
{
	//this->xy;
	//this->rows;

	// stop
	//if (word == crtl-z)

	char upperCase = position.at(0), lowerCase = position.at(1), orientation = position.at(2);
	unsigned int uC = ((int)upperCase - 65), lC = ((int)lowerCase - 97);

	/////create function just for this
	//verify size
	if ( (((int)upperCase + word.length()) > (65 + rows)) && (((int)lowerCase + word.length()) > (97 + columns)))
	{
		cerr << "That word does not fit in the place you want. Try again!" << endl << endl;
		exit(1);
	}
	//valid size
	else
	{
		if (orientation == 'V')
		{
			for (unsigned int i = uC, k = 0, j = lC; k < word.length(); i++, k++)
			{
				xy.at(i).at(j) = word.at(k);
			}
		}
		else
		{
			for (unsigned int i = uC, k = 0, j = lC; k < word.length(); j++, k++)
			{
				xy.at(i).at(j) = word.at(k);
			}
		}
	}
}

bool Board::usedword(string word)
{
	bool notPresent = true;

	for (unsigned int i = 0; i < taken.size(); i++)
	{
		if (taken.at(i) == word)
		{
			notPresent = false;
			cout << "You already used that word";
			break;
		}
		else
			taken.push_back(word);
	}

	return notPresent;
}

void Board::occupied(string position, string word)
{		
	char last = position.at(position.length() - 1);
	string coordenates = position.erase(position.size() - 1, 1);
	vector<string> aux;
	int counter = 0;
	string savepos;

	while (counter != word.size())
	{
		int changecolumn = (int)position.at(1) + counter;
		int changerow = (int)position.at(0) + counter;

		if (last == 'h')
		{
			savepos = position.at(0) + char(changecolumn);
				aux.push_back(savepos);
		}

		if (last == 'v')
		{
			savepos = position.at(1) + char(changerow);
			aux.push_back(savepos);
		}
			
		counter++
	}

	


	for (int i = 0; i < position.size() ; i++)
	{
		int changecolumn = (int)position.at(1) + counter;
		int changerow = (int)position.at(0) + counter;
		 
			if (position.at(2) == "h")
			{
				

				if (position == positionvec.at(i))

				
				positionvec.push_back(changed.substr(0, 2))
			}
		
			if (position.substr(0, 2) == positionvec.at(i))
		
			if()
		}
			cout << position.at(i);
	}

	if (position.at(2) == "h")
    {		
		positionvec.push_back(changed.substr(0, 2))
	}


	if (position.at(2) == "v"

	{
		changed = position.at(0).swap(position.at(0) + 1);
		positionvec.push_back(changed.substr(0, 2))
	}

	
}


