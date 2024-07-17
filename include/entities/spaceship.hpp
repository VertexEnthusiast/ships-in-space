#pragma once
#include <SFML/Audio.hpp>
#include <entities/entity.hpp>
#include <entities/projectile.hpp>

class Spaceship : public Animated
{
public:
    std::vector<std::unique_ptr<Projectile>> fired;
    sf::SoundBuffer projSoundBuffer;
    sf::Sound projectileSound;
    std::unique_ptr<Animated> laser;
    bool laserOn = false;
    const int maxCooldown = 40;
    int cooldown;
    int health = 4;
    const int maxHealth = 4;

    Spaceship(int x, int y, const char *texturePath, struct FrameData *frameInfo);
    ~Spaceship();

    void shoot();
    void activateLaser();
    void move(int x, int y);
    void update() override;

    enum Direction
    {
        LEFT,
        DOWN,
        UP,
        RIGHT
    };
};