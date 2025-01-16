#pragma once

#include <exception>
#include <vector>

#include "tile.hpp"

class BagEmptyException : public std::exception {};

class Bag {
private:
    std::vector<Tile> pieces;
public:
    Bag();
    bool isEmpty() const;
    Tile grab();
};
