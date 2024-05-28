#pragma once

#include <SFML/Graphics.hpp>
#include <entities/entity.hpp>
#include <entities/spaceship.hpp>

class GameManager
{
public:
    Spaceship *player;

    GameManager(sf::RenderWindow *gameWindow);
    ~GameManager();

    /**
     * This function is reponsible for updating all the game logic
     */
    void update();

    /**
     * This function is responsible for drawing sprites to the window
     */
    void draw();

private:
    sf::RenderWindow *gameWindow;
};