#ifndef player_h
#define player_h

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Player
{
public:
	Player(string name);
	string getTime(int initialTime, int finishTime);
	void saveFile(string savedFile, string elapsedTime, int tipAmount);
private:
	string playerName;
	int time;
};
#endif
