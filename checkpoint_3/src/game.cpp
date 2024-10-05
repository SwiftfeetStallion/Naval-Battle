#include "game.hpp"
#include "constants.hpp"

void Game::setMaps(std::map<int, Coord>& free, std::map<Coord, int>& index) {
  int count = 0;
  for (size_t i = 0; i < Map::size_; ++i) {
    for (size_t j = 0; j < Map::size_; ++j) {
      free[count] = Coord(i, j);
      index[Coord(i, j)] = count++;
    }
  }
}

void Game::updateMaps(std::map<int, Coord>& free, std::map<Coord, int>& index) {
  int count = 0;
  std::map<Coord, int> del;
  for (auto it = index.begin(); it != index.end(); ++it) {
    if (!map_2->isAvailable(it->first.x, it->first.y)) {
      free.erase(index[it->first]);
      del[it->first] = 0;
    } else {
      Coord pair = free[index[it->first]];
      free.erase(index[it->first]);
      index[it->first] = count;
      free[count++] = pair;
    }
  }
  for (auto it = del.begin(); it != del.end(); ++it) {
    index.erase(it->first);
  }
}

void Game::changeDirection() {
  if (direction == "left") {
    direction = "right";
  } else if (direction == "right") {
    direction = "left";
  } else if (direction == "up") {
    direction = "down";
  } else {
    direction = "up";
  }
}

void Game::setDirection(int& dx, int& dy) {
  if (direction == "left") {
    dx = 1;
    dy = 0;
  } else if (direction == "right") {
    dx = -1;
    dy = 0;
  } else if (direction == "up") {
    dx = 0;
    dy = 1;
  } else {
    dx = 0;
    dy = -1;
  }
}

void Game::setNewDirection(int x, int y, int new_x, int new_y) {
  if (new_x == x && new_y < y) {
    direction = "down";
  } else if (new_x == x) {
    direction = "up";
  } else if (new_y == y && new_x < x) {
    direction = "right";
  } else {
    direction = "left";
  }
}

void Game::setShot(int x, int y, int& new_x, int& new_y) {
  if (map_2->isAvailable(x + 1, y)) {
    new_x = x + 1;
    new_y = y;
  } else if (map_2->isAvailable(x, y + 1)) {
    new_x = x;
    new_y = y + 1;
  } else if (map_2->isAvailable(x - 1, y)) {
    new_x = x - 1;
    new_y = y;
  } else if (map_2->isAvailable(x, y - 1)) {
    new_x = x;
    new_y = y - 1;
  } else {
    new_x = -1;
    new_y = -1;
  }
}

void Game::white() {
  for (const auto& ship : ships_) {
    if (map_2->isCrashed(ship)) {
      map_2->whiteSurround(ship);
    }
  }
}

Game::Game(const std::vector<Ship>& ships)
    : ships_(ships) {
  map_1 =
      MapBuilder().generateCells()->generateShips(system_ships, true)->build();
  if (ships_.size() == 0) {
    map_2 = MapBuilder().generateCells()->generateShips(ships_, false)->build();
  } else {
    map_2 = MapBuilder().generateCells()->setPlayer_ships(ships_)->build();
  }
  setMaps(free, index);
  splash_buffer.loadFromFile("../splash.wav");
  crash_buffer.loadFromFile("../explosion.wav");
  splash.setBuffer(splash_buffer);
  crash.setBuffer(crash_buffer);
}

Map& Game::getMap(const int index) {
  if (index == art_system) {
    return *map_2;
  }
  return *map_1;
}

const Status& Game::getStatus() {
  return status_;
}

void Game::shoot() {
  if (map_2->isAllCrashed()) {
    status_ = LOSE;
    map_1->ShowShips();
    window->clear();
    DrawMap(*window);
    window->display();
    sleep(sleep_time);
    return;
  }
  window->clear();
  DrawMap(*window);
  window->display();
  sleep(1);
  if (state == 1) {
    if (firstState()) {
      shoot();
    }
  } else if (state == 2) {
    if (secondState()) {
      shoot();
    }
  } else if (state == 3) {
    if (thirdState()) {
      shoot();
    }
  } else {
    if (lastState()) {
      shoot();
    }
  }
}

bool Game::firstState() {
  int pos = rand() % free.size();
  prev_shoot = free[pos];
  if (map_2->getCell(free[pos].x, free[pos].y).isEmpty()) {
    splash.play();
    map_2->markColor(free[pos].x, free[pos].y, "white");
    updateMaps(free, index);
    return false;
  }
  crash.play();
  map_2->markColor(free[pos].x, free[pos].y, "red");
  state = 2;
  white();
  updateMaps(free, index);
  return true;
}

