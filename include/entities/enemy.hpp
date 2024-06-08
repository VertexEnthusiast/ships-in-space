#pragma once
#include <sprites/animated.hpp>
#include <entities/projectile.hpp>

class Enemy : public Animated
{
public:
    int health;
    int speed;
    int secondsUntilMove;
    int secondsUntilShoot = 30;
    int framesUntilDeath = -1;
    std::vector<std::unique_ptr<Projectile>> &fired;
    bool killed = false;
    bool exploded = false;

    Enemy(int x, int y, const char *texturePath, struct FrameData *frameInfo, int health, int speed, std::vector<std::unique_ptr<Projectile>> &fired);
    ~Enemy();

    void shoot();
    void move();
    void deadUpdate();

    void update();
};