#pragma once
#include <SFML/Graphics.hpp>
#include "ship.hpp"

void DrawMap(sf::RenderWindow& window);

void DrawWin(sf::RenderWindow& window);

void DrawLose(sf::RenderWindow& window);

std::vector<Ship> beginGame();