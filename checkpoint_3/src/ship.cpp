#include <iostream>
#include "ship.hpp"

Coord::Coord() = default;

Coord::Coord(int x, int y)
    : x(x),
      y(y) {
}

bool operator<(const Coord& first, const Coord& second) {
  return std::make_pair(first.x, first.y) < std::make_pair(second.x, second.y);
}

Cell::Cell() = default;

bool Cell::isEmpty() const {
  return empty;
}

std::string Cell::getColor() const {
  return color_;
}

void Cell::setColor(const std::string& color) {
  color_ = color;
}

Ship::Ship(const Coord& b, const Coord& e, size_t sz)
    : begin_(b),
      end_(e),
      size_(sz) {
}

Coord Ship::begin() const {
  return begin_;
}

Coord Ship::end() const {
  return end_;
}

size_t Ship::size() const {
  return size_;
}