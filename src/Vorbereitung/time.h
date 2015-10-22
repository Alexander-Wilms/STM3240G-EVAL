// PRAKTIKUM 3

#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <iostream>
class MastermindDigits
{
public:
	// Konstruktoren
	MastermindDigits();
	MastermindDigits(int);
	MastermindDigits(const MastermindDigits&);

	// Destruktor
	~MastermindDigits();

	//Elementfunktionen
	void makeDigitsToGuess();
	void setDigits(int);
	int locationRight(const MastermindDigits&);
	int locationWrong(const MastermindDigits&);
	bool isEqual(const MastermindDigits&);
	int cheat();

private:
	int* digits;
	int* testing;
	int givenNumber;
};
#endif
