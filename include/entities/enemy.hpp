#pragma once
#include <sprites/animated.hpp>

class Enemy : public Animated {
public:
    int health;
    int speed;
    int secondsUntilMove;
    int framesUntilDeath = -1;
    bool killed = false;
    bool exploded = false;

    Enemy(int x, int y, const char* texturePath, struct FrameData* frameInfo, int health, int speed);
    ~Enemy();
    


    void shoot();
    void move();
    void deadUpdate();

    void update();
};