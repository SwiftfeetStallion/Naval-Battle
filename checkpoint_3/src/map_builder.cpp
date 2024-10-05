#include "map_builder.hpp"

MapBuilder::MapBuilder() = default;

MapBuilder* MapBuilder::generateCells() {
  cells_.resize(size_);
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      cells_[i].emplace_back(std::move(std::make_unique<Cell>()));
    }
  }
  return this;
}

MapBuilder* MapBuilder::generateShips(std::vector<Ship>& system_ship,
                                      bool isSystem) {
  std::map<int, Coord> card;
  std::map<Coord, int> index;
  int count = 0;
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = 0; j < size_; ++j) {
      index[Coord(i, j)] = count;
      card[count++] = Coord(i, j);
    }
  }
  for (int size = 4; size >= 1; --size) {
    for (int k = 1; k <= 4 - size + 1; ++k) {
      setShip(size, count, card, index, system_ship, isSystem);
      count = 0;
      std::map<Coord, int> del;
      for (auto it = index.begin(); it != index.end(); ++it) {
        if (!isAvailable(it->first.x, it->first.y)) {
          card.erase(index[it->first]);
          del[it->first] = 0;
        } else {
          Coord pair = card[index[it->first]];
          card.erase(index[it->first]);
          index[it->first] = count;
          card[count++] = pair;
        }
      }
      for (auto it = del.begin(); it != del.end(); ++it) {
        index.erase(it->first);
      }
    }
  }
  return this;
}

MapBuilder* MapBuilder::setPlayer_ships(const std::vector<Ship>& ships) {
  for (size_t i = 0; i < ships.size(); ++i) {
    const Ship& ship = ships[i];
    int x_coord = std::min(ship.begin().x, ship.end().x);
    int max_x_coord = std::max(ship.begin().x, ship.end().x);
    int y_coord = std::min(ship.begin().y, ship.end().y);
    int max_y_coord = std::max(ship.begin().y, ship.end().y);
    for (int x = x_coord; x <= max_x_coord; ++x) {
      for (int y = y_coord; y <= max_y_coord; ++y) {
        cells_[x][y]->setColor("green");
        cells_[x][y]->empty = false;
      }
    }
  }
  return this;
}

std::unique_ptr<Map> MapBuilder::build() {
  return std::move(std::make_unique<Map>(cells_));
}

bool MapBuilder::isAvailable(int x, int y) {
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (x + i < 0 || x + i >= size_ || y + j < 0 || y + j >= size_) {
        continue;
      }
      if (!(cells_[x + i][y + j]->isEmpty())) {
        return false;
      }
    }
  }
  return true;
}

bool MapBuilder::setHorizontal(std::vector<Coord>& hor, std::vector<Coord>& ver,
                               int size, int x, int y) {
  int num = 0;
  for (int i = x - size + 1; i <= x + size - 1; ++i) {
    if (isAvailable(i, y) && i >= 0 && i < size_) {
      ++num;
      hor.push_back(Coord(i, y));
    } else {
      num = 0;
      hor.clear();
    }
    if (num == size) {
      return true;
    }
  }
  return false;
}

bool MapBuilder::setVertical(std::vector<Coord>& hor, std::vector<Coord>& ver,
                             int size, int x, int y) {
  int num = 0;
  for (int i = y - size + 1; i <= y + size - 1; ++i) {
    if (isAvailable(x, i) && i >= 0 && i < size_) {
      ++num;
      ver.push_back(Coord(x, i));
    } else {
      num = 0;
      ver.clear();
    }
    if (num == size) {
      return true;
    }
  }
  return false;
}

void MapBuilder::makeHorizontal(std::vector<Coord>& hor,
                                std::map<int, Coord>& card,
                                std::map<Coord, int>& index,
                                std::vector<Ship>& system_ship, bool isSystem,
                                int size) {
  for (auto it : hor) {
    if (!isSystem) {
      cells_[it.x][it.y]->setColor("green");  // this
    }
    cells_[it.x][it.y]->empty = false;
    card.erase(index[it]);
    index.erase(it);
  }
  system_ship.push_back(Ship(hor[0], hor[hor.size() - 1], size));
}

void MapBuilder::makeVertical(std::vector<Coord>& ver,
                              std::map<int, Coord>& card,
                              std::map<Coord, int>& index,
                              std::vector<Ship>& system_ship, bool isSystem,
                              int size) {
  for (auto it : ver) {
    if (!isSystem) {
      cells_[it.x][it.y]->setColor("green");  // this
    }
    cells_[it.x][it.y]->empty = false;
    card.erase(index[it]);
    index.erase(it);
  }
  system_ship.push_back(Ship(ver[0], ver[ver.size() - 1], size));
}

void MapBuilder::setShip(int size, int count, std::map<int, Coord>& card,
                         std::map<Coord, int>& index,
                         std::vector<Ship>& system_ship, bool isSystem) {
  int ind = rand() % count;
  int pos = rand() % 2;  // 0 if horizontal
  int x = card[ind].x;
  int y = card[ind].y;
  std::vector<Coord> hor;
  std::vector<Coord> ver;
  bool horSet = setHorizontal(hor, ver, size, x, y);
  bool vertSet = setVertical(hor, ver, size, x, y);
  if (!horSet && !vertSet) {
    setShip(size, count, card, index, system_ship, isSystem);
    return;
  }
  if ((pos == 0 && horSet) || (pos == 1 && !vertSet)) {
    makeHorizontal(hor, card, index, system_ship, isSystem, size);
  } else {
    makeVertical(ver, card, index, system_ship, isSystem, size);
  }
}
