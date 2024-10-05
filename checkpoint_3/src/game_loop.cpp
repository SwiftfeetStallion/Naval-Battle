#include "game_loop.hpp"
#include "constants.hpp"

GameLoop::GameLoop() {
  Game::getGame();
}

bool GameLoop::start(sf::RenderWindow& window) {
  Game::getGame()->window = &window;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        return false;
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          int i = (event.mouseButton.x - system_x) / cell_size;
          int j = event.mouseButton.y / cell_size;
          Game::getGame()->click(i, j);
        }
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
      window.close();
      return true;
    }
    window.clear();
    if (Game::getGame()->getStatus() == WIN) {
      DrawWin(window);
    } else if (Game::getGame()->getStatus() == LOSE) {
      DrawLose(window);
    } else {
      DrawMap(window);
    }
    window.display();
  }
  return false;
}

GameLoop::~GameLoop() {
  if (loop_ != nullptr) {
    delete loop_;
  }
  Game::destroy();
}