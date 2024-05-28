#pragma once
#include <entities/entity.hpp>
#include <entities/projectile.hpp>

class Spaceship : public Entity
{
public:
    std::vector<std::unique_ptr<Projectile>> fired;
    const int maxCooldown = 60;
    int cooldown;

    Spaceship(int x, int y);
    ~Spaceship();

    void shoot();
    void move(int x, int y);
    void update() override;

    enum Direction
    {
        LEFT,
        DOWN,
        UP,
        RIGHT
    };
};