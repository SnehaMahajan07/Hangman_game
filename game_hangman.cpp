#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <map>

using namespace std;

// Function to display the current state of the word
void displayWord(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.size(); ++i) {
        if (guessed[i]) {
            cout << word[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

// Function to check if the player has won
bool hasWon(const vector<bool>& guessed) {
    for (bool b : guessed) {
        if (!b) return false;
    }
    return true;
}

// Function to display the hangman diagram
void displayHangman(int tries) {
    string hangman[] = {
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n"
    };
    cout << hangman[tries] << endl;
}

void playGame() {
    // List of words and hints
    map<string, string> words = {
        {"hangman", "A game of guessing letters"},
        {"computer", "An electronic device for processing data"},
        {"programming", "The process of writing computer programs"},
        {"development", "The process of creating software"},
        {"cplusplus", "A powerful general-purpose programming language"},
        {"algorithm", "A step-by-step procedure for solving a problem"},
        {"datastructure", "A way to organize and store data"},
        {"apple", "A fruit that is red or green"},
        {"banana", "A long, curved fruit that is yellow when ripe"},
        {"cat", "A small, furry animal that is often kept as a pet"}
    };

    // Seed for random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Choose a random word from the list
    auto it = words.begin();
    advance(it, rand() % words.size());
    string word = it->first;
    string hint = it->second;

    vector<bool> guessed(word.size(), false);
    vector<char> incorrectGuesses;
    int maxTries = 6;
    int tries = 0;

    cout <<"*****************************************"<<endl;
    cout << "Welcome to Hangman Game!" << endl;
    cout <<"*****************************************"<<endl;
    cout<<endl;
    cout << "Hint: " << hint << endl;

    while (tries < maxTries) {
        displayHangman(tries);

        cout << "Incorrect guesses: ";
        for (char c : incorrectGuesses) {
            cout << c << " ";
        }
        cout << endl;

        displayWord(word, guessed);

        cout << "Enter your guess: ";
        char guess;
        cin >> guess;

        bool correctGuess = false;
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == guess) {
                guessed[i] = true;
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            incorrectGuesses.push_back(guess);
            ++tries;
        }

        if (hasWon(guessed)) {
            displayHangman(tries);
            cout << "Congratulations! You've won!" << endl;
            cout << "You saved the man from being hanged!!!" << endl;
            displayWord(word, guessed);
            break;
        }
    }

    if (tries == maxTries) {
        displayHangman(tries);
        cout << "Sorry, you've lost!!!" << endl;
        cout << "The word was: " << word << endl;
        cout << "You couldn't save the man from being hanged!!!" << endl;
    }
}

int main() {
    char playAgain;
    do {
        playGame();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thank you for playing Hangman!" << endl;
    return 0;
}
