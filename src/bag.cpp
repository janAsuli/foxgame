#include <cstdlib>
#include <utility>

#include "bag.hpp"

Bag::Bag(std::mt19937_64& rng) {
    this->pieces.reserve(12);
    for (int i = 0; i < 6; i++) {
        this->pieces.push_back(Tile::F);
        this->pieces.push_back(Tile::X);
    }
    // Shuffle the pieces
    for (int i = 0; i < this->pieces.size() - 1; i++) {
        auto sz = this->pieces.size() - i + 1;
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
