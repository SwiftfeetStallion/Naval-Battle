#pragma once
#include <map>
#include "map.hpp"

class MapBuilder {
 public:
  MapBuilder();
  MapBuilder* generateCells();
  MapBuilder* generateShips(std::vector<Ship>& system_ship, bool isSystem);
  MapBuilder* setPlayer_ships(const std::vector<Ship>& ships);
  std::unique_ptr<Map> build();

 private:
  bool isAvailable(int x, int y);
  void setShip(int size, int count, std::map<int, Coord>& card,
               std::map<Coord, int>& index, std::vector<Ship>& system_ship,
               bool isSystem);
  bool setHorizontal(std::vector<Coord>& hor, std::vector<Coord>& ver, int size,
                     int x, int y);
  bool setVertical(std::vector<Coord>& hor, std::vector<Coord>& ver, int size,
                   int x, int y);
  void makeHorizontal(std::vector<Coord>& hor, std::map<int, Coord>& card,
                      std::map<Coord, int>& index,
                      std::vector<Ship>& system_ship, bool isSystem, int size);
  void makeVertical(std::vector<Coord>& ver, std::map<int, Coord>& card,
                    std::map<Coord, int>& index, std::vector<Ship>& system_ship,
                    bool isSystem, int size);

 private:
  std::vector<std::vector<std::unique_ptr<Cell>>> cells_;
  static const size_t size_ = 10;
};