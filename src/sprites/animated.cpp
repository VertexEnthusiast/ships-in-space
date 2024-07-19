#include <sprites/animated.hpp>
#include <iostream>

Animated::Animated(int x, int y, const char *texturePath, struct FrameData *frameInfo)
    : Entity(x, y, texturePath), currentFrame(0),
      framesPerUpdate(frameInfo->framesPerUpdate), frameTime(0),
      numFrames(frameInfo->numFrames)
{
    for (int i = 0; i < frameInfo->numFrames; i++)
    {
        frames.push_back(sf::IntRect(i * frameInfo->xdim, 0, frameInfo->xdim, frameInfo->ydim));
    }

    this->sprite.setTextureRect(frames[0]);
}

void Animated::animate()
{
    frameTime++;
    if (frameTime % framesPerUpdate == 0)
    {
        currentFrame = (currentFrame + 1) % numFrames;
        frameTime = 0;
    }
    this->sprite.setTextureRect(frames[currentFrame]);
    if (y < 0)
    {
        // puts("I'm offscreen");
        return;
    }
}

void Animated::updateAnimation(const char *texturePath, struct FrameData *frameInfo)
{
    this->texture.loadFromFile(texturePath);
    this->sprite.setTexture(this->texture);
    this->framesPerUpdate = frameInfo->framesPerUpdate;
    this->numFrames = frameInfo->numFrames;
    this->frames.clear();
    for (int i = 0; i < frameInfo->numFrames; i++)
    {
        int frameHeight = frameInfo->ydim * fraction;
        frames.push_back(sf::IntRect(i * frameInfo->xdim, 0, frameInfo->xdim, frameHeight));
    }
    this->currentFrame = 0;
    this->frameTime = 0;
    this->sprite.setTextureRect(frames[0]);
}

void Animated::scaleRects(int xdim, int ydim, float fraction)
{
    // Fraction is how much of the sprite should be visible, starting from the bottom of the sprite
    if (this->fraction != fraction)
    {
        this->fraction = fraction;
        this->frames.clear();
        std::cout << "Current fraction is " << fraction << std::endl;
        int frameHeight = ydim * fraction;
        int lostHeight = ydim * (1 - fraction);

        for (int i = 0; i < numFrames; i++)
        {
            frames.push_back(sf::IntRect(i * xdim, lostHeight, xdim, frameHeight));
        }
        // Shift the sprite down by the deleted difference
        this->y = Entity::spriteScale.y * lostHeight;
        std::cout << "New y is : " << this->y << std::endl;
        sprite.setPosition(sf::Vector2f(this->x, this->y));
    }
}