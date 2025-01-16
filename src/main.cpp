#include <ctime>
#include <cstdlib>
#include <iostream>

#include "board.hpp"

// Runs a game, and returns whether the player won
bool runGame() {
    Board board;
    Bag bag;
    while (!bag.isEmpty()) {
        board.placeTile(bag);
        if (board.hasFox()) {
            return false;
        }
    }
    return true;
}

int main() {
    std::srand(std::time(nullptr));
    // Run x games, and see how many are wins
    int x = 1'000'000;
    int wins = 0;
    int losses = 0;
    for (int i = 0; i < x; i++) {
        if (runGame()) {
            wins++;
        } else {
            losses++;
        }
    }
    std::cout << "Wins: " << wins << ", Losses: " << losses << std::endl;
}
