#include <vector>
#include <memory>
#include "map.hpp"

Map::Map(std::vector<std::vector<std::unique_ptr<Cell>>>& map)
    : map_(std::move(map)) {
}

Cell& Map::getCell(int x, int y) {
  return *map_[x][y];
}

const Cell& Map::getCell(int x, int y) const {
  return *map_[x][y];
}

void Map::markColor(int x, int y, const std::string& color) {
  map_[x][y]->setColor(color);
}

bool Map::isAllCrashed() {
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      if (!map_[i][j]->isEmpty() && map_[i][j]->getColor() != "red") {
        return false;
      }
    }
  }
  return true;
}

void Map::whiteSurround(const Ship& ship) {
  int x_st = std::min(ship.begin().x, ship.end().x);
  int y_st = std::min(ship.begin().y, ship.end().y);
  int x_end = std::max(ship.begin().x, ship.end().x);
  int y_end = std::max(ship.begin().y, ship.end().y);
  for (int x = x_st; x <= x_end; ++x) {
    for (int y = y_st; y <= y_end; ++y) {
      for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
          if (x + i < 0 || x + i >= size_ || y + j < 0 || y + j >= size_) {
            continue;
          }
          Cell& c = getCell(x + i, y + j);
          if (c.getColor() == "blue") {
            c.setColor("white");
          }
        }
      }
    }
  }
}

bool Map::isCrashed(const Ship& ship) {
  int x_st = std::min(ship.begin().x, ship.end().x);
  int y_st = std::min(ship.begin().y, ship.end().y);
  int x_end = std::max(ship.begin().x, ship.end().x);
  int y_end = std::max(ship.begin().y, ship.end().y);
  for (int i = x_st; i <= x_end; ++i) {
    for (int j = y_st; j <= y_end; ++j) {
      if (map_[i][j]->getColor() != "red") {
        return false;
      }
    }
  }
  return true;
}

void Map::ShowShips() {
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      if (!map_[i][j]->isEmpty() && map_[i][j]->getColor() != "red") {
        map_[i][j]->setColor("green");
      }
    }
  }
}

bool Map::isAvailable(int x, int y) {
  if (x < 0 || x >= size_ || y < 0 || y >= size_) {
    return false;
  }
  if (map_[x][y]->getColor() == "white" || map_[x][y]->getColor() == "red") {
    return false;
  }
  return true;
}