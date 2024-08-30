/*
	pair class for the 2d array 
	
	checkwinner


	draw X
	draw O 
	alternating X or O function

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
void analyzeClick(sf::Vector2i clickPos, int sideLen, int (&arr)[3][3]) {
	
	int unit = sideLen / 14;

	int xUnits;
	int yUnits;

	xUnits = clickPos.x / unit; 
	yUnits = clickPos.y / unit; 

	int xGrid = countUnits(xUnits); 
	int yGrid = countUnits(yUnits); 

	if (xGrid != -1 && yGrid != -1) {
		arr[xGrid][yGrid] = 100;
	}
} 

void checkWinner(int(&arr)[3][3]) {
	// more efficient checkwinner func
}


int main() {
	int sideLen = 700; 
	int arr[3][3]; 


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
