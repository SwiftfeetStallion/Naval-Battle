#pragma once
#include <iostream>

struct Coord {
  int x;
  int y;
  Coord();
  Coord(int x, int y);
};

bool operator<(const Coord& first, const Coord& second);

class Cell {
 public:
  bool empty = true;
  Cell();
  bool isEmpty() const;
  std::string getColor() const;
  void setColor(const std::string& color);

 private:
  std::string color_ = "blue";
};

class Ship {
 public:
  Ship(const Coord& b, const Coord& e, size_t sz);
  Coord begin() const;
  Coord end() const;
  size_t size() const;

 private:
  Coord begin_;
  Coord end_;
  size_t size_;
};