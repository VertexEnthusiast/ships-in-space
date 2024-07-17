#include <manager/spawner.hpp>
#include <entities/enemy.hpp>
#include <entities/entity.hpp>
#include <entities/spaceship.hpp>
#include <iostream>
#include <random>

Spawner::Spawner() : difficulty(0), timeUntilSpawn(0)
{
    // Explosion sound
    explosionBuffer.loadFromFile("assets/explosion_v1.wav");
    explosionSound.setBuffer(explosionBuffer);
    explosionSound.setVolume(30);

    // Spaceship hit sound
    hitBuffer.loadFromFile("assets/player_damaged.wav");
    hitSound.setBuffer(hitBuffer);
    hitSound.setVolume(80);
    spawn();
}

Spawner::~Spawner()
{
    puts("Spawner deleting");
}

/**
 * Call update on all enemies, powerups
 * Check conditions
 */
void Spawner::update(Spaceship &spaceship)
{
    if (timeUntilSpawn == 0)
    {
        spawn();
    }
    else
    {
        timeUntilSpawn--;
    }

    int enemyLen = enemies.size();
    for (int i = 0; i < enemyLen; i++)
    {
        // Check all the enemies to ensure none have 0 health
        if (enemies[i]->exploded)
        {
            enemies.erase(enemies.begin() + i);
            i--;
            enemyLen--;
            continue;
        }
        // Update enemy
        enemies[i]->update();
    }
    // Check if the enemy projectile has hit the player
    int projectileLen = enemyProjectiles.size();
    for (int j = 0; j < projectileLen; j++)
    {
        if (Entity::projectileCollides(enemyProjectiles[j].get(), &spaceship))
        {
            spaceship.health -= 1;
            hitSound.play();
            enemyProjectiles.erase(enemyProjectiles.begin() + j);
            projectileLen--;
            j--;
            continue;
        }
        else
        {
            enemyProjectiles[j]->update();
        }
    }
}

void Spawner::spawn()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 672);
    int x_pos;

    bool tooClose = true;
    int attempts = 0;
    // Ensure that there aren't any nearby enemies
    while (tooClose && attempts < 50)
    {
        attempts++;
        tooClose = false;
        x_pos = dis(gen);
        int enemyLen = enemies.size();

        int radius = 16;
        for (int i = 0; i < enemyLen; i++)
        {
            Enemy *enemy = &(*enemies[i]);
            if ((enemy->x > (x_pos - (32 * Entity::spriteScale.x + radius)) &&
                 enemy->x < (x_pos + 32 * Entity::spriteScale.x + radius)) &&
                (enemy->y < 16 * Entity::spriteScale.y))
            {
                tooClose = true;
                std::cout << "Enemy with coordinates: " << enemy->x << " " << enemy->y << " too close to " << x_pos << std::endl;
            }
        }
    }

    int health = 1;
    int speed = 2;

    struct FrameData frameInfo = {
        .framesPerUpdate = 6,
        .numFrames = 4,
        .xdim = 32,
        .ydim = 32};
    auto enemy = std::make_unique<Enemy>(x_pos, -100, "assets/basic_enemy.png", &frameInfo, health, speed, enemyProjectiles);

    enemies.push_back(std::move(enemy));

    timeUntilSpawn = spawnCooldown;
}
/**
 * Iterate through all enemies and delete 'exploded' enemies
 * and trigger explosion on 'killed' enemies
 */
bool Spawner::checkProjectileCollision(Entity *projectile)
{
    int enemyLen = enemies.size();
    for (int i = 0; i < enemyLen; i++)
    {
        if (Entity::projectileCollides(projectile, enemies[i].get()))
        {
            if (enemies[i]->health == 1 && !enemies[i]->killed)
            {
                // Begin explosion, enemy has been killed
                explosionSound.play();
                enemies[i]->killed = true;
                score++;
                return true;
            }
            else if (enemies[i]->health > 1)
            {
                enemies[i]->health -= 1;
                return true;
            }
        }
    }
    return false;
}
void checkNextWave();
void killEnemy(Enemy *enemy);
bool Spawner::checkLoss(){
    int enemyLen = enemies.size();
    for (int i = 0; i < enemyLen; i++)
    {
        if (enemies[i]->y > 600) {
            return true;
        }
    }
    return false;
}