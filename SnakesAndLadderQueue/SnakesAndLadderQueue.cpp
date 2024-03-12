#include<iostream>
#include<queue>
#include<string>
using namespace std;
int main()
{
	queue<int> score;
	queue<string> Participants;
	queue<string> winners;
	int value, NoOfPlayers;
	string name;

	//-----------------------------------------------------// Declarations


	cout << "Enter the number of players: ";
	cin >> NoOfPlayers;

	for (int i = 0; i < NoOfPlayers; i++)
	{
		cout << "Enter the name of player " << i + 1 << ": ";
		cin >> name;
		Participants.push(name);
		
	}

	for (int i = 0; i < NoOfPlayers; i++)
	{
		score.push(0);
	}
	string Temp;

	int dice;

	while (!Participants.empty())     // While Loop in which the game is running.
	{
		if (NoOfPlayers == 1) 
		{
			cout << "GAME OVER !" << endl;
			cout << Participants.front() << " has lost :( " << endl;
			winners.push(Participants.front());
			break;
		}

		cout << Participants.front() << " turn:" << endl;
		Temp = Participants.front();
		dice = rand() % 6 + 1;
		cout << "The dice rolled " << dice << ".";
		value = dice + score.front();
		cout << Participants.front() << " total score " << value << "." << endl;
		score.pop();
		Participants.pop();
		
		if (value == 20) 
		{
			value = value + 20;
			cout << "Moving to 40 from Ladder " << endl;
			Participants.push(Temp);
			score.push(value);
		}

		else if (value == 60) 
		{
			value = value + 15;
			cout << "Moving to 75 from ladder " << endl;
			Participants.push(Temp);
			score.push(value);
		}

		else if (value == 50) 
		{
			value = value - 10;
			cout << "Fall down from 50 to 40, there is a snake " << endl;
			Participants.push(Temp);
			score.push(value);
		}

		else if (value == 90) 
		{
			value = value - 11;
			cout << "Fall down from 90 to 79, there is a snake " << endl;
			Participants.push(Temp);
			score.push(value);
		}

		else if (value > 100)
		{
			value = value - dice;
			cout << "Score exceeds hundred, cannot be counted " << value << "." << endl;
			Participants.push(Temp);
			score.push(value);
		}

		else if (value == 100) 
		{
			winners.push(Temp);
			NoOfPlayers--;
		}
		
		else 
		{
			Participants.push(Temp);
			score.push(value);
		}

		cout << endl;
	}

	cout << endl;
}