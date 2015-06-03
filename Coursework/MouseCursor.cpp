/*
===========================================================================
This project distributed under GNU GPLv3
Copyright (C) 2015 Chabanenko Dmitry
This file is part of the Tanks GPL Source Code.
Tanks Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
Tanks Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with Tanks Source Code.  If not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

#include "MouseCursor.h"


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
