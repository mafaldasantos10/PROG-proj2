#include "player.h"

using namespace std;
ofstream fout;

Player::Player(string name)
{
	this->playerName = name;
}

//determines the time it took the player to finish the board
string Player::getTime(int initialTime, int finishTime)
{
	this->time;
	string elapsedTime;

	int hour = 0,
		min = 0,
		sec = 0;

	time = finishTime - initialTime;

	//converting time to HH:MM:SS
	hour = time / 3600;
	time = time % 3600;
	min = time / 60;
	time = time % 60;
	sec = time;

	// display data to user///////////
	elapsedTime = "Solved in: " + to_string(hour) + " hours, " + to_string(min) + " minutes and " + to_string(sec) + " seconds!";
	
	return elapsedTime;
}

//saves the statistics
void Player::saveFile(string savedFile, string elapsedTime, int tipAmount)
{
	string fileName,
		   next;

	//saves with the correct name format
	fileName = savedFile.insert(4, "_p");

	//opens the file that will will be written
	fout.open(fileName, std::ofstream::out | std::ofstream::app);

	fout << "Player: " + playerName << ". " << elapsedTime << " Used " << tipAmount << " tips to complete the board." << endl << endl;

	fout.close();

	cout << " Stats of the game saved to file: " << fileName << endl << endl;
}