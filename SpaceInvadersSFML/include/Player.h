#pragma once
#include "Bullets.h"
#include <SFML/Graphics.hpp>

class Player
{
	public:
		Player();

		void actionPlayer();
		const long getPositionX() { return m_playerPositionX; }
		std::vector<Bullets> getFiredBullets() { return m_firedBullets; }
		std::vector<Bullets> getActiveBullets() { return m_activeBullets; }
		void draw(sf::RenderWindow& myWindow);
		void updateVectorBullets(size_t j);
		sf::Sprite getSprite() { return m_player; }
		void substractLifes() { m_lifes--; }
		void setLifes(float lifes) { m_lifes = lifes; }
		float getLifes() { return m_lifes; }
		void setScore(float score) { m_score += score; }
		void resetScore() { m_score = 0; }
		float getScore() { return m_score; }

	private:
		long m_playerPositionX;
		long m_reload;
		float m_lifes;
		float m_score;
		sf::Sprite m_player;
		sf::Texture m_texture;
		std::vector<Bullets> m_activeBullets;
		std::vector<Bullets> m_firedBullets;
};