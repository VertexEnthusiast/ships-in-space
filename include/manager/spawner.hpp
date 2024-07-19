#pragma once

#include <entities/enemy.hpp>
#include <entities/spaceship.hpp>
#include <SFML/Audio.hpp>
/**
 * This class is responsible for spawning enemies and powerups,
 * and handles deletion of enemies once they are killed
 */
class Spawner
{
public:
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Projectile>> enemyProjectiles;
    sf::SoundBuffer explosionBuffer;
    sf::Sound explosionSound;
    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;

    int difficulty;
    int score = 0;
    int spawnCooldown = 80;
    int timeUntilSpawn;

    Spawner();
    ~Spawner();

    void update(Spaceship& spaceship);
    void spawn();
    bool checkProjectileCollision(Entity *projectile);
    bool checkLoss();
};