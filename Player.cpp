/*
Group Members:
(BCSF20A015-ZOHAIB ASLAM)
(BCSF20A020-ABDUL REHMAN)
(BCSF20A024-ALI AMANAT ALI)
*/
#define _CRT_SECURE_NO_WARNINGS
#include "Player.h"
Player::Player(int i, const char* n, int s, int b) :playerId(i), name(NULL), playerScore(s), ballsFaced(b)
{
	setname(n);
}
void Player::setname(const char* a) {
	if (a != NULL) {
		name = new char[strlen(a) + 1];
		strcpy(name, a);
	}
	else {
		name = new char;
		strcpy(name, "");
	}
}
void Player::setID(int id) {
	if (id > 0 && id<12)
		playerId = id;
	else 
	{
		cout << "You entered wrong id" << endl;
	}
}
void Player::addPlayerScore(int s)
{
	if (s>0)
	{
		playerScore += s;
	}
}
void Player::addBallsFaced()
{
	ballsFaced++;
}
Player:: ~Player() {
	if (name != NULL) 
	{
		delete[]name;
		name = NULL;
		playerId = 0;
	}
}
Player::Player(const Player& orig) :name(NULL)
{
	*this = orig;
}
Player& Player:: operator=(const Player& rhs) 
{
	if (this == &rhs)
	{
		return *this;
	}
	else 
	{
		if (name != NULL) 
		{
			delete[]name;
			name = NULL;
			playerId = 0;
			playerScore = 0;
			ballsFaced = 0;
		}
		setname(rhs.name);
		setID(rhs.playerId);
		playerScore = rhs.playerScore;
		ballsFaced = rhs.ballsFaced;
		return *this;
	}
}
