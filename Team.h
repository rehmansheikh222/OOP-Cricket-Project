#pragma once
#include "Player.h"
#include <iomanip>
#include <ctime>
#include <cstdlib>
class Team
{
private:
	static int totalOvers;
	Player* players[11];  //Aggregation Behaviour
	int teamID, wickets, balls, score;
	bool statusWin, statusDraw;
	char* teamName;
	int toss;
	const double distanceL;  //66 feet
	const double distanceW;  //3 feet
	const double distanceH;  // abouve 4 feet otherwise ball is normal 
	bool isStrike;
	bool wd, noB;
	int overs;
	int extras;
public:
	Team();
	~Team();
	void addPlayer(Player*, int);
	void setTeamName(const char *n);
	const char* getTeamName()const { return teamName; }
	void setTeamID(int i);
	int getTeamID()const { return teamID; }
	int getScore()const{ return score; }
	const char* getPlayerName(int id)const { return players[id - 1]->getname(); }
	void addPlyrScr(int, int);
	int getPlyrScr(int id)const { return players[id - 1]->getPlayerScore(); }
	void addBallsPlyr(int);
	int getBallsPlyr(int id)const { return players[id-1]->getBallsFaced(); }
	void BattingOrder(int, int);
	void displayTeam()const;
	void addExtras();
	void displayScoreBoard()const;
	bool tossDecision();
	void userBowling(Team & opp);
	void ball();
	static void setTotalOvers(int);
	int getTotalOvers()const { return totalOvers; }
	int getOvers()const{ return overs; }
	int getWickets()const{ return wickets; }
	bool getStatusWin()const{ return statusWin; }
	bool getStatusDraw()const{ return statusDraw; }
	void decisionGame(const Team&);
	int getBall()const{ return balls; }
	bool wide(double)const;
	bool noBall(double)const;
	bool bouncer(double)const;
	bool spin(double)const;
	bool getNb()const{ return noB; }
	bool getWd()const{ return wd; }
	void setIsStrike(bool);
	void randomStrike();
	void wideRandomStrike();
	void hitWicket(){ wickets++; cout << "-----------------------" << endl; cout << "HitWicket!" << endl; }
	void catchOut(){ wickets++; cout << "-----------------------" << endl; cout << "Catch Out!" << endl; }
	void lbw(){ wickets++; cout << "-----------------------" << endl; cout << "LBW!" << endl; }
	void userBating(Team&);
};