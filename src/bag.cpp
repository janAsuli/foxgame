module;

#include <cstdlib>
#include <exception>
#include <random>
#include <utility>
#include <vector>

export module Bag;

import Tile;

class BagEmptyException : public std::exception {};

// A bag that contains tiles
export class Bag {
private:
    // The tiles in the bag
    std::vector<Tile> pieces;
public:
    // Creates a new bag and shuffles it with a seed
    Bag(std::mt19937_64&);
    // Returns whether the bag has no more elements
    bool isEmpty() const;
    // Gets the next tile from the bag
    Tile grab();
};


Bag::Bag(std::mt19937_64& rng) {
    this->pieces.reserve(12);
    for (int i = 0; i < 5; i++) {
        this->pieces.push_back(Tile::F);
        this->pieces.push_back(Tile::X);
    }
    this->pieces.push_back(Tile::O);
    this->pieces.push_back(Tile::O);
    // Shuffle the pieces
    for (unsigned long i = 0; i < this->pieces.size() - 1; i++) {
        auto sz = this->pieces.size() - i;
        int j = rng() % sz + i;
        std::swap(this->pieces[i], this->pieces[j]);
    }
}

bool Bag::isEmpty() const {
    return this->pieces.empty();
}

Tile Bag::grab() {
    if (this->isEmpty()) {
        throw BagEmptyException();
    }
    Tile ret = this->pieces.back();
    this->pieces.pop_back();
    return ret;
}
