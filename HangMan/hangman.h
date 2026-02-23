#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <random>
#include <exception>
#include <fstream> 
#include <ctime>

using namespace std;
class Hangman {
private:
	int attemptsLeft;
	set<char> LettersGuessed;
	string secretword;
	string word_guessed;
	int difficulty;
public:
	Hangman(int attemptsLeft, string secretword, set<char> LettersGuessed, string word_guessed,int difficulty);
	Hangman();
	Hangman(int difficulty);

	void set_attemptsLeft(int attemptsLeft);
	int get_attemptsLeft();
	void set_difficulty(int difficulty);
	int get_difficulty();
	void set_secretword(string secretword);
	string get_secretword();
	void set_word_guessed(string word_guessed);
	string get_word_guessed();
	void Play();
	void DrawingTime();
	char Clue();
	bool Updateword(char guess);


};