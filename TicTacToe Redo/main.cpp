#include <SFML/Graphics.hpp>
#include <utility>
#include <cmath>
#include <iostream>

#include "TicTacToe.hpp"

int main() {
	int sideLen = 700; 
	std::string arr[3][3]; 

	sf::Font font;
	if (!font.loadFromFile("C:/Users/maxwe/source/repos/TicTacToe Redo/TicTacToe Redo/fonts/semibold.ttf")) {
		std::cerr << "Failed to load font" << std::endl;
		return EXIT_FAILURE;
	}

	sf::Text text("biag", font);
	text.setCharacterSize(24);
	text.setPosition(300, 400);


	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			arr[i][j] = ""; 
		}
	}


	sf::RenderWindow window(sf::VideoMode(sideLen, sideLen), "Tic-tac-toe");
	window.setFramerateLimit(60);
	// sf::Window::setSize(int size)

	std::string letter = "O";

	bool startingScreen = true;
	bool gameScreen = false;
	bool winScreen = false;

	while (window.isOpen()) {

		window.clear(); 

		sf::Event event;
		while (window.pollEvent(event)) {

			// close window if close button clicked
			if (event.type == sf::Event::Closed)
				window.close();

			if (startingScreen) {
				window.draw(text); 
				window.display(); 
			}	


			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i clickPos = sf::Mouse::getPosition(window);

				if (startingScreen) {
					startingScreen = false; 
					gameScreen = true; 
				}

				if (gameScreen) {
					// switches letter
					if (validClick(clickPos, sideLen)) {
						if (letter == "O") {
							letter = "X";
						}
						else if (letter == "X") {
							letter = "O";
						}
					}

					// checks click and registers it in 2D array
					analyzeClick(clickPos, sideLen, arr, letter);
					checkWinner(arr, gameScreen, winScreen, text); 
				}
			}
			
		}

		if (gameScreen) {
			drawLetter(window, arr, sideLen);
			drawGrid(window, sideLen);
			window.display();
		}

		if (winScreen) {
			window.draw(text);
			window.display();
		}
	}

	return 0; 
}
