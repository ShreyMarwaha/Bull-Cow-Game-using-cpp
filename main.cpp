#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal Engine Friendly
using Ftext = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
Ftext GetValidGuess();
bool AskToPlayAgain();

void GameSummary();

FBullCowGame BCGame; //instantiate a new game, which we reuse across plays

int main()
{
    PrintIntro();
    do
    {
        PlayGame();
    }     while (AskToPlayAgain());

    return 0;
}

//plays a single game to completion
void PlayGame()
{
    BCGame.Reset();
    //Loop for number of turns
    while ( ! BCGame.isGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) { 
        Ftext Guess = GetValidGuess();
                
        //submit valid guess to game, and recieves counts 
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        std::cout << "Bulls: " << BullCowCount.Bulls << ", Cows: " << BullCowCount.Cows << "\nYour guess was: " << Guess <<"\n\n";
    }
    GameSummary(); 
}


void PrintIntro() {
    std::cout << "\\|/          (__)\n";
    std::cout << "    /`\\------(oo)\n";
    std::cout << "       ||    (__)\n";
    std::cout << "       ||w--||     \\|/\n";
    std::cout << "   \\|/\n";

    std::cout << "Welcome to Bulls and Cows, a fun word Puzzle Game\n";
    std::cout << "Can you guess " << BCGame.GetHiddemWordLength() << " letter isogram I'm thinking of?\n\n";
}

//loop continuously untill user enters valid guess
Ftext GetValidGuess() {
    Ftext Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do
    {
        // ask for a guess
        std::cout << "Try " << BCGame.GetCurrentTry() << " of "<< BCGame.GetMaxTries() <<". Enter your guess: ";
        std::getline(std::cin, Guess);

        Status = BCGame.CheckGuessValidity(Guess);

        switch (Status)
        {
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word without repeating letters\n"; break;

            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddemWordLength() << " Letter word.\n"; break;

            case EGuessStatus::Not_Lowercase:
                std::cout << "Please make sure all characters are lowercase/\n"; break;
            
            default: break;//assume guess is valid
     
        }
    } while (Status != EGuessStatus::OK); //keep looping untill we get valid guess
    return Guess;
}

bool AskToPlayAgain()
{   
    std::cout << "Do you want to play again with the same hidden word? (y/n)\n";
    Ftext response = "";
    std::getline(std::cin, response);
    return response[0] == 'y' || response[0] == 'Y';
}

void GameSummary()
{
    if (BCGame.isGameWon())
        std::cout << "Fantastic! You found the hidden word.\n\n";
    else
        std::cout << "Oh No! Out of lives. Better luck next time.\n\n";
}
