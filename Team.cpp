/*
Group Members:
(BCSF20A015-ZOHAIB ASLAM)
(BCSF20A020-ABDUL REHMAN)
(BCSF20A024-ALI AMANAT ALI)
*/
#define _CRT_SECURE_NO_WARNINGS
#include "Team.h"
int Team::totalOvers = 0;
Team::Team() :distanceL(66), distanceW(3), distanceH(4)
{
	for (int i = 0; i < 11; i++)
	{
		players[i] = NULL;
	}
	overs = 0;
	teamID = 0;
	wickets = 0;
	balls = 0;
	score = 0;
	statusWin = false;
	statusDraw = false;
	noB = false;
	wd = false;
	extras = 0;
	teamName = new char;
	strcpy(teamName, "");
}
Team::~Team()
{
	if (teamName != NULL)
	{
		delete[]teamName;
		teamName = NULL;
	}
}
void Team::setTeamName(const char* n)
{
	if (n != NULL)
	{
		teamName = new char[strlen(n) + 1];
		strcpy(teamName, n);
	}
	else 
	{
		teamName = new char;
		strcpy(teamName, "");
	}
}
void Team::setTeamID(int i)
{
	if (i > 0 && i < 6)
	{
		teamID = i;
	}
	else
	{
		cout << "Id is invalid: " << endl;
	}
}
void Team::addPlayer(Player* pl, int i)
{
	players[i - 1] = pl;
}
void Team::addPlyrScr(int id, int s)
{
	players[id - 1]->addPlayerScore(s);
}
void Team::addBallsPlyr(int id)
{
	players[id - 1]->addBallsFaced();
}
void Team::BattingOrder(int a, int b)
{
	char temp[50];
	strcpy(temp, players[a - 1]->getname());
	players[a - 1]->setname(players[b - 1]->getname());
	players[b - 1]->setname(temp);
}
void Team::displayTeam()const
{
	for (int i = 0; i < 11; i++)
	{
		cout << left << setw(5) << players[i]->getID();
		cout << left << setw(35) << players[i]->getname();
		cout << endl;
	}
}
void Team::addExtras()
{
	extras++;
}
void Team::displayScoreBoard()const
{
	cout << "---------------------------------------------" << endl;
	cout << "SCORE BOARD OF " << getTeamName() << endl;
	cout << "---------------------------------------------" << endl;
	for (int i = 0; i < 11; i++)
	{
		cout << left << setw(5) << players[i]->getID();
		cout << left << setw(20) << players[i]->getname();
		cout << " " << left << setw(4) << players[i]->getPlayerScore() << "(" << players[i]->getBallsFaced() << ")";
		cout << endl;
	}
	cout << "---------------------------------------------" << endl;
	cout << "Total Score: " << score << "/" << wickets << right << setw(25) << "Extras: " << extras << endl;
	cout << "---------------------------------------------" << endl;
}
bool Team::tossDecision()
{
	toss = rand() % 2;
	if (toss == 1)
	{
		return true;
	}
	return false;
}
void Team::setTotalOvers(int o)
{
	totalOvers = o;
}
void Team::ball()
{
	balls++;
	if (balls == 6)
	{
		balls = 0;
		overs += 1;
	}
}
bool Team::wide(double w)const
{
	if (w > distanceW)
	{
		return true;
	}
	return false;
}
bool Team::noBall(double n)const
{
	if (n < distanceL)
	{
		return true;
	}
	return false;
}
bool Team::bouncer(double b)const
{
	if (b >= distanceH)
	{
		return true;
	}
	return false;
}
bool Team::spin(double s)const
{
	if (s >= 5 || s <= -5)
	{
		return true;
	}
	return false;
}
void Team::setIsStrike(bool b)
{
	isStrike = b;
}
void Team::randomStrike()
{
	int a = rand() % 4;
	if (a == 0)
	{
		setIsStrike(false);
	}
	else
	{
		setIsStrike(true);
	}
}
void Team::wideRandomStrike()
{
	int a = rand() % 4;
	if (a == 0)
	{
		setIsStrike(true);
	}
	else
	{
		setIsStrike(false);
	}
}
void Team::decisionGame(const Team& opp)
{
	if (score > opp.score)
	{
		statusWin = true;
		cout << "Congratulations you have won this game" << endl;
	}
	else if (score < opp.score)
	{
		statusWin = false;
		cout << "You have lost the game. Better luck next time" << endl;
	}
	else
	{
		statusDraw = true;
		cout << "The score of both teams is equal so the match is drawn" << endl;
	}
}
void Team::userBowling(Team& opp)
{
	if (score != 0)
	{
		cout << "---------------------------------------------" << endl;
		cout << "Total Score: " << opp.score << "/" << opp.wickets << " in " << overs << "." << balls << " Overs" << "\tRemaining: " << (score + 1 - opp.score) << endl;
		cout << "---------------------------------------------" << endl;
	}
	else
	{
		cout << "-------------------------------------" << endl;
		cout << "Total Score: " << opp.score << "/" << opp.wickets << " in " << overs << "." << balls << " Overs" << endl;
		cout << "-------------------------------------" << endl;
	}
	double l, w, h, angle;
	cout << "Enter the Length of Ball (64-70) : ";
	cin.clear();
	cin.ignore(127, '\n');
	while (!(cin>>l)||true)
	{
		if (!cin)
		{
			cin.clear();
			cin.ignore(127, '\n');
			cout << "Please enter the right input! ";
			continue;
		}
		else
		{
			if (!(l >= 64 && l <= 70))
			{
				cin.clear();
				cin.ignore(127, '\n');
				cout << "Please enter a valid value (64-70) for the length of the ball: ";
			}
			else
			{
				break;
			}
		}
	}
	cout << "Enter the width of the Ball (0-5) : ";
	cin.clear();
	cin.ignore(127, '\n');
	while (!(cin >> w) || true)
	{
		if (!cin)
		{
			cin.clear();
			cin.ignore(127, '\n');
			cout << "Please enter the right input! ";
			continue;
		}
		else
		{
			if (!(w >= 0 && w <= 5))
			{
				cin.clear();
				cin.ignore(127, '\n');
				cout << "Please enter a valid value (0-5) for the width of the ball: ";
			}
			else
			{
				break;
			}
		}
	}
	cout << "Enter the Height of the Ball (0-7) : ";
	cin.clear();
	cin.ignore(127, '\n');
	while (!(cin >> h) || true)
	{
		if (!cin)
		{
			cin.clear();
			cin.ignore(127, '\n');
			cout << "Please enter the right input! ";
			continue;
		}
		else
		{
			if (!(h >= 0 && h <= 7))
			{
				cin.clear();
				cin.ignore(127, '\n');
				cout << "Please enter a valid value (0-7) for the height of the ball: ";
			}
			else
			{
				break;
			}
		}
	}
	cout << "Enter the Angle of deviation of the Ball (-8 <-> 8) : ";
	cin.clear();
	cin.ignore(127, '\n');
	while (!(cin >> angle) || true)
	{
		if (!cin)
		{
			cin.clear();
			cin.ignore(127, '\n');
			cout << "Please enter the right input! ";
			continue;
		}
		else
		{
			if (!(angle <= 8 && angle >= -8))
			{
				cin.clear();
				cin.ignore(127, '\n');
				cout << "Please enter a valid value (-8 <-> 8) for the angle of deviation of the ball: ";
			}
			else
			{
				break;
			}
		}
	}
	if (score != 0)
	{
		cout << "---------------------------------------------" << endl;
	}
	else
	{
		cout << "-------------------------------------" << endl;
	}
	if (noBall(l))		//No Ball
	{
		noB = true;
		wd = false;
		opp.score++;
		opp.randomStrike();
		if (opp.isStrike)
		{
			cout << "The oppononet has striked the ball" << endl;
			int c = rand() % 2;
			if (c == 0)
			{
				opp.score += 4;
			}
			else
			{
				opp.score += 6;
			}
		}
		else
		{
			cout << "The opponent has not striked the ball" << endl;
		}
	}
	else if (wide(w))		//Wide Ball
	{
		noB = false;
		opp.wideRandomStrike();
		if (opp.isStrike)
		{
			ball();
			cout << "The oppononet has striked the ball" << endl;
			opp.score += 4;
		}
		else
		{
			wd = true;
			cout << "The opponent has not striked the ball" << endl;
			opp.score++;
		}
	}
	else if (bouncer(h) || spin(angle))
	{
		noB = false;
		wd = false;
		ball();
		if (bouncer(h))		//Bouncer
		{
			opp.randomStrike();
			if (opp.isStrike)
			{
				cout << "The opponent has striked the ball\n";
				int a = rand() % 8;
				if (a == 3 || a == 5)
				{
					if (a == 3)
					{
						opp.catchOut();
					}
					else if (a==5)
					{
						opp.hitWicket();
					}
				}
				else
				{
					opp.score += 6;
				}
			}
			else
			{
				cout << "The opponent has not striked the ball" << endl;
			}
		}
		else			//Spin Ball
		{
			opp.randomStrike();
			if (opp.isStrike)
			{
				cout << "The oppononet has striked the ball" << endl;
				int s = rand() % 9;
				if (s == 5)
				{
					opp.catchOut();
				}
				else if (s == 7)
				{
					opp.hitWicket();
				}
				else
				{
					int c = rand() % 5;
					if (c == 1)
					{
						opp.score += 1;
					}
					else if (c == 2)
					{
						opp.score += 2;
					}
					else if (c == 3)
					{
						opp.score += 4;
					}
					else if (c == 4)
					{
						opp.score += 6;
					}
				}
			}
			else
			{
				cout << "The opponent has not striked the ball\n";
				int a = rand() % 5;
				if (a == 2 || a == 3)
				{
					opp.lbw();
				}
			}
		}
	}
	else			//Normal Ball
	{
		wd = false;
		noB = false;
		ball();
		opp.randomStrike();
		if (opp.isStrike)
		{
			cout << "The opponent has striked the ball" << endl;
			int s = rand() % 8;
			if (s == 5 || s == 7)
			{
				if (s == 5)
				{
					opp.catchOut();
				}
				else if (s==7)
				{
					opp.hitWicket();
				}
			}
			else
			{
				{
					int a = rand() & 5;
					if (a == 0)
					{
						opp.score++;
					}
					else if (a == 1)
					{
						opp.score += 2;
					}
					else if (a == 2)
					{
						opp.score += 3;
					}
					else if (a == 3)
					{
						opp.score += 4;
					}
					else if (a == 4)
					{
						opp.score += 6;
					}
				}
			}
		}
		else
		{
			cout << "The opponent has not striked the ball" << endl;
			int a = rand() % 4;
			if (a == 3)
			{
				opp.lbw();
			}
		}
	}
}
void Team::userBating(Team& op)
{
	if (op.score != 0)
	{
		cout << "---------------------------------------------" << endl;
		cout << "Total Score: " << score << "/" << wickets << " in " << op.overs << "." << op.balls << " Overs" << "\tRemaining: " << (op.score + 1 - score) << endl;
		cout << "---------------------------------------------" << endl;
	}
	else
	{
		cout << "-------------------------------------" << endl;
		cout << "Total Score: " << score << "/" << wickets << " in " << op.overs << "." << op.balls << " Overs" << endl;
		cout << "-------------------------------------" << endl;
	}
	char c;
	cout << "Do you want to strike (Y/N)? ";
	cin.clear();
	cin.ignore(127, '\n');
	cin >> c;
	while (!(c == 'y' || c == 'Y') && !(c == 'n' || c == 'N'))
	{
		cin.clear();
		cin.ignore(127, '\n');
		cout << "Please Choose between Y/N: ";
		cin >> c;
	}
	if (c == 'y' || c == 'Y')
	{
		setIsStrike(true);
	}
	else if (c == 'n' || c == 'N')
	{
		setIsStrike(false);
	}
	double l = static_cast<double>((rand() % 10) + 65);
	double w = static_cast<double>((rand() % 6)-2);
	double h = static_cast<double>(rand() % 5);
	double angle = static_cast<double>((rand() % 13) - 6);
	if (op.noBall(l))		//No Ball
	{
		op.noB = true;
		op.wd = false;
		score++;
		if (isStrike)
		{
			int c = rand() % 2;
			if (c == 0)
			{
				score += 4;
			}
			else
			{
				score += 6;
			}
		}
	}
	else if (op.wide(w))		//Wide Ball
	{
		op.noB = false;
		if (isStrike)
		{
			score += 4;
			op.ball();
		}
		else
		{
			op.wd = true;
			score++;
		}
	}
	else if (op.bouncer(h) || op.spin(angle))
	{
		op.wd = false;
		op.noB = false;
		op.ball();
		if (op.bouncer(h))		//Bouncer
		{
			if (isStrike)
			{
				int a = rand() % 9;
				if (a == 5 || a == 7)
				{
					if (a == 5)
					{
						catchOut();
					}
					else if (a==7)
					{
						hitWicket();
					}
				}
				else
				{
					score += 6;
				}
			}
		}
		else				//Spin Ball
		{
			if (isStrike)
			{
				int s = rand() % 8;
				if (s == 4)
				{
					catchOut();
				}
				else if (s == 6)
				{
					hitWicket();
				}
				else
				{
					int c = rand() % 5;
					if (c == 1)
					{
						score += 1;
					}
					else if (c == 2)
					{
						score += 2;
					}
					else if (c == 3)
					{
						score += 4;
					}
					else if (c == 4)
					{
						score += 6;
					}
				}
			}
			else
			{
				int s = rand() % 5;
				if (s == 2 || s == 4)
				{
					lbw();
				}
			}
		}
	}
	else             //Normal Ball
	{
		op.wd = false;
		op.noB = false;
		op.ball();
		if (isStrike)
		{
			int s = rand() % 8;
			if (s == 5 || s == 7)
			{
				if (s == 5)
				{
					catchOut();
				}
				else if ( s == 7 )
				{
					hitWicket();
				}
			}
			else
			{
				int a = rand() & 5;
				if (a == 0)
				{
					score++;
				}
				else if (a == 1)
				{
					score += 2;
				}
				else if (a == 2)
				{
					score += 3;
				}
				else if (a == 3)
				{
					score += 4;
				}
				else if (a == 4)
				{
					score += 6;
				}
			}
		}
		else
		{
			int a = rand() % 4;
			if (a == 3)
			{
				lbw();
			}
		}
	}
}