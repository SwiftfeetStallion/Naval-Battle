#include "game.hpp"
#include "constants.hpp"

std::vector<Ship> beginGame() {
  std::vector<Ship> ships;
  std::string ans;
  std::cout << "Do you want the random placement of your ships? If so, type "
               "YES. Else type NO\n";
  std::cin >> ans;
  if (ans == "YES") {
    return ships;
  }
  int x1, y1, x2, y2;
  std::cout << "Enter the coordinates of the four-deck ship\n";
  std::cin >> x1 >> y1 >> x2 >> y2;
  ships.push_back(Ship(Coord(x1, y1), Coord(x2, y2), 4));
  std::cout << "Enter the coordinates of the two three-deck ships\n";
  for (int i = 0; i < 2; ++i) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    ships.push_back(Ship(Coord(x1, y1), Coord(x2, y2), 3));
  }
  std::cout << "Enter the coordinates of the three two-deck ships\n";
  for (int i = 0; i < 3; ++i) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    ships.push_back(Ship(Coord(x1, y1), Coord(x2, y2), 2));
  }
  std::cout << "Enter the coordinates of the four one-deck ships\n";
  for (int i = 0; i < 4; ++i) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    ships.push_back(Ship(Coord(x1, y1), Coord(x2, y2), 1));
  }
  return ships;
}

void DrawWin(sf::RenderWindow& window) {
  sf::RectangleShape rectangle(window_size);
  rectangle.setPosition(0, 0);
  rectangle.setFillColor(dark_blue);
  window.draw(rectangle);
  sf::Text text;
  sf::Text new_text;
  text.setString("Felicitaciones!");
  new_text.setString("Has ganado la batalla!");
  text.setPosition(win_x, win_y);
  text.setFillColor(orange_text);
  text.setCharacterSize(text_size);
  new_text.setPosition(new_win_x, new_win_y);
  new_text.setFillColor(orange_text);
  new_text.setCharacterSize(text_size);
  sf::Font font;
  font.loadFromFile("../Glinster.ttf");
  text.setFont(font);
  new_text.setFont(font);
  window.draw(text);
  window.draw(new_text);
}

void DrawLose(sf::RenderWindow& window) {
  sf::RectangleShape rectangle(window_size);
  rectangle.setPosition(0, 0);
  rectangle.setFillColor(dark_blue);
  window.draw(rectangle);
  sf::Text text;
  sf::Text new_text;
  text.setString("Perdiste todos barcos...");
  new_text.setString("Has sufrido la derrota.");
  text.setPosition(lose_x, lose_y);
  text.setFillColor(orange_text);
  text.setCharacterSize(text_size);
  new_text.setPosition(new_lose_x, new_lose_y);
  new_text.setFillColor(orange_text);
  new_text.setCharacterSize(text_size);
  sf::Font font;
  font.loadFromFile("../Glinster.ttf");
  text.setFont(font);
  new_text.setFont(font);
  window.draw(text);
  window.draw(new_text);
}

void DrawMap(sf::RenderWindow& window) {
  const Map& map_1 = Game::getGame()->getMap(player);
  const Map& map_2 = Game::getGame()->getMap(art_system);
  sf::RectangleShape rectangle_1(sf::Vector2f(field_size, field_size));
  rectangle_1.setPosition(system_x, 0);
  window.draw(rectangle_1);
  sf::RectangleShape rectangle_2(sf::Vector2f(field_size, field_size));
  rectangle_2.setPosition(player_x, 0);
  window.draw(rectangle_2);
  for (size_t i = 0; i < Map::size_; ++i) {
    for (size_t j = 0; j < Map::size_; ++j) {
      sf::RectangleShape cell_1(sf::Vector2f(cell_size, cell_size));
      sf::RectangleShape cell_2(sf::Vector2f(cell_size, cell_size));
      cell_1.setPosition(i * cell_size + i + system_x, j * cell_size + j);
      cell_2.setPosition(i * cell_size + i + player_x, j * cell_size + j);
      if (map_1.getCell(i, j).getColor() == "white") {
        cell_1.setFillColor(white_cell);
      } else if (map_1.getCell(i, j).getColor() == "red") {
        cell_1.setFillColor(red_cell);
      } else if (map_1.getCell(i, j).getColor() == "green") {
        cell_1.setFillColor(green_cell);
      } else {
        cell_1.setFillColor(blue_cell);
      }
      if (map_2.getCell(i, j).getColor() == "white") {
        cell_2.setFillColor(white_cell);
      } else if (map_2.getCell(i, j).getColor() == "red") {
        cell_2.setFillColor(red_cell);
      } else if (map_2.getCell(i, j).getColor() == "green") {
        cell_2.setFillColor(green_cell);
      } else {
        cell_2.setFillColor(blue_cell);
      }
      window.draw(cell_1);
      window.draw(cell_2);
    }
  }
}