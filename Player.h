#pragma once
#include<iostream>
#include<cstring>
using namespace std;
class Player
{
private:
	int playerId;
	char* name;
	int playerScore;
	int ballsFaced;
public:
	Player(int i = 0, const char* n = NULL, int s=0, int b=0);
	void setname(const char* a);
	const  char* getname()const { return name; }
	void setID(int);
	int getID()const { return playerId; }
	void addPlayerScore(int);
	int getPlayerScore()const{ return playerScore; }
	void addBallsFaced();
	int getBallsFaced()const{ return ballsFaced; }
	~Player();
	Player(const Player&);
	Player & operator=(const Player&);
};
