#include "MouseCursor.h"
#define CURSOR_PICKER_ZONE (mousePos.y > 840) || (pow(mousePos.x - 960, 2) / 3450306 + pow(mousePos.y + 120, 2) / 67600 <= 1)


MouseCursor::MouseCursor(sf::Texture &texture)
{
	targetCursor.setTexture(texture);
	targetCursor.setTextureRect(sf::IntRect(290, 1925, 50, 50));
	targetCursor.setOrigin(25, 25);

	pickerCursor.setTexture(texture);
	pickerCursor.setTextureRect(sf::IntRect(340, 1925, 50, 50));
	pickerCursor.setOrigin(10, 10);
}


void MouseCursor::update()
{
	sf::Mouse mouse;
	sf::Vector2i mousePos = mouse.getPosition();

	if (CURSOR_PICKER_ZONE) {
		changeCursor = true;
		pickerCursor.setPosition(mousePos.x, mousePos.y);
	}
	else {
		changeCursor = false;
		targetCursor.setPosition(mousePos.x, mousePos.y);
	}
}


void MouseCursor::draw(sf::RenderWindow &window)
{
	if (changeCursor) {
		window.draw(pickerCursor);
	}
	else {
		window.draw(targetCursor);
	}
}


MouseCursor::~MouseCursor()
{
}
