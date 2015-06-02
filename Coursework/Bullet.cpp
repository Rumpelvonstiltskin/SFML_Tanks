#include "Bullet.h"
#define OUTSIDE_AREA bulletPos.x > 1920 || bulletPos.x < 0 || bulletPos.y < 0 || bulletPos.y > 1080


Bullet::Bullet(sf::Texture &texture, sf::Vector2f gun_pos, float angle, float level)
{
	bullet.setTexture(texture);
	bulletTexture.setSmooth(true);
	bullet.setTextureRect(sf::IntRect(435, 1925, 34, 34));
	bullet.setOrigin(17, 17);

	angle = angle * 3.14 / 180;
	bullet.setPosition(gun_pos.x + 115 * sin(angle), gun_pos.y - 115 * cos(angle));

	dx = (1 + (level / 2)) * sin(angle);
	dy = -(1 + (level / 2)) * cos(angle);
}


Bullet::~Bullet()
{
}

void Bullet::update(float deltaTime)
{
	sf::Vector2f bulletPos = bullet.getPosition();

	bullet.move(dx * deltaTime, dy * deltaTime);

	if (OUTSIDE_AREA) life = false;
}

sf::Vector2f Bullet::getPosition()
{
	return bullet.getPosition();
}

void Bullet::draw(sf::RenderWindow &window)
{
	window.draw(bullet);
}
