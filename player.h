#ifndef player_h
#define player_h

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Player
{
public:
	Player(string name);
	double getTime(int initialTime, int finishTime);
private:
	string playerName;
	int //initialTime,
		  // finishTime,
		   elapsedTime;
};
#endif
