#pragma once
#include <vector>
#include <memory>
#include "ship.hpp"

class Map {
 public:
  static const size_t size_ = 10;
  Map(std::vector<std::vector<std::unique_ptr<Cell>>>& map);
  Cell& getCell(int x, int y);
  const Cell& getCell(int x, int y) const;
  void markColor(int x, int y, const std::string& color);
  bool isAllCrashed();
  void whiteSurround(const Ship& ship);
  bool isCrashed(const Ship& ship);
  void ShowShips();
  bool isAvailable(int x, int y);

 private:
  std::vector<std::vector<std::unique_ptr<Cell>>> map_;
  std::vector<Ship> ships_;
};
