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

    struct FrameData data = {
        .numFrames = 5,
        .framesPerUpdate = 5,
        .xdim = 32,
        .ydim = 96};

    laser = std::make_unique<Animated>(this->x, this->y, "assets/laser_animated.png", &data);
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

void Spaceship::activateLaser()
{
    if (!laserOn)
    {
        laserOn = true;
    }
}

Spaceship::~Spaceship()
{
    std::cout << "Deleted spaceship... Not really\n";
}

void Spaceship::move(int x, int y)
{
    int leftbound, rightbound, topbound, bottombound;
    leftbound = 0;
    rightbound = 800 - Entity::spriteScale.x * 32;
    bottombound = 600 - Entity::spriteScale.y * 32;
    topbound = 400;

    int speed = 4;
    int newx = this->x + x * speed;
    int newy = this->y + y * speed;

    if ((newx < leftbound) || (newx > rightbound) || (newy < topbound) || (newy > bottombound))
    {
        return;
    }
    else
    {
        this->x = newx;
        this->y = newy;
    }
}

void Spaceship::update()
{
    cooldown--;
    animate();
    if (laserOn)
    {
        laser->sprite.setPosition(sf::Vector2f(x, y - 64 * Entity::spriteScale.y));
        laser->animate();
    }

    // Do flashing animation when hit
    if (flashing > 0)
    {
        if (flashing == 12 || flashing == 2)
        {
            sf::Color color = sprite.getColor();
            color.a = 255;
            sprite.setColor(color);
        }
        if (flashing == 8)
        {
            sf::Color color = sprite.getColor();
            color.a = 100;
            sprite.setColor(color);
        }

        flashing--;
    }

    sprite.setPosition(sf::Vector2f(x, y));
}

void Spaceship::damaged()
{
    flashing = 15;
    sf::Color color = sprite.getColor();
    color.a = 100;
    sprite.setColor(color);
}