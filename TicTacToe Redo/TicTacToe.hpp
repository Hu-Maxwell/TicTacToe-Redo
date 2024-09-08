#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <SFML/Graphics.hpp>

void drawGrid(sf::RenderWindow& window, int sideLen);
float countUnits(int clickXY, int sideLen);
bool validClick(sf::Vector2i clickPos, int sideLen);
void analyzeClick(sf::Vector2i clickPos, int sideLen, std::string(&arr)[3][3], std::string letter);
bool checkLine(std::string a, std::string b, std::string c, std::string player);
void checkWinner(std::string(&arr)[3][3], bool& gameScreen, bool& winScreen, sf::Text& text);
void drawX(sf::RenderWindow& window, int sideLen, int x, int y);
void drawO(sf::RenderWindow& window, int sideLen, int x, int y);
void drawLetter(sf::RenderWindow& window, std::string(&arr)[3][3], int sideLen);

#endif