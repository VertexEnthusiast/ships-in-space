#pragma once
#include <entities/entity.hpp>

class Projectile : public Entity {
public:
    int speed;
    sf::IntRect frames[14];
    int currentFrame;
    const int frameLength = 4;
    int frameTime;

    Projectile(int x, int y, const char* texturePath, int speed);

    void update() override;
};  