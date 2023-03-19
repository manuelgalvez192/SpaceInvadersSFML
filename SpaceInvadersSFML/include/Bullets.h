#pragma once
#include <SFML/Graphics.hpp>

class Bullets
{
	public:
		Bullets(long positionPlayerX);

		const long getPositionY() { return m_bulletPositionY; }
		sf::RectangleShape getSprite() { return m_bullet; }
		void setPositionY();
		void setPositionX(long positionPlayerX);
		void draw(sf::RenderWindow& myWindow);
		
	private:
		long m_bulletPositionY;
		long m_bulletPositionX;
		sf::RectangleShape m_bullet;
};