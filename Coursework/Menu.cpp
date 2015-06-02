#include "Menu.h"


Menu::Menu()
{
	if (!menuItems.loadFromFile("Resources\\Squares.otf")) {
		exit(1);
	}

	if (!about.loadFromFile("Resources\\ArmyStamp.ttf")) {
		exit(1);
	}
	
	for (int i = 0; i <= 3; ++i) {
		item[i].setFont(menuItems);
		item[i].setColor(sf::Color::White);
		item[i].setPosition(sf::Vector2f(1920 / 2.4, (i + 1) * 1080 / 5 - 20));
		item[i].setCharacterSize(72);
	}

	item[0].setColor(sf::Color::Yellow);

	item[0].setString("Play");
	item[1].setString("Options");
	item[2].setString("About");
	item[3].setString("Exit");

	item[4].setString("Music Volume");
	item[5].setString("SFX Volume");

	item[4].setFont(menuItems);
	item[4].setCharacterSize(50);
	item[4].setPosition(300, 440);
	item[4].setColor(sf::Color::Yellow);

	item[5].setFont(menuItems);
	item[5].setCharacterSize(50);
	item[5].setPosition(300, 560);

	selectedItemIndexMenu = 0;

	for (int i = 0; i <= 2; i++) {
		aboutItem[i].setFont(about);
		aboutItem[i].setColor(sf::Color(34, 101, 15));
		aboutItem[i].setCharacterSize(150);
		aboutItem[i].setPosition(300, 370 + i * 100);
	}

	aboutItem[0].setString("Tanks v1.0");
	aboutItem[1].setString("Author: Dmitry Chabanenko");

	for (int j = 0; j <= 1; j++)
	for (int i = 0; i <= 9; i++) {
		bar[i][j].setSize(sf::Vector2f(40, 80));
		bar[i][j].setPosition(1000 + i * 50, 440 + j * 120);
	}

	if (!menuThemeBuffer.loadFromFile("Resources\\menu_theme.ogg")) exit(1);
	menuTheme.setBuffer(menuThemeBuffer);
	menuTheme.setLoop(true);
}


Menu::~Menu()
{
}


void Menu::update(float deltaTime, int gameState)
{
	delayTime += deltaTime;
	this->gameState = gameState;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (delayTime > 200) {
			if (gameState == 4) {
				if (selectedItemIndexMenu >= 1) {
					item[selectedItemIndexMenu].setColor(sf::Color::White);
					selectedItemIndexMenu--;
					item[selectedItemIndexMenu].setColor(sf::Color::Yellow);
				}
				else {
					item[selectedItemIndexMenu].setColor(sf::Color::White);
					selectedItemIndexMenu = 3;
					item[selectedItemIndexMenu].setColor(sf::Color::Yellow);
				}
			}

			if (gameState == 1) {
				if (selectedItemIndexOptions == 5) {
					item[selectedItemIndexOptions].setColor(sf::Color::White);
					selectedItemIndexOptions = 4;
					item[selectedItemIndexOptions].setColor(sf::Color::Yellow);
				}
				else {
					item[selectedItemIndexOptions].setColor(sf::Color::White);
					selectedItemIndexOptions = 5;
					item[selectedItemIndexOptions].setColor(sf::Color::Yellow);
				}
			}

			delayTime = 0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (delayTime > 200) {
			if (gameState == 4) {
				if (selectedItemIndexMenu <= 2) {
					item[selectedItemIndexMenu].setColor(sf::Color::White);
					selectedItemIndexMenu++;
					item[selectedItemIndexMenu].setColor(sf::Color::Yellow);
				}
				else {
					item[selectedItemIndexMenu].setColor(sf::Color::White);
					selectedItemIndexMenu = 0;
					item[selectedItemIndexMenu].setColor(sf::Color::Yellow);
				}
			}

			if (gameState == 1) {
				if (selectedItemIndexOptions == 5) {
					item[selectedItemIndexOptions].setColor(sf::Color::White);
					selectedItemIndexOptions = 4;
					item[selectedItemIndexOptions].setColor(sf::Color::Yellow);
				}
				else {
					item[selectedItemIndexOptions].setColor(sf::Color::White);
					selectedItemIndexOptions = 5;
					item[selectedItemIndexOptions].setColor(sf::Color::Yellow);
				}
			}

			delayTime = 0;
		}
	}

	for (int j = 0; j <= 1; j++)
	for (int i = 0; i <= 9; ++i)
		bar[i][j].setFillColor(sf::Color::Black);

	for (int i = 0; i <= musicVolumeState; i++)
		bar[i][0].setFillColor(sf::Color(i * 28, 255 - i * 28, 0));

	for (int i = 0; i <= sfxVolumeState; i++)
		bar[i][1].setFillColor(sf::Color(i * 28, 255 - i * 28, 0));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (delayTime > 50) {
			if (selectedItemIndexOptions == 4) {
				musicVolumeState--;
			}

			if (selectedItemIndexOptions == 5) {
				sfxVolumeState--;
			}

			delayTime = 0;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (delayTime > 50) {
			if (selectedItemIndexOptions == 4) {
				musicVolumeState++;
			}

			if (selectedItemIndexOptions == 5) {
				sfxVolumeState++;
			}
			
			delayTime = 0;
		}
	}

	if (musicVolumeState < -1) musicVolumeState = -1;
	if (musicVolumeState > 9) musicVolumeState = 9;

	if (sfxVolumeState < -1) sfxVolumeState = -1;
	if (sfxVolumeState > 9) sfxVolumeState = 9;

	if (menuTheme.getStatus() == 0)
		menuTheme.play();
}


void Menu::draw(sf::RenderWindow &window)
{
	window.clear(sf::Color(221, 201, 93));
	if (gameState == 4)
	for (int i = 0; i < 4; i++) {
		window.draw(item[i]);
	}

	if (gameState == 2)
	for (int i = 0; i <= 2; i++)
		window.draw(aboutItem[i]);

	if (gameState == 1) {
		for (int j = 0; j <= 1; j++)
			for (int i = 0; i <= 9; i++) {
				window.draw(bar[i][j]);
			}
		window.draw(item[4]);
		window.draw(item[5]);
	}
}


int Menu::GetPressedItem()
{
	return selectedItemIndexMenu;
}