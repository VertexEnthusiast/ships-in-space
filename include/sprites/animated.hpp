#pragma once

#include <SFML/Graphics.hpp>
#include <entities/entity.hpp>

struct FrameData{
    int numFrames;
    int framesPerUpdate;
    int xdim;
    int ydim;
};
class Animated : public Entity {
public:
    std::vector<sf::IntRect> frames;
    int currentFrame;
    int framesPerUpdate;
    int frameTime;
    int numFrames;

    Animated(int x, int y, const char* texturePath, struct FrameData* frameInfo);

    void animate();
    void updateAnimation(const char* texturePath, struct FrameData* frameInfo);
};