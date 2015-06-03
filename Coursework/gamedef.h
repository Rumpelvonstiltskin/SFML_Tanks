#pragma once
typedef short int si;

enum gameStates {
	GAME, OPTIONS, ABOUT, EXIT, MENU, PAUSE
};

#define OUTSIDE_AREA bulletPos.x > 1920 || bulletPos.x < 0 || bulletPos.y < 0 || bulletPos.y > 1080
#define CURSOR_PICKER_ZONE (mousePos.y > 840) || (pow(mousePos.x - 960, 2) / 3450306 + pow(mousePos.y + 120, 2) / 67600 <= 1)
#define ELLIPSE_Y 260 * sqrt(1 - pow(tankPos.x - 960, 2) / 3450306) - 50
#define BATTLE_ZONE (mousePos.y < 840) && (pow(mousePos.x - 960, 2) / 3450306 + pow(mousePos.y + 120, 2) / 67600 >= 1)