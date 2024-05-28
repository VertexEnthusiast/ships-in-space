#pragma once
#include <entities/entity.hpp>

class Projectile : public Entity
{
public:
    int speed;
    sf::IntRect frames[14];
    int currentFrame;
    const int frameLength = 6;
    int frameTime;

    Projectile(int x, int y, int speed);

    void update() override;
};