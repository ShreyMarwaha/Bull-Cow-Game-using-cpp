/* The game logic (no view code or direct user iinteracinon)
The game is siimple guess the word game based on Mastermind
*/

#pragma once
#include <string>

//to make syntax Unreal Engine Friendly
using FString = std::string;
using int32 = int;


struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame
{
public:
	FBullCowGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddemWordLength() const;
	bool isGameWon() const;

	void Reset(); 
	EGuessStatus CheckGuessValidity(FString) const; 											
	FBullCowCount SubmitValidGuess(FString); // counts bulls & cows, and inc turn # , assuming valid guess

private:
	//for Initialisation, see costructor
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};