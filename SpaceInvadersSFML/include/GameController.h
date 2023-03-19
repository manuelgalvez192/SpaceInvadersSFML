#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Enemies.h"
#include "Player.h"

class GameController
{
    public:
        GameController();
        
        void update();
        bool isInvaderCrashing(std::vector<Enemies> activeEnemy, Player p1);

    private:
        sf::RenderWindow m_window;
};