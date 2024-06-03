#pragma once

#include <SFML/Graphics.hpp>
#include <entities/entity.hpp>
#include <entities/spaceship.hpp>
#include <manager/spawner.hpp>

class GameManager
{
public:
    std::unique_ptr<Spaceship> player;
    std::unique_ptr<Spawner> spawner;
    sf::Font font;
    sf::Text scoreText;
    sf::Texture background;
    sf::Sprite backgroundSprite;

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