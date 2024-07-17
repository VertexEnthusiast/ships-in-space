#include <sprites/animated.hpp>
#include <entities/enemy.hpp>
#include <iostream>

Enemy::Enemy(int x, int y, const char *texturePath, struct FrameData *frameInfo, int health, int speed, std::vector<std::unique_ptr<Projectile>> &fired)
    : Animated(x, y, texturePath, frameInfo), health(health), speed(speed), fired(fired)
{
    puts("Wooooo enemy made");
}

Enemy::~Enemy()
{
    puts("Deleted enemy");
}

void Enemy::update()
{
    if (killed)
    {
        deadUpdate();
    }
    else if (secondsUntilMove > 0)
    {
        secondsUntilMove--;
    }
    else
    {
        move();
    }

    if (!killed)
    {
        if (secondsUntilShoot == 0)
        {
            shoot();
            secondsUntilShoot = 90;
        }
        else
        {
            secondsUntilShoot--;
        }
    }
    animate();
    sprite.setPosition(sf::Vector2f(x, y));
}

void Enemy::shoot()
{
    int speed = -6;
    struct FrameData data = {
        .numFrames = 1,
        .framesPerUpdate = 1,
        .xdim = 32,
        .ydim = 32};
    auto projectile = std::make_unique<Projectile>(this->x, this->y, "assets/basic_enemy_projectile.png", &data, speed);
    fired.push_back(std::move(projectile)); // Move the unique_ptr into the vector
}
void Enemy::deadUpdate()
{
    if (framesUntilDeath < 0)
    {
        // Then it hasn't been set to 'dead' yet
        struct FrameData frameInfo = {
            .numFrames = 6,
            .framesPerUpdate = 6,
            .xdim = 32,
            .ydim = 32};
        framesUntilDeath = frameInfo.framesPerUpdate * frameInfo.numFrames - 3;
        updateAnimation("assets/explosion.png", &frameInfo);
    }
    else if (framesUntilDeath > 0)
    {
        framesUntilDeath--;
    }
    else
    {
        exploded = true;
    }
}



void Enemy::move()
{
    y += 4 * speed;
    secondsUntilMove = 30;
}