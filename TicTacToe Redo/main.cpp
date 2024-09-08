#include <SFML/Graphics.hpp>
#include <utility>
#include <cmath>
#include <iostream>

void drawGrid(sf::RenderWindow &window, int sideLen) {
	int unit = sideLen / 14; 

	sf::RectangleShape vLine1(sf::Vector2f(unit, sideLen));
	vLine1.setPosition(unit * 4, 0);
	sf::RectangleShape vLine2(sf::Vector2f(unit, sideLen));
	vLine2.setPosition(unit * 9, 0);

	sf::RectangleShape hLine1(sf::Vector2f(sideLen, unit));
	hLine1.setPosition(0, unit * 4);
	sf::RectangleShape hLine2(sf::Vector2f(sideLen, unit));
	hLine2.setPosition(0, unit * 9);
	
	window.draw(vLine1);
	window.draw(vLine2);
	window.draw(hLine1);
	window.draw(hLine2); 
}

// clickXY is the x or y coordinate of where the click happened. countUnits will be called twice 
// returns the grid that the click was 
float countUnits(int clickXY, int sideLen) {

	float unit = sideLen / 14; 
	int val = clickXY / unit; 

	if (val > 0 && val < 4) {
		return 0;
	}
	else if (val > 5 && val < 9) {
		return 1; 
	} 
	else if (val > 10 && val < 14) {
		return 2; 
	} else {
		return -1; 
	}
}

bool validClick(sf::Vector2i clickPos, int sideLen) {
	if (countUnits(clickPos.x, sideLen) != -1 && countUnits(clickPos.y, sideLen) != -1) {
		return true; 
	}
	return false; 
}

// in wherever there was a click, the 2D array will filled with the value 100 
void analyzeClick(sf::Vector2i clickPos, int sideLen, std::string (&arr)[3][3], std::string letter) {

	int xGrid = countUnits(clickPos.x, sideLen); 
	int yGrid = countUnits(clickPos.y, sideLen);

	if (xGrid != -1 && yGrid != -1) {
		arr[xGrid][yGrid] = letter; // use the alternating x or o function to fill this 
	}
} 

bool checkLine(std::string a, std::string b, std::string c, std::string player) {
	return a == player && b == player && c == player; 
}

void checkWinner(std::string(&arr)[3][3], bool& gameScreen, bool& winScreen, sf::Text& text) {
	std::string players[2] = { "X", "O" };

	for (const std::string player : players) {
		for (int i = 0; i < 3; i++) {
			if (checkLine(arr[i][0], arr[i][1], arr[i][2], player) ||
			checkLine(arr[0][i], arr[1][i], arr[2][i], player)) {
				std::cout << player << " wins" << std::endl;
				gameScreen = false;
				winScreen = true;
				text.setString(player + " won"); 
				return;
			}
		}

		if (checkLine(arr[0][0], arr[1][1], arr[2][2], player) ||
		checkLine(arr[0][2], arr[1][1], arr[2][0], player)) {
			std::cout << player << " wins" << std::endl; 
			gameScreen = false;
			winScreen = true;
			text.setString(player + " won");
			return; 
		}
	}
}


void drawX(sf::RenderWindow& window, int sideLen, int x, int y) { // takes for input the x and y (and window), then draws X
	int unit = sideLen / 14; 

	int length = sqrt(2 * ((3 * unit) * (3 * unit)));
	int thickness = 10; 
	
	// declaration 
	sf::RectangleShape line1(sf::Vector2f(length - thickness, thickness));
	sf::RectangleShape line2(sf::Vector2f(length - thickness, thickness));

	// setting the positions
	line1.setPosition((unit * x * 5) + (unit * 2), (unit * y * 5) + (unit * 2));
	line2.setPosition((unit * x * 5) + (unit * 2), (unit * y * 5) + (unit * 2));

	// setting the origin of the lines to the center
	line1.setOrigin(line1.getSize().x / 2, line1.getSize().y / 2); // line1 
	line1.setRotation(45);

	line2.setOrigin(line2.getSize().x / 2, line2.getSize().y / 2); // line2
	line2.setRotation(135);

	window.draw(line1);
	window.draw(line2);

}

void drawO(sf::RenderWindow& window, int sideLen, int x, int y) {
	int unit = sideLen / 14;

	int thickness = 10; 

	sf::CircleShape circle(1.5 * unit);

	circle.setOrigin(circle.getRadius(), circle.getRadius());

	circle.setPosition((unit * x * 5) + (unit * 2), (unit * y * 5) + (unit * 2));

	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(thickness);

	window.draw(circle);
}


void drawLetter(sf::RenderWindow &window, std::string (&arr)[3][3], int sideLen) {
	// iterates through the grid, and any time x or o is found it draws it
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) { 
			if (arr[i][j] == "X") {
				drawX(window, sideLen, i, j);
			}
			else if (arr[i][j] == "O") {
				drawO(window, sideLen, i, j);
			}
		}
	}
}


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
