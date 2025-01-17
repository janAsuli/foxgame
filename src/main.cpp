#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>

#include "board.hpp"

// Runs a game, and returns whether the player won
bool runGame(std::mt19937_64& rng) {
    Board board;
    Bag bag(rng);
    while (!bag.isEmpty()) {
        board.placeTile(rng, bag);
        if (board.hasFox()) {
            return false;
        }
    }
    return true;
}

int main() {
    auto rng = std::mt19937_64(std::time(nullptr));
    // Run x games, and see how many are wins
    int x = 1'000'000;
    int wins = 0;
    int losses = 0;
    for (int i = 0; i < x; i++) {
        if (runGame(rng)) {
            wins++;
        } else {
            losses++;
        }
    }
    std::cout << "Wins: " << wins << ", Losses: " << losses << std::endl;
}
