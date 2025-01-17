#pragma once

#include <exception>
#include <random>
#include <vector>

#include "tile.hpp"

class BagEmptyException : public std::exception {};

class Bag {
private:
    std::vector<Tile> pieces;
public:
    Bag(std::mt19937_64&);
    bool isEmpty() const;
    Tile grab();
};
