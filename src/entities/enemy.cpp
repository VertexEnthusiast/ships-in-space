#include <sprites/animated.hpp>
#include <entities/enemy.hpp>

Enemy::Enemy(int x, int y, const char *texturePath, struct FrameData *frameInfo, int health, int speed) : Animated(x, y, texturePath, frameInfo), health(health), speed(speed)
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
    animate();
    sprite.setPosition(sf::Vector2f(x, y));
}

void Enemy::deadUpdate()
{
    if (framesUntilDeath < 0)
    {
        // Then it hasn't been set to 'dead' yet
        struct FrameData frameInfo = {
            .framesPerUpdate = 6,
            .numFrames = 6,
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