#include "hangman.h"
#include "raylib.h" 

Hangman::Hangman() 
	: attemptsLeft(6), LettersGuessed(LettersGuessed) {
		set_secretword(secretword);
		set_word_guessed(word_guessed),set_difficulty(difficulty);
}

Hangman::Hangman(int attemptsLeft,string secretword, set<char> LettersGuessed, string word_guessed,int difficulty) {
	this->set_difficulty(difficulty);
	this->attemptsLeft = 6;
	this->set_secretword(secretword);
	this->LettersGuessed = LettersGuessed;
	this->set_word_guessed(word_guessed);
}
Hangman::Hangman(int difficulty) {
	this->set_difficulty(difficulty);
	this->attemptsLeft = 6;
	this->set_secretword(secretword);
	this->LettersGuessed.clear();
	this->set_word_guessed(word_guessed);
}
void Hangman::set_attemptsLeft(int attemptsLeft) {
	this -> attemptsLeft = 6;
}
int Hangman::get_attemptsLeft() {
	return attemptsLeft;
}
void Hangman::set_difficulty(int difficulty) {
	if(difficulty == 1 || difficulty == 2 || difficulty == 3)
		this->difficulty = difficulty;
	else
		throw invalid_argument("Difficulty must be 1, 2, or 3!");
}
int Hangman::get_difficulty() {
	return difficulty;
}
void Hangman::set_secretword(string secretword) {
	//vector<string> word = { "apple","banana","strawberry","peach","pear"};
	//int index = rand() % word.size();
	//this-> secretword = word[index];

	vector<string> word;
	string line;
	string filename;

	if (difficulty == 1) {
		filename = "words.txt";
	}
	else if (difficulty == 2) {
		filename = "wordsmedium.txt";
	}
	else {
		filename = "wordshard.txt";
	}

	ifstream file(filename);
	if (file.is_open()) {
		while (getline(file, line)) {
			if (!line.empty()) {
				for (char& c : line) {
					c = tolower(c);
				}
				word.push_back(line);
			}
		}
		file.close();
	}
	if (word.empty()) {
		word = { "apple", "banana", "strawberry", "peach", "pear" };
	}

	if (!word.empty()) {
		int index = rand() % word.size();
		this->secretword = word[index];
	}

}

string Hangman::get_secretword() {
	return secretword;
}

void Hangman::set_word_guessed(string word_guessed) {
	this-> word_guessed = string(get_secretword().length(), '_');
	Updateword(get_secretword()[0]);
}
string Hangman::get_word_guessed() {
	return word_guessed;
}


bool Hangman::Updateword(char guess)
{
	bool correctGuess = false;
	for (int i = 0; i < secretword.length(); i++) {
		if (secretword[i] == guess) {
			word_guessed[i] = guess;
			correctGuess = true;
		}
	}
	LettersGuessed.insert(guess);
	return correctGuess;
}


/*
* void Hangman::DrawingTime()
* int a = attemptsLeft;
	switch(a) {
        case 5:
			cout << "O" << endl;
			break;
		case 4:
			cout << "O" << endl;
			cout << "|" << endl;
			break;
		case 3:   
			cout <<" "<<"O" << endl;
			cout << ">" <<  "|"<<endl;
			break;
		case 2:
			cout << " " << "O" << endl;
			cout << ">" << "|" << "<" <<endl;
			break;
		case 1:
			cout << " " << "O" << endl;
			cout << ">" << "|" << "<" << endl;
			cout << "]" << endl;
			break;
		case 0:
			cout << " " << "O" << endl;
			cout << ">" << "|" << "<" << endl;
			cout << "]" <<" " <<"[" << endl;
			break;
*/
void Hangman::DrawingTime()
{
	int a = attemptsLeft;

	// Adăugăm desenul Raylib (acesta va fi apelat în bucla din Play)
	// Desenăm stâlpul fix (mereu prezent)
	DrawLine(100, 450, 300, 450, BLACK); // Base
	DrawLine(150, 450, 150, 100, BLACK); // Post
	DrawLine(150, 100, 350, 100, BLACK); // Beam
	DrawLine(350, 100, 350, 150, BLACK); // Rope

	// Drawing the man based on attemptsLeft
	if (a <= 5) DrawCircle(350, 180, 30, BLACK);      // Head
	if (a <= 4) DrawLine(350, 210, 350, 330, BLACK); // Body
	if (a <= 3) DrawLine(350, 240, 310, 200, BLACK); // Left Arm
	if (a <= 2) DrawLine(350, 240, 390, 200, BLACK); // Right Arm
	if (a <= 1) DrawLine(350, 330, 310, 400, BLACK); // Left Leg
	if (a <= 0) DrawLine(350, 330, 390, 400, BLACK); // Right Leg
	
}

