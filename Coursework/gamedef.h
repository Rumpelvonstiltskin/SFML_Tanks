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

#pragma once
typedef short int si;

enum gameStates {
	GAME, OPTIONS, ABOUT, EXIT, MENU, PAUSE
};

#define OUTSIDE_AREA bulletPos.x > 1920 || bulletPos.x < 0 || bulletPos.y < 0 || bulletPos.y > 1080
#define CURSOR_PICKER_ZONE (mousePos.y > 840) || (pow(mousePos.x - 960, 2) / 3450306 + pow(mousePos.y + 120, 2) / 67600 <= 1)
#define ELLIPSE_Y 260 * sqrt(1 - pow(tankPos.x - 960, 2) / 3450306) - 50
#define BATTLE_ZONE (mousePos.y < 840) && (pow(mousePos.x - 960, 2) / 3450306 + pow(mousePos.y + 120, 2) / 67600 >= 1)