#include <iostream>
#include <random>
#include <chrono>
#include <limits>
#include <cctype>

using namespace std;

int getIntInput(const string &prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            return x;
        }
        // invalid input
        cout << "Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

char getCharYesNo(const string &prompt) {
    char c;
    while (true) {
        cout << prompt;
        if (cin >> c) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            if (c == 'y' || c == 'n') return c;
        }
        cout << "Please enter y or n.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    // random number generator
    mt19937 rng(static_cast<unsigned>(chrono::steady_clock::now().time_since_epoch().count()));

    cout << "=== Number Guessing Game ===\n";
    cout << "Rules: Choose a difficulty, the system will generate a random number. Use hints (higher/lower) to guess within limited attempts.\n\n";

    int bestAttempts = numeric_limits<int>::max();

    while (true) {
        cout << "Choose difficulty:\n";
        cout << "1. Easy (1-50, 10 tries)\n";
        cout << "2. Normal (1-100, 7 tries)\n";
        cout << "3. Hard (1-200, 5 tries)\n";
        int diff = getIntInput("Enter 1/2/3 to choose difficulty: ");

        int maxN = 100;
        int maxTries = 7;
        if (diff == 1) { maxN = 50; maxTries = 10; }
        else if (diff == 2) { maxN = 100; maxTries = 7; }
        else if (diff == 3) { maxN = 200; maxTries = 5; }
        else {
            cout << "Invalid choice, defaulting to Normal.\n";
            maxN = 100; maxTries = 7;
        }

        uniform_int_distribution<int> dist(1, maxN);
        int secret = dist(rng);

        cout << "A number between 1 and " << maxN << " has been generated. You have " << maxTries << " attempts.\n";

        bool won = false;
        for (int attempt = 1; attempt <= maxTries; ++attempt) {
            int guess = getIntInput("Attempt " + to_string(attempt) + ": Enter your guess: ");
            if (guess == secret) {
                cout << "Congratulations, you guessed it! Attempts used: " << attempt << ".\n";
                won = true;
                if (attempt < bestAttempts) {
                    bestAttempts = attempt;
                    cout << "This is your new record!\n";
                }
                break;
            } else if (guess < secret) {
                cout << "The number is higher.\n";
            } else {
                cout << "The number is lower.\n";
            }
            if (attempt == maxTries) {
                cout << "Out of attempts. The correct number was " << secret << ".\n";
            }
        }

        if (bestAttempts != numeric_limits<int>::max()) {
            cout << "Current best record (fewest attempts): " << bestAttempts << "\n";
        }

        char again = getCharYesNo("Play again? (y/n): ");
        if (again == 'n') break;
        cout << "\n";
    }

    cout << "Thanks for playing! Goodbye.\n";
    return 0;
}