bool Game::secondState() {
  int x = prev_shoot.x, y = prev_shoot.y;
  int new_x = 0, new_y = 0;
  setShot(x, y, new_x, new_y);
  if (new_x == -1) {
    state = 1;
    return true;
  }
  if (map_2->getCell(new_x, new_y).isEmpty()) {
    splash.play();
    map_2->markColor(new_x, new_y, "white");
    updateMaps(free, index);
    return false;
  }
  prev_shoot = Coord(new_x, new_y);
  crash.play();
  map_2->markColor(new_x, new_y, "red");
  for (const auto& ship : ships_) {
    if (map_2->isCrashed(ship)) {
      map_2->whiteSurround(ship);
    }
  }
  state = 3;
  setNewDirection(x, y, new_x, new_y);
  updateMaps(free, index);
  return true;
}

bool Game::thirdState() {
  int x = prev_shoot.x, y = prev_shoot.y;
  int dx = -1, dy = -1;
  setDirection(dx, dy);
  int new_x = x + dx, new_y = y + dy;
  if (!map_2->isAvailable(new_x, new_y)) {
    if (!map_2->isAvailable(x - 2 * dx, y - 2 * dy)) {
      state = 1;
    } else {
      crash.play();
      map_2->markColor(x - 2 * dx, y - 2 * dy, "red");
      white();
      state = 4;
      prev_shoot = Coord(x - 2 * dx, y - 2 * dy);
      changeDirection();
      updateMaps(free, index);
    }
    return true;
  }
  if (!map_2->getCell(new_x, new_y).isEmpty()) {
    crash.play();
    map_2->markColor(new_x, new_y, "red");
    white();
    state = 4;
    prev_shoot = Coord(new_x, new_y);
    updateMaps(free, index);
    return true;
  }
  splash.play();
  map_2->markColor(new_x, new_y, "white");
  state = 4;
  prev_shoot = Coord(new_x, new_y);
  updateMaps(free, index);
  return false;
}

bool Game::lastState() {
  int x = prev_shoot.x, y = prev_shoot.y;
  int dx = -1, dy = -1;
  int new_x = -1, new_y = -1;
  setDirection(dx, dy);
  if (map_2->getCell(x, y).getColor() == "white") {
    new_x = x - 3 * dx;
    new_y = y - 3 * dy;
    if (!map_2->isAvailable(new_x, new_y)) {
      state = 1;
    } else {
      crash.play();
      map_2->markColor(new_x, new_y, "red");
      changeDirection();
      prev_shoot = Coord(new_x, new_y);
      white();
      updateMaps(free, index);
    }
    return true;
  }
  new_x = x + dx;
  new_y = y + dy;
  if (!map_2->isAvailable(new_x, new_y)) {
    new_x = new_x - 2 * dx;
    new_y = new_y - 2 * dy;
    if (!map_2->isAvailable(new_x, new_y)) {
      state = 1;
    } else {
      crash.play();
      map_2->markColor(new_x, new_y, "red");
      state = 1;
      white();
      updateMaps(free, index);
    }
    return true;
  }
  if (map_2->getCell(new_x, new_y).isEmpty()) {
    splash.play();
    map_2->markColor(new_x, new_y, "white");
    changeDirection();
    prev_shoot = Coord(new_x - 3 * dx, new_y - 3 * dy);
    updateMaps(free, index);
    return false;
  }
  crash.play();
  map_2->markColor(new_x, new_y, "red");
  white();
  state = 1;
  updateMaps(free, index);
  return true;
}

void Game::click(int x, int y) {
  if (x < 0 || x >= Map::size_ || y < 0 || y >= Map::size_ ||
      status_ != PROCESS) {
    return;
  }
  if (map_1->getCell(x, y).isEmpty()) {
    splash.play();
    map_1->markColor(x, y, "white");
    window->clear();
    DrawMap(*window);
    window->display();
    shoot();
  } else {
    crash.play();
    map_1->markColor(x, y, "red");
    for (auto ship : system_ships) {
      if (map_1->isCrashed(ship)) {
        map_1->whiteSurround(ship);
      }
    }
  }
  if (map_1->isAllCrashed()) {
    window->clear();
    DrawMap(*window);
    window->display();
    sleep(sleep_time);
    status_ = WIN;
    return;
  }
}

Game::~Game() = default;