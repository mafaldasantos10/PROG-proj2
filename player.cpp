#include "player.h"

using namespace std;

Player::Player(string name)
{
	this->playerName = name;
}

//determines the time it took the player to finish the board
double Player::getTime(int initialTime, int finishTime)
{
	this->elapsedTime;

	// declare variables
	int hour = 0,
		min = 0,
		sec = 0;

	elapsedTime = finishTime - initialTime;

	// using the time from ^ above, convert 
	// secs to HH:MM:SS format using division
	// and modulus
	hour = elapsedTime / 3600;
	elapsedTime = elapsedTime % 3600;
	min = elapsedTime / 60;
	elapsedTime = elapsedTime % 60;
	sec = elapsedTime;

	// display data to user
	cout << endl << "The player took: " << hour << " hours, "
		         << min << " minutes, and " << sec << " seconds!" << endl << endl;
	
	return elapsedTime;
}
