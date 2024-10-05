#pragma once
#include <unistd.h>
#include <SFML/Audio.hpp>
#include "map_builder.hpp"
#include "interface.hpp"

enum Status { LOSE, WIN, PROCESS };

class Game {
 public:
  sf::RenderWindow* window;
  Game(const std::vector<Ship>& ships);
  Map& getMap(const int index);
  const Status& getStatus();
  void shoot();
  void click(int x, int y);
  static Game* getGame() {
    if (game_ == nullptr) {
      std::vector<Ship> ships = beginGame();
      game_ = new Game(ships);
    }
    return game_;
  }
  static void destroy() {
    if (game_ != nullptr) { game_ = nullptr; }
  }
  ~Game();

 private:
  std::unique_ptr<Map> map_1;
  std::unique_ptr<Map> map_2;
  Status status_ = PROCESS;
  static Game* game_;
  std::vector<Ship> ships_;
  std::vector<Ship> system_ships;
  Coord prev_shoot = Coord(-1, -1);
  int state = 1;
  std::string direction;
  std::map<int, Coord> free;
  std::map<Coord, int> index;
  sf::SoundBuffer splash_buffer;
  sf::SoundBuffer crash_buffer;
  sf::Sound splash;
  sf::Sound crash;
  void setMaps(std::map<int, Coord>& free, std::map<Coord, int>& index);
  void updateMaps(std::map<int, Coord>& free, std::map<Coord, int>& index);
  void changeDirection();
  void setDirection(int& dx, int& dy);
  void setNewDirection(int x, int y, int new_x, int new_y);
  void setShot(int x, int y, int& new_x, int& new_y);
  void white();
  bool firstState();
  bool secondState();
  bool thirdState();
  bool lastState();
};