char Hangman::Clue() {
	int a = 0;
	char clue;
	for (int i = 0; i < secretword.length(); i++) {
		string temp = word_guessed;
		if (secretword[i] != temp[i]) {
			clue = secretword[i];
			a++;
			for (int i = 0; i < secretword.length(); i++) {
					if (secretword[i] == clue) {
						temp[i] = clue;
					}
				}
		}
	}
	if (a > 2) {
		DrawText(TextFormat("HINT: Try '%c'", clue), 650, 650, 30, GOLD);
		return clue;
	}
	else {
		DrawText("No clue available", 650, 650, 20, LIGHTGRAY);
		return '\0';
	}


}

/*
* void Hangman::Play() {
	int ok = 1;
	cout << "Guess the word: "  <<endl;
	for (char c : word_guessed) {
		cout << c << " ";
	}
	cout << endl;
	while (attemptsLeft > 0 && ok != 0) {

		if(attemptsLeft == 1) {
			Clue();
		}
		ok = 0;
		cout << "Guess a letter: ";
		char guess;
		cin >> guess;
		if(isalpha(guess)) {
			guess = tolower(guess);
		}
		 else {
			throw invalid_argument("The guess must be a letter!");
		}
		
		if (LettersGuessed.count(guess)) {
			cout << "Letter already guessed: ";
		}
		else if (Updateword(guess)) {
			cout << "Good job! Letter in the word.";

		}
		else {
			cout << "Wrong guess!"<<endl;
			attemptsLeft--;
			DrawingTime();
		}
		for (int i = 0; i < secretword.length(); i++) {
			if (secretword[i] != word_guessed[i]) {
				ok++;
			}
		}
		for (char c : word_guessed) {
			cout << c << " ";
		}
		cout << endl << "Attempts left: " << attemptsLeft<<endl;
	}
	if (ok == 0) {
		cout << "CONGRATIULATION YOU WON THE GAME!";


	}
	else {
		cout << "YOU FAILED!"<<endl;
		cout<<"The word was: " << secretword << endl;
	}
	
}

*/
void Hangman::Play() {
	InitWindow(1000, 800, "Hangman Game - Full Graphics");
	SetTargetFPS(60);

	string statusMsg = "Press a key to guess!";
	Color statusColor = DARKGRAY;
	int ok = 1;

	while (!WindowShouldClose()) {

		int key = GetCharPressed();

		if (key > 0 && attemptsLeft > 0 && ok > 0) {
			char guess = (char)tolower(key);
			if (guess >= 'a' && guess <= 'z') {

				if (LettersGuessed.count(guess)) {
					statusMsg = TextFormat("Letter '%c' already guessed!", guess);
					statusColor = ORANGE;
				}
				else if (Updateword(guess)) {
					statusMsg = "Good job! Letter in the word.";
					statusColor = GREEN;
				}
				else {
					statusMsg = "Wrong guess!";
					statusColor = RED;
					attemptsLeft--;
				}
			}
			else {
				statusMsg = "Invalid input! Use letters only.";
				statusColor = MAROON;
			}

			ok = 0;
			for (int i = 0; i < secretword.length(); i++) {
				if (secretword[i] != word_guessed[i]) {
					ok++;
				}
			}//compute how many letters we have left to guess (if ok == 0 we win the game)
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("HANGMAN", 420, 20, 40, DARKGRAY);

		DrawText(statusMsg.c_str(), 350, 80, 25, statusColor);

		DrawingTime();

		DrawText(word_guessed.c_str(), 200, 550, 60, DARKBLUE);

		if (attemptsLeft <= 2 && ok > 0) {
			Clue();
		}

		DrawText(TextFormat("Attempts left: %d", attemptsLeft), 700, 150, 25, DARKGRAY);
		if (ok == 0) {
			DrawText("CONGRATULATIONS YOU WON THE GAME!", 150, 300, 40, GREEN);
		}
		else if (attemptsLeft <= 0) {
			DrawText("YOU FAILED!", 400, 250, 50, RED);
			DrawText(TextFormat("The word was: %s", secretword.c_str()), 350, 320, 25, DARKGRAY);
		}

		DrawText("Press ESC to exit", 10, 770, 20, LIGHTGRAY);
		EndDrawing();
	}

	CloseWindow();
}


	