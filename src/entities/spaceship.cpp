#include <SFML/Audio.hpp>
#include <entities/spaceship.hpp>
#include <sprites/animated.hpp>
#include <iostream>

Spaceship::Spaceship(int x, int y, const char *texturePath, struct FrameData *frameInfo)
    : Animated(x, y, texturePath, frameInfo), cooldown(0)
{   
    if (!projSoundBuffer.loadFromFile("assets/lasergun_v1.wav"))
        puts("Error loading laser sound");
    
    projectileSound.setBuffer(projSoundBuffer);

}

void Spaceship::shoot()
{
    std::cout << "Add shooting implementation here\n";
    int speed = 8;

    if (cooldown > 0)
    {
        puts("Not ready yet");
        return;
    }

    // Create a new Projectile object using std::make_unique
    struct FrameData data = {
        .numFrames = 14,
        .framesPerUpdate = 5,
        .xdim = 32,
        .ydim = 32};
    auto projectile = std::make_unique<Projectile>(this->x, this->y, "assets/super_projectile_sheet.png", &data, speed);
    fired.push_back(std::move(projectile)); // Move the unique_ptr into the vector
    cooldown = maxCooldown;
    projectileSound.play();
}

Spaceship::~Spaceship()
{
    std::cout << "Deleted spaceship... Not really\n";
}

void Spaceship::move(int x, int y)
{
    int speed = 4;
    this->x += x * speed;
    this->y += y;
}

void Spaceship::update()
{
    cooldown--;
    animate();
    sprite.setPosition(sf::Vector2f(x, y));
}