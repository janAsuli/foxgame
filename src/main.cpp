#include <ctime>
#include <cstdlib>
#include <iostream>

#include "board.hpp"

int main() {
    std::srand(std::time(nullptr));
    Board board;
    Bag bag;
    board.output();
    while (!bag.isEmpty()) {
        board.placeTile(bag);
        board.output();
        if (board.hasFox()) {
            std::cout << "You Lose!\n";
            return 0;
        }
        std::cout << '\n';
    }
    std::cout << "You win!\n";
}
