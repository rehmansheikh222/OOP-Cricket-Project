/*
Group Members:
(BCSF20A015-ZOHAIB ASLAM)
(BCSF20A020-ABDUL REHMAN)
(BCSF20A024-ALI AMANAT ALI)
*/
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include "Team.h"
#include <string>
#include <fstream>
void inputValue(int st, int end, int& val)
{
	while (!(cin >> val) || true)
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
			if (!(val >= st&&val <= end))
			{
				cin.clear();
				cin.ignore(127, '\n');
				cout << "Please enter the right input! ";
			}
			else if (val >= st&&val <= end)
			{
				break;
			}
		}
	}
}
int checkRepitition(int* arr, int &val, int j, int i)
{
	if (j < 0)
	{
		return val;
	}
	if (val != arr[j])
	{
		checkRepitition(arr, val, j - 1, i);
	}
	else
	{
		cout << "Player is already selected\nSelect another player: ";
		inputValue(1, 16, val);
		j = i;
		checkRepitition(arr, val, j, i);
	}
}
void play() {
	fstream fin("teamPlayers.txt", ios::in);
	if (!fin) {
		cout << "file not found : " << endl;
		exit(1);
	}
	cout << "Select your team from the following." << endl;
	cout << "1. Pakistan" << endl;
	cout << "2. Australia" << endl;
	cout << "3. New Zealand" << endl;
	cout << "4. Zimbabwe" << endl;
	cout << "5. Sri Lanka" << endl;
	int tem, oponent;
	cin.clear();
	cin.ignore(127, '\n');
	cout << "Enter your team: ";
	inputValue(1, 6, tem);
	cin.clear();
	cin.ignore(127, '\n');
	cout << "Enter your opponent's team: ";
	while (!(cin >> oponent)|| true)
	{
		if (!cin)
		{
			cin.clear();
			cin.ignore(127, '\n');
			cout << "Please enter the right input! ";
			continue;
		}
		if (oponent == tem)
		{
			cin.clear();
			cin.ignore(127, '\n');
			cout << "Please select another team ";
			continue;
		}
		else if (!(oponent > 0 && oponent < 6))
		{
			cin.clear();
			cin.ignore(127, '\n');
			cout << "Please enter the right input! ";
		}
		else
		{
			break;
		}
	}
	cin.clear();
	cin.ignore(127, '\n');
	int ov;
	cout << "Enter the number of overs for the game (5,10,20): ";
	while (!(cin>>ov) || true)
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

			if (!(ov == 10 || ov == 20 || ov == 5))
			{
				cin.clear();
				cin.ignore(127, '\n');
				cout << "Please enter the right input! ";
			}
			else
			{
				break;
			}
		}
	}
	Team::setTotalOvers(ov);
	char arr[1000];
	Team t, t1;
	t.setTeamID(tem);
	fin.seekg(42 * 17 * (tem - 1));
	fin.get(arr, 10);
	t.setTeamName(arr);
	system("CLS");
	for (int i = 0; i < 17; i++)
	{
		fin.seekg(42 * (((17 * (tem - 1))) + i));
		fin.get(arr, 40);
		cout << arr << endl;
	}
	int select;
	cout << "------------------------------------------" << endl;
	cout << "Select your squard of 11 players: " << endl;
	cout << "------------------------------------------" << endl;
	Player p[11];
	char pname[100];
	int position;
	int ar[16];
	for (int i = 0; i < 11; i++)
	{
		cout << "Select player No " << i + 1 << ": ";
		cin.clear();
		cin.ignore(127, '\n');
		inputValue(1, 16, select);
		int j = i - 1;
		ar[i] = checkRepitition(ar, select, j, i - 1);

		position = (16 * (tem - 1) + tem) * (42) + (42 * (select - 1) + 5);
		fin.seekg(position);
		fin.get(pname, 20);
		p[i].setname(pname);
		p[i].setID(i + 1);
	}
	for (int i = 0; i < 11; i++)
	{
		t.addPlayer(&p[i], p[i].getID());
	}
	system("CLS");
	cout << "------------------------------------------" << endl;
	cout << "Your selected Team is: " << endl;
	cout << "------------------------------------------" << endl;
	t.displayTeam();
	bool f = false;
	char s1;
	do {
		int id, pos;
		cout << "Do you want to modify the batting order(Y / N) ?" << endl;
		cin.clear();
		cin.ignore(127, '\n');
		cin >> s1;
		while (!(s1 == 'y' || s1 == 'Y') && !(s1 == 'n' || s1 == 'N'))
		{
			cin.clear();
			cin.ignore(127, '\n');
			cout << "Please Choose between Y/N: ";
			cin >> s1;
		}
		if (s1 == 'y' || s1 == 'Y')
		{
			f = true;
			cout << "Please enter the id number of the players which needs to be modified:" << endl;
			cin.clear();
			cin.ignore(127, '\n');
			inputValue(1, 11, id);
			cout << "Please specify the position number in the team to insert the player:" << endl;
			cin.clear();
			cin.ignore(127, '\n');
			inputValue(1, 11, pos);
			t.BattingOrder(id, pos);
		}
	} while ((s1 == 'y' || s1 == 'Y'));
	system("CLS");
	cout << "------------------------------------------" << endl;
	cout << "Your Selected Team " << endl;
	cout << "------------------------------------------" << endl;
	t.displayTeam();
	cout << "------------------------------------------" << endl;
	cout << "Press any key to see your opponent team . . . ";
	_getch();
	system("CLS");
	t1.setTeamID(oponent);
	char arr1[1000];
	fin.seekg(42 * 17 * (oponent - 1));
	fin.get(arr1, 10);
	t1.setTeamName(arr1);
	Player p1[11];
	for (int i = 0; i < 11; i++)
	{
		position = (16 * (oponent - 1) + oponent) * (42) + (42 * (i)+5);
		fin.seekg(position);
		fin.get(pname, 20);
		p1[i].setname(pname);
		p1[i].setID(i + 1);
	}
	for (int i = 0; i < 11; i++)
	{
		t1.addPlayer(&p1[i], p1[i].getID());
	}
	cout << "------------------------------------------" << endl;
	cout << "Your Opponent Team " << endl;
	cout << "------------------------------------------" << endl;
	t1.displayTeam();
	cout << "------------------------------------------" << endl; fin.close();
	cout << "Press any key for the toss of the match . . . ";
	_getch();
	system("CLS");

	unsigned seed = time(0);
	srand(seed);
	cout << "Toss\n";
	cout << "Heads or Tails?" << endl;
	cout << right << setw(5) << "1." << right << setw(8) << "Heads" << endl;
	cout << right << setw(5) << "2." << right << setw(8) << "Tails" << endl;
	int ts;
	cout << "Enter your choice: ";
	cin.clear();
	cin.ignore(127, '\n');
	inputValue(1, 2, ts);
	bool lose = false;
	int win =0;
	if (t.tossDecision())
	{
		cout << "Congratulations! You won the toss.. Would you like to bat or bowl?\n";
		cout << right << setw(5) << "1." << right << setw(5) << "Bat" << endl;
		cout << right << setw(5) << "2." << right << setw(6) << "Bowl" << endl;
		cin.clear();
		cin.ignore(127, '\n');
		inputValue(1, 2, win);
	}
	else
	{
		int c = rand() % 2;
		if (c == 1)
		{
			cout << "Sorry you lost the toss.. The opponent has chosen to bat\n";
			lose = true;
		}
		else
		{
			cout << "Sorry you lost the toss.. The opponent has chosen to bowl\n";
		}
	}
	cout << "Press any key to start the game . . . ";
	_getch();
	system("CLS");
	if (lose || win == 2)
	{
		string arr = "";
		int strikerId = 1, nonStrikerId = 2;
		cout << "-------------------------------------" << endl;
		cout << t1.getPlayerName(strikerId) << " " << t1.getPlyrScr(strikerId) << " (" << t1.getBallsPlyr(strikerId) << ")" << endl;
		cout << t1.getPlayerName(nonStrikerId) << " " << t1.getPlyrScr(nonStrikerId) << " (" << t1.getBallsPlyr(nonStrikerId) << ")" << endl;
		while (t1.getWickets() < 10 && t.getOvers() < t.getTotalOvers())
		{
			static int count = 0;
			int previous = t1.getScore();
			int pr = t.getBall();
			int p = t.getOvers();
			int pw = t1.getWickets();
			t.userBowling(t1);
			int scr = t1.getScore() - previous;
			if (pw < t1.getWickets())
			{
				t1.addBallsPlyr(strikerId);
				cout << "WICKET of " << t1.getPlayerName(strikerId) << endl;
				cout << "-----------------------" << endl;
				if (t1.getWickets()<10)
				{
					if (strikerId>nonStrikerId)
					{
						strikerId++;
					}
					else if (strikerId < nonStrikerId)
					{
						strikerId = nonStrikerId + 1;
					}
				}
				arr += "W ";
			}
			else if (pr == t.getBall())
			{
				if (t.getNb())
				{
					arr += to_string(scr) + "N ";
					t1.addPlyrScr(strikerId, scr - 1);
					t1.addExtras();
				}
				else if (t.getWd())
				{
					arr += "Wd ";
					t1.addExtras();
				}
			}
			else
			{
				if (scr % 2 == 0)
				{
					t1.addPlyrScr(strikerId, scr);
					t1.addBallsPlyr(strikerId);
				}
				else
				{
					t1.addPlyrScr(strikerId, scr);
					t1.addBallsPlyr(strikerId);
					strikerId += nonStrikerId;
					nonStrikerId = strikerId - nonStrikerId;
					strikerId = strikerId - nonStrikerId;
				}
				arr += to_string(scr) + " ";
			}
			cout << "Current Over: ";
			cout << arr;
			cout << endl;
			cout << "-------------------------------------" << endl;
			cout << t1.getPlayerName(strikerId) << " " << t1.getPlyrScr(strikerId) << " (" << t1.getBallsPlyr(strikerId) << ")" << endl;
			cout << t1.getPlayerName(nonStrikerId) << " " << t1.getPlyrScr(nonStrikerId) << " (" << t1.getBallsPlyr(nonStrikerId) << ")" << endl;
			count++;
			if (p != t.getOvers())
			{
				if (scr % 2 == 0)
				{
					strikerId += nonStrikerId;
					nonStrikerId = strikerId - nonStrikerId;
					strikerId = strikerId - nonStrikerId;
				}
				count = 0;
				arr = "";
			}
			if (t1.getWickets() == 10 || t.getOvers() == t.getTotalOvers())
			{
				cout << "-------------------------------------" << endl;
				cout << "Total Score: " << t1.getScore() << "/" << t1.getWickets() << " in " << t.getOvers() << "." << t.getBall() << " Overs" << endl;
				cout << "-------------------------------------" << endl;
				cout << "\n";
				cout << "FIRST INNINGS is completed" << endl;
			}
		}
		cout << "Press any key to see the Score Board . . . ";
		_getch();
		system("CLS");
		t1.displayScoreBoard();
		cout << t.getTeamName() << " needs to score " << t1.getScore() + 1 << " runs to win the game.." << endl;
		cout << "Press any key to start your batting . . . ";
		_getch();
		system("CLS");
		string arr1 = "";
		cout << "                                          ------------" << endl;
		cout << "                                           Target: " << t1.getScore() + 1 << endl;
		cout << "                                          ------------" << endl;
		strikerId = 1;
		nonStrikerId = 2;
		cout << "---------------------------------------------" << endl;
		cout << t.getPlayerName(strikerId) << " " << t.getPlyrScr(strikerId) << " (" << t.getBallsPlyr(strikerId) << ")" << endl;
		cout << t.getPlayerName(nonStrikerId) << " " << t.getPlyrScr(nonStrikerId) << " (" << t.getBallsPlyr(nonStrikerId) << ")" << endl;
		while ((t.getWickets() < 10 && t1.getOvers() < t1.getTotalOvers()) && (t.getScore() <= t1.getScore()))
		{
			static int count = 0;
			int previous = t.getScore();
			int pr = t1.getBall();
			int p = t1.getOvers();
			int pw = t.getWickets();
			t.userBating(t1);
			int scr = t.getScore() - previous;
			if (pw < t.getWickets())
			{
				t.addBallsPlyr(strikerId);
				cout << "WICKET of " << t.getPlayerName(strikerId) << endl;
				cout << "-----------------------" << endl;
				if (t.getWickets()<10)
				{
					if (strikerId>nonStrikerId)
					{
						strikerId++;
					}
					else if (strikerId < nonStrikerId)
					{
						strikerId = nonStrikerId + 1;
					}
				}
				arr1 += "W ";
			}
			else if (pr == t1.getBall())
			{
				if (t1.getNb())
				{
					arr1 += to_string(scr) + "N ";
					t.addPlyrScr(strikerId, scr - 1);
					t.addExtras();
				}
				else if (t1.getWd())
				{
					arr1 += "Wd ";
					t.addExtras();
				}
			}
			else
			{
				if (scr % 2 == 0)
				{
					t.addPlyrScr(strikerId, scr);
					t.addBallsPlyr(strikerId);
				}
				else
				{
					t.addPlyrScr(strikerId, scr);
					t.addBallsPlyr(strikerId);
					strikerId += nonStrikerId;
					nonStrikerId = strikerId - nonStrikerId;
					strikerId = strikerId - nonStrikerId;
				}
				arr1 += to_string(scr) + " ";
			}
			cout << "Current Over: ";
			cout << arr1;
			cout << endl;
			cout << "---------------------------------------------" << endl;
			cout << t.getPlayerName(strikerId) << " " << t.getPlyrScr(strikerId) << " (" << t.getBallsPlyr(strikerId) << ")" << endl;
			cout << t.getPlayerName(nonStrikerId) << " " << t.getPlyrScr(nonStrikerId) << " (" << t.getBallsPlyr(nonStrikerId) << ")" << endl;
			count++;
			if (p != t1.getOvers())
			{
				if (scr % 2 == 0)
				{
					strikerId += nonStrikerId;
					nonStrikerId = strikerId - nonStrikerId;
					strikerId = strikerId - nonStrikerId;
				}
				count = 0;
				arr1 = "";
			}
		}
		cout << "---------------------------------------------" << endl;
		cout << "Total Score: " << t.getScore() << "/" << t.getWickets() << " in " << t1.getOvers() << "." << t1.getBall() << " Overs" << endl;
		cout << "---------------------------------------------" << endl;
		t.decisionGame(t1);
		cout << "Press any key to see the Score Board . . . ";
		_getch();
		system("CLS");
		t.displayScoreBoard();
	}
	else
	{
		string arr = "";
		int strikerId = 1, nonStrikerId = 2;
		cout << "-------------------------------------" << endl;
		cout << t.getPlayerName(strikerId) << " " << t.getPlyrScr(strikerId) << " (" << t.getBallsPlyr(strikerId) << ")" << endl;
		cout << t.getPlayerName(nonStrikerId) << " " << t.getPlyrScr(nonStrikerId) << " (" << t.getBallsPlyr(nonStrikerId) << ")" << endl;
		while (t.getWickets() < 10 && t1.getOvers() < t1.getTotalOvers())
		{
			static int count = 0;
			int previous = t.getScore();
			int pr = t1.getBall();
			int p = t1.getOvers();
			int pw = t.getWickets();
			t.userBating(t1);
			int scr = t.getScore() - previous;
			if (pw < t.getWickets())
			{
				t.addBallsPlyr(strikerId);
				cout << "WICKET of " << t.getPlayerName(strikerId) << endl;
				cout << "-----------------------" << endl;
				if (t.getWickets()<10)
				{
					if (strikerId>nonStrikerId)
					{
						strikerId++;
					}
					else if (strikerId < nonStrikerId)
					{
						strikerId = nonStrikerId + 1;
					}
				}
				arr += "W ";
			}
			else if (pr == t1.getBall())
			{
				if (t1.getNb())
				{
					arr += to_string(scr) + "N ";
					t.addPlyrScr(strikerId, scr - 1);
					t.addExtras();
				}
				else if (t1.getWd())
				{
					arr += "Wd ";
					t.addExtras();
				}
			}
			else
			{
				if (scr % 2 == 0)
				{
					t.addPlyrScr(strikerId, scr);
					t.addBallsPlyr(strikerId);
				}
				else
				{
					t.addPlyrScr(strikerId, scr);
					t.addBallsPlyr(strikerId);
					strikerId += nonStrikerId;
					nonStrikerId = strikerId - nonStrikerId;
					strikerId = strikerId - nonStrikerId;
				}
				arr += to_string(scr) + " ";
			}
			cout << "Current Over: ";
			cout << arr;
			cout << endl;
			cout << "-------------------------------------" << endl;
			cout << t.getPlayerName(strikerId) << " " << t.getPlyrScr(strikerId) << " (" << t.getBallsPlyr(strikerId) << ")" << endl;
			cout << t.getPlayerName(nonStrikerId) << " " << t.getPlyrScr(nonStrikerId) << " (" << t.getBallsPlyr(nonStrikerId) << ")" << endl;
			count++;
			if (p != t1.getOvers())
			{
				if (scr % 2 == 0)
				{
					strikerId += nonStrikerId;
					nonStrikerId = strikerId - nonStrikerId;
					strikerId = strikerId - nonStrikerId;
				}
				count = 0;
				arr = "";
			}
			if (t1.getOvers() == t1.getTotalOvers() || t.getWickets() == 10)
			{
				cout << "-------------------------------------" << endl;
				cout << "Total Score: " << t.getScore() << "/" << t.getWickets() << " in " << t1.getOvers() << "." << t1.getBall() << " Overs" << endl;
				cout << "-------------------------------------" << endl;
				cout << "\n";
				cout << "FIRST INNINGS is completed\n";
			}
		}
		cout << "Press any key to see the Score Board . . . ";
		_getch();
		system("CLS");
		t.displayScoreBoard();
		cout << t1.getTeamName() << " needs to score " << t.getScore() + 1 << " runs to win the game.." << endl;
		cout << "Press any key to start your Bowling . . . ";
		_getch();
		system("CLS");
		string arr1 = "";
		cout << "                                          ------------" << endl;
		cout << "                                           Target: " << t.getScore() + 1 << endl;
		cout << "                                          ------------" << endl;
		strikerId = 1;
		nonStrikerId = 2;
		cout << "---------------------------------------------" << endl;
		cout << t1.getPlayerName(strikerId) << " " << t1.getPlyrScr(strikerId) << " (" << t1.getBallsPlyr(strikerId) << ")" << endl;
		cout << t1.getPlayerName(nonStrikerId) << " " << t1.getPlyrScr(nonStrikerId) << " (" << t1.getBallsPlyr(nonStrikerId) << ")" << endl;
		while ((t1.getWickets() < 10 && t.getOvers() < t.getTotalOvers()) && (t1.getScore() <= t.getScore()))
		{
			static int count = 0;
			int previous = t1.getScore();
			int pr = t.getBall();
			int p = t.getOvers();
			int pw = t1.getWickets();
			t.userBowling(t1);
			int scr = t1.getScore() - previous;
			if (pw < t1.getWickets())
			{
				t1.addBallsPlyr(strikerId);
				cout << "WICKET of " << t1.getPlayerName(strikerId) << endl;
				cout << "-----------------------" << endl;
				if (t1.getWickets()<10)
				{
					if (strikerId>nonStrikerId)
					{
						strikerId++;
					}
					else if (strikerId < nonStrikerId)
					{
						strikerId = nonStrikerId + 1;
					}
				}
				arr1 += "W ";
			}
			else if (pr == t.getBall())
			{
				if (t.getNb())
				{
					arr1 += to_string(scr) + "N ";
					t1.addPlyrScr(strikerId, scr - 1);
					t1.addExtras();
				}
				else if (t.getWd())
				{
					arr1 += "Wd ";
					t1.addExtras();
				}
			}
			else
			{
				if (scr % 2 == 0)
				{
					t1.addPlyrScr(strikerId, scr);
					t1.addBallsPlyr(strikerId);
				}
				else
				{
					t1.addPlyrScr(strikerId, scr);
					t1.addBallsPlyr(strikerId);
					strikerId += nonStrikerId;
					nonStrikerId = strikerId - nonStrikerId;
					strikerId = strikerId - nonStrikerId;
				}
				arr1 += to_string(scr) + " ";
			}
			cout << "Current Over: ";
			cout << arr1;
			cout << endl;
			cout << "---------------------------------------------" << endl;
			cout << t1.getPlayerName(strikerId) << " " << t1.getPlyrScr(strikerId) << " (" << t1.getBallsPlyr(strikerId) << ")" << endl;
			cout << t1.getPlayerName(nonStrikerId) << " " << t1.getPlyrScr(nonStrikerId) << " (" << t1.getBallsPlyr(nonStrikerId) << ")" << endl;
			count++;
			if (p != t.getOvers())
			{
				if (scr % 2 == 0)
				{
					strikerId += nonStrikerId;
					nonStrikerId = strikerId - nonStrikerId;
					strikerId = strikerId - nonStrikerId;
				}
				count = 0;
				arr1 = "";
			}
		}
		cout << "---------------------------------------------" << endl;
		cout << "Total Score: " << t1.getScore() << "/" << t1.getWickets() << " in " << t.getOvers() << "." << t.getBall() << " Overs" << endl;
		cout << "---------------------------------------------" << endl;
		t.decisionGame(t1);
		cout << "Press any key to see the Score Board . . . ";
		_getch();
		system("CLS");
		t1.displayScoreBoard();
	}
}
void showrules()
{
	string str;
	ifstream fi("rules.txt");
	if (!fi)
	{
		cout << "File not found: " << endl;
		exit(1);
	}
	else
	{
		while (!fi.eof())
		{
			getline(fi, str);
			cout << str << endl;
		}
	}
	fi.close();
}
int main()
{
	int option;
	char ply;
	do {
		cout << "					 **Welcome**					" << endl;
		cout << "Select an option (1-3):" << endl;
		cout << "1. Play" << endl;
		cout << "2. Rules" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter the option: ";
		inputValue(1, 3, option);
		system("cls");
		if (option == 1)
		{
			play();
		}
		else if (option == 2)
		{
			showrules();
			char pl;
			cout << "Do you want to play (Y/N)?:  ";
			cin.clear();
			cin.ignore(127, '\n');
			cin >> pl;
			while (!(pl == 'y' || pl == 'Y') && !(pl == 'n' || pl == 'N'))
			{
				cin.clear();
				cin.ignore(127, '\n');
				cout << "Please Choose between Y/N: ";
				cin >> pl;
			}
			if (pl == 'y' || pl == 'Y')
			{
				system("CLS");
				play();
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return 1;
		}
		cout << "Do you want to play again (Y/N)?: ";
		cin.clear();
		cin.ignore(127, '\n');
		cin >> ply;
		while (!(ply == 'y' || ply == 'Y') && !(ply == 'n' || ply == 'N'))
		{
			cin.clear();
			cin.ignore(127, '\n');
			cout << "Please Choose between Y/N: ";
			cin >> ply;
		}
		system("CLS");
		cin.clear();
		cin.ignore(127, '\n');
	} while (ply == 'y' || ply == 'Y');
	cout << endl;
	return 0;
}