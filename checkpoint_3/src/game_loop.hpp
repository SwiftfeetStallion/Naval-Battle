#pragma once
#include "game.hpp"

class GameLoop {
 public:
  GameLoop();
  bool start(sf::RenderWindow& window);
  static GameLoop* getLoop() {
    if (loop_ == nullptr) {
      loop_ = new GameLoop();
    }
    return loop_;
  }
  static void destroy() {
    Game::destroy();
    if (loop_ != nullptr) { loop_ = nullptr; }
  }
  ~GameLoop();

 private:
  static GameLoop* loop_;
};