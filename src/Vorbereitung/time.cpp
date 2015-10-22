// PRAKTIKUM 3

#include <iostream>
#include <stdlib.h>
#include "time.h"

MastermindDigits::MastermindDigits() // Standardkonstruktor
{
	digits = new int[4];
	srand( time(NULL) ); // Typecasting, da sich sonst der Compiler beschwert
	makeDigitsToGuess();
}

MastermindDigits::MastermindDigits(int givenNumberInt)

{
	digits = new int[4];
	setDigits(givenNumberInt);

	if(0 < digits[0] && digits[0] < 7 && 0 < digits[1] && digits[1] < 7 && 0 < digits[2] && digits[2] < 7 &&  0 < digits[3] && digits[3] < 7)
	{
		setDigits(givenNumberInt);
	} else // Zufallszahl benutzen
	{
		srand( time(NULL) ); // Typecasting, da sich sonst der Compiler beschwert
		std::cout << "Zahl nicht zulaessig. Nehme Zufallszahl ";
		for (int i = 0; i < 4; i++)
		{
			digits[i] = 1 + rand() % 6;
			std::cout << digits[i];
		}
		std::cout << std::endl;
	}
}

MastermindDigits::MastermindDigits(const MastermindDigits& copy) // Kopierkonstrukor
{
	digits = new int[4];
	for (int i = 0; i < 4; i++)
	{
		digits[i] = copy.digits[i];
	}
}

MastermindDigits::~MastermindDigits() // Destruktor
{
	delete[] digits;
	digits = nullptr; // Speicherplatz freigeben
}

void MastermindDigits::makeDigitsToGuess()
{
	for (int i = 0; i < 4; i++)
	{
		digits[i] = 1 + rand() % 6;
	}
}

void MastermindDigits::setDigits(int givenNumberInt)
{
	digits[0] = givenNumberInt / 1000;
	digits[1] = (givenNumberInt - 1000 * digits[0]) /100;
	digits[2] = (givenNumberInt - 1000 * digits[0] - 100 * digits[1]) /10;
	digits[3] = (givenNumberInt - 1000 * digits[0] - 100 * digits[1] - 10 * digits[2]);
}

int MastermindDigits::locationRight(const MastermindDigits& givenNumber)
{
	int counter = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (digits[i] == givenNumber.digits[i]) // Wenn eine Ziffer an der richtigen Stelle ist...
		{
			counter++;
		}
	}
	return counter;
}

int MastermindDigits::locationWrong(const MastermindDigits& givenNumber)
{
	int counter = 0, i;
	int actual[] = {0,0,0,0,0,0};
	int given[] = {0,0,0,0,0,0};

	for(i = 0; i < 4; i++)
	{
		actual[digits[i]-1]++; // Zählen, wie oft die Ziffern 1 bis 6 vorkommen
	}

	for(i = 0; i < 4; i++)
	{
		given[givenNumber.digits[i]-1]++; // Zählen, wie oft die Ziffern 1 bis 6 vorkommen
	}

	for(i = 0; i < 4; i++)
	{
		if (digits[i] == givenNumber.digits[i]) // Ziffern an der richtigen Stelle nicht mitzählen
		{
			actual[digits[i]-1]--;
			given[digits[i]-1]--;
		}
	}

	for(i = 0; i < 6; i++)
	{
		if(actual[i] != 0 && given[i] != 0)
		{
			counter = counter + actual[i]; // actual[i] und digits[i] sind gleich
		}
	}

	return counter;
}

bool MastermindDigits::isEqual(const MastermindDigits& givenNumber) // Checken, ob zwei Objekte gleich sind
{
	for (int i = 0; i < 4; i++)
	{
		if (givenNumber.digits[i] != digits[i])
		return false;
	}
	return true;
}

int MastermindDigits::cheat()
{
	return 1000 * digits[0] + 100 * digits[1] + 10 * digits[2] + digits[3];
}
