#include "Bullets.h"
#include "Values.h"
#include <iostream>

Bullets::Bullets(long positionPlayerX)
{
	m_bullet = sf::RectangleShape(sf::Vector2f(5, 15));
	m_bullet.setFillColor(sf::Color::White);
	m_bullet.setPosition(positionPlayerX, BULLET_BASEY_PLAYER);

	m_bulletPositionY = BULLET_BASEY_PLAYER;
	m_bulletPositionX = positionPlayerX;
}

void Bullets::setPositionY()
{
	m_bulletPositionY = BULLET_BASEY_PLAYER; 
}

void Bullets::setPositionX(long positionPlayerX)
{
	m_bulletPositionX = positionPlayerX;
}

void Bullets::draw(sf::RenderWindow& myWindow)
{
	if (m_bullet.getPosition().y >= 0)
	{
		m_bullet.setPosition(m_bulletPositionX, m_bulletPositionY);
		m_bulletPositionY -= BULLET_SPEED;
		myWindow.draw(m_bullet);
	}
}