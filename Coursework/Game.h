#pragma comment(lib, "C:\\SFML-2.3\\lib\\sfml-graphics")
#pragma comment(lib, "C:\\SFML-2.3\\lib\\sfml-system")
#pragma comment(lib, "C:\\SFML-2.3\\lib\\sfml-window")
#pragma comment(lib, "C:\\SFML-2.3\\lib\\sfml-audio")

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "Tank.h"
#include "Bullet.h"
#include "Map.h"
#include "GameInterface.h"
#include "MouseCursor.h"
#include "TankBot.h"
#include "gamedef.h"

class Game {
public:
	Game();
	~Game();
	void run();
private:
	sf::RenderWindow window;
	sf::Texture gameTexture;
	//sf::Music gameTheme;

	Menu* menu;
	Map* map;
	Tank* player;
	MouseCursor* dynamicCursor;
	TankBot* bot;
	GameInterface* gameInterface;
	sf::SoundBuffer levelThemeBuffer;
	sf::Sound musicTheme;

	si gameState = MENU;
private:
	void update(float deltaTime);
	void render();
	void processEvents();
};


