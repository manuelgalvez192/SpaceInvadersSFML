#pragma once
#include <SFML/Graphics.hpp>

class BulletsEnemy
{
	public:
		BulletsEnemy(long positionEnemyX, long positionEnemyY);

		const long getPositionY() { return m_bulletPositionY; }
		sf::RectangleShape getSprite() { return m_bullet; }
		void setPositionY(long positionEnemyY);
		void setPositionX(long positionEnemyX);
		void draw(sf::RenderWindow& myWindow);

	private:
		long m_bulletPositionY;
		long m_bulletPositionX;
		sf::RectangleShape m_bullet;
};