#include<iostream>
#include<cstdlib>
using namespace std;

enum engamechoice { stone = 1, paper = 2, scissors = 3 };
enum enwinner { player1 = 1, computer = 2, draw = 3 };
struct stgameresults
{
	short gamerounds = 0;
	short player1wintimes = 0;
	short computer2wintimes = 0;
	short drawtimes = 0;
	enwinner gamerwinner;
	string winnername = "";
};
struct stroundinfo
{
	short roundnumber = 0;
	engamechoice player1choice;
	engamechoice coumputerchoice;
	enwinner winner;
	string winnername;

};
int RandomNumber(int From, int To)
{
	int randNum;
	randNum = rand() % (To - From + 1) + From;
	return randNum;
}

short readhowmanyround()
{
	short gamerounds = 1;
	do
	{
		cout << "how many rounds 1 to 10 ? \n";
		cin >> gamerounds;

	} while (gamerounds < 1 || gamerounds > 10);
	return gamerounds;
}
engamechoice readplayer1xhoise()
{
	short choice = 1;
	do
	{
		cout << " your choise:  stone:[1], paper:[2], scissors:[3] ?";
		cin >> choice;
	} while (choice < 1 || choice > 3);

	return (engamechoice)choice;
}
engamechoice getcoumputerchoice()
{
	return (engamechoice)RandomNumber(1, 3);
}
enwinner whowontheround(stroundinfo roundinfo)
{
	if (roundinfo.player1choice == roundinfo.coumputerchoice)
	{
		return enwinner::draw;
	}
	switch (roundinfo.player1choice)
	{
	case engamechoice::stone:
		if (roundinfo.coumputerchoice == engamechoice::paper)
		{
			return enwinner::computer;
		}
		break;
	case engamechoice::paper:
		if (roundinfo.coumputerchoice == engamechoice::scissors)
		{
			return enwinner::computer;
		}
		break;
	case engamechoice::scissors:
		if (roundinfo.coumputerchoice == engamechoice::stone)
		{
			return enwinner::computer;
		}
		break;
	}
	return enwinner::player1;

}
string winnername(enwinner winner)
{
	string arrwinnername[3] = { "player1", "computer", "draw" };
	return arrwinnername[winner - 1];
}


string choicename(engamechoice choice)
{
	string arrgamechoice[3] = { "stone","paper","scissors" };
	return arrgamechoice[choice - 1];
}
void printroundresult(stroundinfo roundinfo)
{
	cout << " \n____________round [" << roundinfo.roundnumber << "] ____________\n\n";
	cout << "player1 choice: " << choicename(roundinfo.player1choice) << endl;
	cout << "computer choice: " << choicename(roundinfo.coumputerchoice) << endl;
	cout << "round winner: " << roundinfo.winnername << endl;
	cout << "___________________________________________\n" << endl;
}

enwinner whowonthegame(short player1wintimes, short computerwintimes)
{
	if (player1wintimes > computerwintimes)
		return enwinner::player1;
	else if (computerwintimes > player1wintimes)
		return enwinner::computer;
	else
		return enwinner::draw;
}
stgameresults fillgameresults(int gamerounds, short player1wintimes, short computerwintimes, short drawtimes)
{
	stgameresults gameresults;
	gameresults.gamerounds = gamerounds;
	gameresults.player1wintimes = player1wintimes;
	gameresults.computer2wintimes = computerwintimes;
	gameresults.drawtimes = drawtimes;
	gameresults.gamerwinner = whowonthegame(player1wintimes, computerwintimes);
	gameresults.winnername = winnername(gameresults.gamerwinner);

	return gameresults;

}

stgameresults playgame(short howmanyrounds)
{
	stroundinfo roundinfo;
	short player1wintimes = 0, computerwintimes = 0, drawtimes = 0;
	for (short gameround = 1; gameround <= howmanyrounds; gameround++)
	{
		cout << "round [" << gameround << "] begins:\n";
		roundinfo.roundnumber = gameround;
		roundinfo.player1choice = readplayer1xhoise();
		roundinfo.coumputerchoice = getcoumputerchoice();
		roundinfo.winner = whowontheround(roundinfo);
		roundinfo.winnername = winnername(roundinfo.winner);

		if (roundinfo.winner == enwinner::player1)
			player1wintimes++;
		else if (roundinfo.winner == enwinner::computer)
			computerwintimes++;
		else
			drawtimes++;

		printroundresult(roundinfo);
	}
	return fillgameresults(howmanyrounds, player1wintimes, computerwintimes, drawtimes);
}

string tabs(short numberoftabs)
{
	string t = "";
	for (int i = 1; i < numberoftabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}
void showgameoverscreen()
{
	cout << tabs(2) << "__________________________________________________________\n\n";
	cout << tabs(2) << "                 +++ G a m e  O v e r +++\n";
	cout << tabs(2) << "__________________________________________________________\n\n";
}
void setwinnerscreencolor(enwinner winner)
{
	switch (winner)
	{
	case enwinner::player1:
		system("color 2F");
		break;

	case enwinner::computer:
		system("color 4F");
		cout << "\a";
		break;

	default:
		system("color 6F");
		break;
	}
}

void showfinalgameresults(stgameresults gameresults)
{
	cout << tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
	cout << tabs(2) << "game round         : " << gameresults.gamerounds << endl;
	cout << tabs(2) << "player1 won times  : " << gameresults.player1wintimes << endl;
	cout << tabs(2) << "computer won times : " << gameresults.computer2wintimes << endl;
	cout << tabs(2) << "draw times         : " << gameresults.drawtimes << endl;
	cout << tabs(2) << "final winner       : " << gameresults.winnername << endl;
	cout << tabs(2) << "___________________________________________________________\n";

	setwinnerscreencolor(gameresults.gamerwinner);
}
void resetscreen()
{
	system("cls");
	system("color 0F");
}

void startgame()
{
	char playagain = 'Y';
	do
	{
		resetscreen();
		stgameresults gameresult = playgame(readhowmanyround());
		showgameoverscreen();
		showfinalgameresults(gameresult);
		cout << "do you want to play again? Y/N?";
		cin >> playagain;

	} while (playagain == 'Y' || playagain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	startgame();


	return 0;
}
