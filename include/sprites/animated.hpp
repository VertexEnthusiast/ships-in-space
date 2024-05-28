#pragma once

#include <SFML/Graphics.hpp>
#include <entities/entity.hpp>

class Animated : public Entity {
public:
    std::vector<sf::IntRect> frames;
    int currentFrame;
    int framesPerUpdate;
    int frameTime;

    Animated(int x, int y, int numFrames, int framesPerUpdate, int frameTime);

    void animate();
};