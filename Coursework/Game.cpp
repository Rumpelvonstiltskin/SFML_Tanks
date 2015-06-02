#include "Game.h"


void Game::run()
{
	sf::Clock clock;
	float timeSinceLastUpdate = 0;

	while (window.isOpen()) {
		timeSinceLastUpdate = clock.getElapsedTime().asMilliseconds();
		clock.restart();

		processEvents();
		update(timeSinceLastUpdate);
		render();
	}
}

Game::Game() : window(sf::VideoMode::getDesktopMode(), "Game", sf::Style::Fullscreen)
{
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(144);

	if (!gameTexture.loadFromFile("Resources\\Game_Texture.png")) exit(1);
	gameTexture.setSmooth(true);

	gameInterface = new GameInterface(gameTexture);
	player = new Tank(gameTexture);
	bot = new TankBot(gameTexture);
	dynamicCursor = new MouseCursor(gameTexture);
	map = new Map(gameTexture);
	menu = new Menu;

	//GameInterface gameInterface = GameInterface(gameTexture);
	//window.setVerticalSyncEnabled(true);
	//int newH = (1920 * window.getSize().y) / window.getSize().x;
	//int displace = (newH - 1080) / (-2);
	//sf::View view = sf::View(sf::FloatRect(0, 0, 1920, newH));
	//std::cout << view.getCenter().x << ' ' << view.getCenter().y << std::endl;
	//view.setCenter(window.getSize().x / 2, (1080 - displace) / 2);
	//window.setView(view);
}


void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code) {
				case sf::Keyboard::Escape:
					if (gameState == MENU) {
						exit(0);
					}
					else {
						gameState = MENU;
					}
					break;
				case sf::Keyboard::Space:
					if (menu->GetPressedItem() == GAME) {
						gameState = GAME;
					}
					if (menu->GetPressedItem() == OPTIONS) {
						gameState = OPTIONS;
					}
					if (menu->GetPressedItem() == ABOUT) {
						gameState = ABOUT;
					}
					if (menu->GetPressedItem() == EXIT) {
						exit(0);
					}
					break;
				default:
					break;
			}
		}

		if (event.type == sf::Event::Closed)
			window.close();
	}
}


void Game::update(float deltaTime)
{
	if (gameState == GAME) {
		gameInterface->update(player->stats, deltaTime);
		map->update(deltaTime);
		player->update(deltaTime);
		bot->update(deltaTime, player->getGunPosition(), player->getFirstBulletPosition(), player->life);
		dynamicCursor->update();
	}

	if (gameState != GAME && gameState !=EXIT)
		menu->update(deltaTime, gameState);
}


void Game::render()
{
	window.clear();

	switch (gameState) {
		case MENU:
			menu->draw(window);
			break;
		case GAME:
			map->draw(window);
			player->draw(window);
			bot->draw(window);
			gameInterface->draw(window);
			dynamicCursor->draw(window);
			break;
		case OPTIONS:
			menu->draw(window);
			break;
		case ABOUT:
			menu->draw(window);
			break;
		default:
			break;
	}

	window.display();
}


Game::~Game()
{
}
