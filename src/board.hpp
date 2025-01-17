#pragma once

#include <array>
#include <exception>
#include <optional>
#include <random>

#include "bag.hpp"
#include "tile.hpp"

class BoardFullException : public std::exception {};

class Board {
public:
  typedef std::optional<Tile> Item;
  typedef std::array<Item, 3> Span;
private:

  std::array<std::array<Item, 4>, 4> data;

  Span getHorizontal(int, int) const;
  Span getVertical(int, int) const;
  Span getDiagonal(int, int) const;

  bool spanIsFox(Span&&) const;
public:
  Board();
  bool hasFox() const;
  bool isFull() const;
  void placeTile(std::mt19937_64& rng, Bag& bag);
  void output() const;
};
