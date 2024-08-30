/*
	checkwinner
	alternating X or O function

	draw X
	draw O 

	stop functionality once winner

	play screen
	winner screen
*/ 

#include <SFML/Graphics.hpp>
#include <utility>
#include <cmath>
#include <iostream>

void drawGrid(sf::RenderWindow &window, int sideLen) {
	int unit = sideLen / 14; 

	sf::RectangleShape vLine1(sf::Vector2f(unit * .6, sideLen));
	vLine1.setPosition(unit * 4.6, 0);
	sf::RectangleShape vLine2(sf::Vector2f(unit * .6, sideLen));
	vLine2.setPosition(unit * 9.6, 0);

	sf::RectangleShape hLine1(sf::Vector2f(sideLen, unit * .6));
	hLine1.setPosition(0, unit * 4.6);
	sf::RectangleShape hLine2(sf::Vector2f(sideLen, unit * .6));
	hLine2.setPosition(0, unit * 9.6);
	
	window.draw(vLine1);
	window.draw(vLine2);
	window.draw(hLine1);
	window.draw(hLine2); 
}

int countUnits(int val) {
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

// in wherever there was a click, the 2D array will filled with the value 100 
void analyzeClick(sf::Vector2i clickPos, int sideLen, std::string (&arr)[3][3]) {
	
	int unit = sideLen / 14;

	int xUnits;
	int yUnits;

	xUnits = clickPos.x / unit; 
	yUnits = clickPos.y / unit; 

	int xGrid = countUnits(xUnits); 
	int yGrid = countUnits(yUnits); 

	if (xGrid != -1 && yGrid != -1) {
		arr[xGrid][yGrid] = "filled"; // use the alternating x or o function to fill this 
	}
} 

bool checkLine(std::string a, std::string b, std::string c, std::string player) {
	return a == player && b == player && c == player; 
}

void checkWinner(std::string(&arr)[3][3]) {
	std::string players[2] = { "X", "O" };

	for (const std::string player : players) {
		for (int i = 0; i < 3; i++) {
			if (checkLine(arr[i][0], arr[i][1], arr[i][2], player) ||
				checkLine(arr[0][i], arr[1][i], arr[2][i], player)) {
			}
			std::cout << player << " wins" << std::endl;
			return;
		}

		if (checkLine(arr[0][0], arr[1][1], arr[2][2], player) ||
			checkLine(arr[0][2], arr[1][1], arr[2][0], player)) {
			std::cout << player << " wins" << std::endl; 
			return; 
		}
	}


	// more efficient checkwinner func
}


int main() {
	int sideLen = 700; 
	std::string arr[3][3]; 

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			arr[i][j] = ""; 
		}
	}


	sf::RenderWindow window(sf::VideoMode(sideLen, sideLen), "Tic-tac-toe");
	window.setFramerateLimit(60);
	// sf::Window::setSize(int size)

	while (window.isOpen()) {

		window.clear(); 

		sf::Event event;
		while (window.pollEvent(event))
		{

			// close window if close button clicked
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i clickPos = sf::Mouse::getPosition(window);
				analyzeClick(clickPos, sideLen, arr); 
			}

		}


		drawGrid(window, sideLen); 
		window.display();
	}

	return 0; 
}
