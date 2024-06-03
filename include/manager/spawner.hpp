#pragma once

#include <entities/enemy.hpp>
#include <SFML/Audio.hpp>
/**
 * This class is responsible for spawning enemies and powerups, 
 * and handles deletion of enemies once they are killed
*/
class Spawner {
public:
    std::vector<std::unique_ptr<Enemy>> enemies;
    //
    int difficulty;
    int score = 0;
    int timeUntilSpawn;
    sf::SoundBuffer explosionBuffer;
    sf::Sound explosionSound;




    Spawner();
    ~Spawner();

    void update();
    void spawn();
    bool checkProjectileCollision(Entity* projectile);
    void checkEnemies();
    void checkNextWave();
    void killEnemy(Enemy* enemy);
};