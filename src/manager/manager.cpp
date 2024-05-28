#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <manager/manager.hpp>
#include <entities/entity.hpp>
#include <entities/spaceship.hpp>

// Constructor definition
GameManager::GameManager(sf::RenderWindow *gameWindow)
    : gameWindow(gameWindow), player(new Spaceship(0, 500))
{
    // Additional initialization if needed
    std::cout << "GameManager initialized with window pointer" << std::endl;
}

GameManager::~GameManager()
{
    std::cout << "Deleting GameManager";
}

// Update function definition
void GameManager::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
    {
        // left key is pressed: move our character
        puts("Moving left");
        player->move(-1, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
    {
        // right key is pressed: move our character
        puts("Moving right");
        player->move(1, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space))
    {
        // space is pressed: shoot
        puts("Spacebar pressed");
        player->shoot();
    }

    // Update game logic here
    player->update();

    // Updating player projectiles
    int len = player->fired.size();
    for (int i = 0; i < len; i++)
    {
        if (player->fired[i]->y < 0)
        {
            player->fired.erase(player->fired.begin() + i);
            // Since erasing vector component shifts whole vector reduce counting index and length of vector
            i--;
            len--;
        }
        else
            player->fired[i]->update();
    }
}

// Draw function definition
void GameManager::draw()
{
    // Draw sprites to the window here
    gameWindow->clear(sf::Color::Black);

    // Draw projectiles
    int len = player->fired.size();
    for (int i = 0; i < len; i++)
    {
        gameWindow->draw(player->fired[i]->sprite);
    }

    // Draw player
    gameWindow->draw(player->sprite);

    

    // Draw enemies

    gameWindow->display();
}