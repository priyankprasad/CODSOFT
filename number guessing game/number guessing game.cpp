#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int secretNumber = std::rand() % 100 + 1;
    int guess;
    int attempts = 0;

    std::cout << "Welcome to the Number Guessing Game!\n";
    std::cout << "I've selected a random number between 1 and 100. Can you guess it?\n";

    do {
        std::cout << "Enter your guess: ";
        std::cin >> guess;
        attempts++;

        if (guess < secretNumber) {
            std::cout << "Your guess is too low. Try again.\n";
        } else if (guess > secretNumber) {
            std::cout << "Your guess is too high. Try again.\n";
        } else {
            std::cout << "Congratulations! You guessed the number " << secretNumber << " in " << attempts << " attempts!\n";
        }

    } while (guess != secretNumber);

    return 0;
}
