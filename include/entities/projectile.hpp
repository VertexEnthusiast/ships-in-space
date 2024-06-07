#pragma once
#include <entities/entity.hpp>
#include <sprites/animated.hpp>

class Projectile : public Animated
{
public:
    int speed;
    sf::IntRect frames[14];
    int currentFrame;
    const int frameLength = 4;
    int frameTime;

    Projectile(int x, int y, const char *texturePath, struct FrameData *frameInfo, int speed);
    ~Projectile();

    void update() override;
};