#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <manager/manager.hpp>
#include <entities/entity.hpp>
#include <entities/spaceship.hpp>

// Constructor definition
GameManager::GameManager(sf::RenderWindow *gameWindow)
    : gameWindow(gameWindow)
{
    // Initialise enemy spawner
    spawner = std::make_unique<Spawner>();
    font.loadFromFile("assets/8bit.ttf");

    // Initialise score text
    scoreText.setFont(font);
    scoreText.setPosition(10, 10);
    scoreText.setCharacterSize(24);
    // scoreText.setFillColor(sf::Color::White);

    // Initialise player

    struct FrameData frameInfo ={
        .framesPerUpdate = 6,
        .numFrames = 4,
        .xdim = 32,
        .ydim = 32
    };
    player = std::make_unique<Spaceship>(0, 500, "assets/animated_big_spaceship_v3.png", &frameInfo);
    std::cout << "GameManager initialized with window pointer" << std::endl;

    background.loadFromFile("assets/starry_background.png");
    backgroundSprite.setTexture(background);
    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setScale(4.0f, 4.0f);
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

    // Update spawner
    spawner->update();

    // Updating player projectiles
    int len = player->fired.size();
    for (int i = 0; i < len; i++)
    {
        if (player->fired[i]->y < -32 || spawner->checkProjectileCollision(&(*player->fired[i])))
        {
            player->fired.erase(player->fired.begin() + i);
            // Since erasing vector component shifts whole vector reduce counting index and length of vector
            i--;
            len--;
        }
        else
        {
            player->fired[i]->update();
        }
    }

    // Update score
    scoreText.setString("Score: " + std::to_string(spawner->score));
}

// Draw function definition
void GameManager::draw()
{
    // Draw sprites to the window here
    gameWindow->clear(sf::Color::Black);
    gameWindow->draw(backgroundSprite);


    // Draw projectiles
    int firedLen = player->fired.size();
    for (int i = 0; i < firedLen; i++)
    {
        gameWindow->draw(player->fired[i]->sprite);
    }


    // Draw player
    gameWindow->draw(player->sprite);

    
    // Draw enemies
    int enemyLen = spawner->enemies.size();
    for (int i = 0; i < enemyLen; i++)
    {
        gameWindow->draw(spawner->enemies[i]->sprite);
    }

    // Draw score
    gameWindow->draw(scoreText);


    gameWindow->display();
}