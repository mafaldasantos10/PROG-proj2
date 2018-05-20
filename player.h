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

	/* getTime
	PURPOSE: 
	 - determines the time it took the player to finish the game
	PARAMETERS:
	 - int initialTime: time when the user started playing
	 - int finishTime: time when the user finished playing
	RETURNS:
	 - string with the time taken by the user in HH:MM:SS
	*/
	string getTime(int initialTime, int finishTime);

	/* saveFile
	PURPOSE:
	- saves the stats of the game in the file format BXXX_p.txt (where BXXX.txt is the file used to load the current board)
	PARAMETERS:
	- string savedFile: file that was used to load the current game
	- string elapsedTime: string with the time taken by the user in HH:MM:SS
	- int tipAmount: amount of tips used by the user to complete the board
	*/
	void saveFile(string savedFile, string elapsedTime, int tipAmount);
private:
	string playerName; //name of the player
	int time; //time taken by the user to finish (determined)
};
#endif
