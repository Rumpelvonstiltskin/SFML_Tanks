#pragma once
#include <SFML/Graphics.hpp>

class MouseCursor
{
public:
	MouseCursor(sf::Texture &texture);
	~MouseCursor();
	void update();
	void draw(sf::RenderWindow &window);
private:
	sf::Sprite targetCursor;
	sf::Sprite pickerCursor;
	sf::Mouse mouse;

	bool changeCursor = false;
};

