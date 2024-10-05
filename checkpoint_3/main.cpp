#include "src/game.hpp"
#include "src/game_loop.hpp"

Game* Game::game_ = nullptr;
GameLoop* 
GameLoop::loop_ = nullptr;

int main() {
  while (true) {
    srand(time(0));
    GameLoop::getLoop();
    sf::RenderWindow window(sf::VideoMode({1050, 530}), "Battle!");
    bool restart = GameLoop::getLoop()->start(window);
    if (!restart) { break; }
    GameLoop::destroy();
  };

}
 