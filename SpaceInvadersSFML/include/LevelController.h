#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Enemies.h"

class LevelController
{
public:
    LevelController();

    std::vector<Enemies> createLevel(std::vector<Enemies> activeEnemy, long offsetEnemies);
    float getLevel() { return m_level; }
    void levelUp() { m_level++; }
    void resetLevel();
    void resetHeight(){ m_height = 45;}

    private:
        float m_level;
        float m_height;
};