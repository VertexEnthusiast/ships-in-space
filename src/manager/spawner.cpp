#include <manager/spawner.hpp>
#include <entities/enemy.hpp>
#include <entities/entity.hpp>
#include <iostream>
#include <random>

Spawner::Spawner() : difficulty(0), timeUntilSpawn(0)
{
    explosionBuffer.loadFromFile("assets/explosion_v1.wav");
    explosionSound.setBuffer(explosionBuffer);
    explosionSound.setVolume(30);
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
void Spawner::update()
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
        if (enemies[i]->exploded){
            enemies.erase(enemies.begin() + i);
            i--;
            enemyLen--;
            continue;
        }
        // Update enemy
        enemies[i]->update();
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
    auto enemy = std::make_unique<Enemy>(x_pos, -100, "assets/basic_enemy.png", &frameInfo, health, speed);

    enemies.push_back(std::move(enemy));

    timeUntilSpawn = 120;
}
/**
 * Iterate through all enemies and delete 'exploded' enemies
 * and trigger explosion on 'killed' enemies
 */
bool Spawner::checkProjectileCollision(Entity * projectile)
{
    int x = projectile->x;
    int y = projectile->y;
    int width = projectile->sprite.getGlobalBounds().width;
    int height = projectile->sprite.getGlobalBounds().height;
    x += width / 3;
    y += height / 3;
    width /= 3;
    height /= 3;

    // int x, int y, int width, int height
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
void killEnemy(Enemy * enemy);