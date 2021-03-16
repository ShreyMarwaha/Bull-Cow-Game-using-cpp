#include "FBullCowGame.h"
#include <map>
#define TMap std::map //to make syntax Unreal Engine Friendly

FBullCowGame::FBullCowGame()	{Reset();} //constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddemWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::isGameWon() const { return bIsGameWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLenghtToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,21} };
	return WordLenghtToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "money"; //This must be an ISOGRAM
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bIsGameWon = false;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if ( ! IsIsogram(Guess)) //if guess not isogram 
		return EGuessStatus::Not_Isogram;

	else if (Guess.length()!=GetHiddemWordLength()) //wrong guess length
		return EGuessStatus::Wrong_Length;

	else if (!IsLowercase(Guess))// all guess char not lowercase    
		return EGuessStatus::Not_Lowercase;

	else
		return EGuessStatus::OK;
}


// recieves a valid guess, increments turns, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//increment the turn num
	MyCurrentTry++;

	//setup a return variable
	FBullCowCount BullCowCount;

	//loop through all leters in the guess
		// compare leters against the hidden word

	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++){
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if (Guess[j] == MyHiddenWord[i])
			{
				if (i == j)
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength)	
		bIsGameWon =true;
	
	return BullCowCount;
}


bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) return true;

	TMap<char, bool> LetterSeen;

	for (auto Letter : Word)
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) //if letter is in the map
			return false;	//Word is not an ISOGRAM
		else
			LetterSeen[Letter] = true; //add letter to the map and continue iterating
	}
	return true;
}


bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
			return false;
	}
	return true;
}
