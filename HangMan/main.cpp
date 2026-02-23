/*
#include "hangman.h"
#include <ctime>

int main()
{
	srand(static_cast<unsigned int>(time(0)));
    int difficulty;
	cout << "Welcome to Hangman!" << endl;
	cout << "Select difficulty level: " << endl;
	cout << "1. Easy" << endl;
	cout << "2. Medium" << endl;
	cout << "3. Hard" << endl;
	cin >> difficulty;

	Hangman game(difficulty);
	game.Play();

    return 0;
}
*/
#include "raylib.h"
#include "hangman.h"
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
	srand(static_cast<unsigned int>(time(0)));// Seed the random number generator
    int difficulty;
    cout << "Welcome to Hangman!" << endl;
    cout << "Select difficulty level: " << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    cin >> difficulty;

    // Create the game object
    Hangman game(difficulty);
	game.Play();
    return 0;
}