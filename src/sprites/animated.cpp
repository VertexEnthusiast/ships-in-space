#include <sprites/animated.hpp>

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
    // this->y -= speed * 1;
    // sprite.setPosition(sf::Vector2f(this->x, this->y));
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
        frames.push_back(sf::IntRect(i * frameInfo->xdim, 0, frameInfo->xdim, frameInfo->ydim));
    }
    this->currentFrame = 0;
    this->frameTime = 0;
    this->sprite.setTextureRect(frames[0]);
}