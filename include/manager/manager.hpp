#pragma once

#include <SFML/Graphics.hpp>
#include <entities/entity.hpp>
#include <entities/spaceship.hpp>
#include <manager/spawner.hpp>
#include <ui/button.hpp>

class GameManager
{
public:
    std::unique_ptr<Spaceship> player;
    std::unique_ptr<Spawner> spawner;
    sf::Font font;
    sf::Text scoreText;
    sf::Text highscoreText;
    sf::Texture background;
    sf::Sprite backgroundSprite;
    std::unique_ptr<Button> startButton;
    std::unique_ptr<Button> quitButton;
    std::unique_ptr<Button> restartButton;
    std::unique_ptr<Animated> healthBar;


    bool started = 0;
    bool ended = 0;
    bool quit = 0;

    int highscore = 0;

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

    void handleMovement();
    void handleUpdates();

    void drawGame();
    void drawStart();
    void drawEnd();

    void constructGame();
    void restartGame();

private:
    sf::RenderWindow *gameWindow;
};