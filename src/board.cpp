#include <cstdlib>
#include <iostream>
#include <utility>

#include "board.hpp"

Board::Board() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                this->data[i][j] = Tile::O;
            } else {
                this->data[i][j] = std::nullopt;
            }
        }
    }
}

bool Board::isFull() const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!this->data[i][j].has_value()) {
                return false;
            }
        }
    }
    return true;
}

Board::Span Board::getHorizontal(int x, int y) const {
    auto left = this->data.at(y).at(x);
    auto center = this->data.at(y).at(x + 1);
    auto right = this->data.at(y).at(x + 2);
    return {left, center, right};
}

Board::Span Board::getVertical(int x, int y) const {
    auto top = this->data.at(y).at(x);
    auto center = this->data.at(y + 1).at(x);
    auto bottom = this->data.at(y + 2).at(x);
    return {top, center, bottom};
}

Board::Span Board::getDiagonal(int x, int y) const {
    auto first = this->data.at(y).at(x);
    auto second = this->data.at(y - 1).at(x + 1);
    auto third = this->data.at(y - 2).at(x + 2);
    return {first, second, third};
}

bool Board::spanIsFox(Board::Span&& span) const {
    for (auto spot: span) {
        if (!spot.has_value()) {
            return false;
        }
    }
    if (span[1].value() != Tile::O) {
        return false;
    }
    if (span[0].value() == Tile::F and span[2].value() == Tile::X) {
        return true;
    }
    if (span[2].value() == Tile::F and span[0].value() == Tile::X) {
        return true;
    }
    return false;
}

bool Board::hasFox() const {
    for (int i = 0; i < 2; i++) {
        Span span = this->getHorizontal(i, i + 1);
        if (this->spanIsFox(std::move(span))) {
            return true;
        }
    }
    for (int i = 0; i < 2; i++) {
        Span span = this->getVertical(i + 1, i);
        if (this->spanIsFox(std::move(span))) {
            return true;
        }
    }
    for (int i = 0; i < 2; i++) {
        Span span = this->getDiagonal(i, i + 2);
        if (this->spanIsFox(std::move(span))) {
            return true;
        }
    }
    return false;
}

void Board::placeTile(Bag& bag) {
    int emptySpaces = 0;
    for (auto row: this->data) {
        for (auto space: row) {
            if (!space.has_value()) {
                emptySpaces += 1;
            }
        }
    }

    if (emptySpaces == 0) {
        throw BoardFullException();
    }

    int i = std::rand() % emptySpaces;
    int targetI = 0;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (!this->data[y][x].has_value()) {
                if (targetI == i) {
                    this->data[y][x] = bag.grab();
                }
                targetI++;
            }
        }
    }
}

char tileToChar(Board::Item item) {
    if (item.has_value()) {
        switch (item.value()) {
            case Tile::F:
                return 'F';
            case Tile::O:
                return 'O';
            case Tile::X:
                return 'X';
        }
    }
    return '_';
}

void Board::output() const {
    for (auto row: this->data) {
        std::cout << '[';
        for (int i = 0; i < 4; i++) {
            std::cout << tileToChar(row[i]);
            if (i != 3) {
                std::cout << ',';
            } else {
                std::cout << ']';
            }
        }
        std::cout << '\n';
    }
}
