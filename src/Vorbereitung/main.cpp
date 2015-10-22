// PRAKTIKUM 3
// g++ -std=c++0x main.cpp Mastermind.cpp Mastermind.h

#include <iostream>
#include <stdio.h>
#include "time.h"
using namespace std;

void Play();
void Test();

int main()
{
	char validtest;
	int choice;
	bool done = false;
	while(!done)
	{
		cout << "Testen(1) oder Spielen(2): ";
		cin >> validtest;
		if(validtest - '0' == 1 || validtest - '0' == 2)
		{
			choice = validtest - '0';
			if(choice == 1) { Test(); done = true;}
			else if(choice == 2) { Play(); done = true;}
		} else cout << "Invalid" << endl;
		rewind (stdin);
	}
}

void Play()
{
	MastermindDigits NumberToGuess;

	int givenNumberInt;
	int counter = 0, i = 1;

	while (true)
	{
		cout << i << ". Versuch; Gib Zahl: ";
		cin >> givenNumberInt;

		if(givenNumberInt == -1)
		{
			cout << "Zahl: " << NumberToGuess.cheat() << std::endl;
		} else
		{
			MastermindDigits givenNumber(givenNumberInt);
			if (NumberToGuess.isEqual(givenNumber) == true)
			{
				cout << "Zahl erraten" << std::endl;
				rewind(stdin);
				getchar();
				counter++;
				break;
			}
			else
			{
				cout << NumberToGuess.locationRight(givenNumber) << " an der richtigen Stelle;";
				cout << " sonst " << NumberToGuess.locationWrong(givenNumber) << " richtig" << std::endl << std::endl;
			}
			i++;
		}
	}
}

void Test()
{
	int givenNumberInt, testNumber, counter = 0, i = 1;
	cout << "Testzahl eingeben: " << std::endl;
	cin >> testNumber;
	MastermindDigits NumberToGuess(testNumber);

	while (true)
	{
		cout << i << ". Versuch; Gib Zahl: ";
		cin >> givenNumberInt;
		if(givenNumberInt == -1)
		{
			cout << "Zahl: " << NumberToGuess.cheat() << std::endl << std::endl;
		} else
		{
			MastermindDigits Guess(givenNumberInt);
			if (NumberToGuess.isEqual(Guess) == true)
			{
				cout << "Zahl erraten" << std::endl;
				rewind(stdin);
				getchar();
				counter++;
				break;
			}
			else
			{
				cout << NumberToGuess.locationRight(Guess) << " an der richtigen Stelle;";
				cout << " sonst " << NumberToGuess.locationWrong(Guess) << " richtig" << std::endl << std::endl;
			}
			i++;
		}
	}
}
