#include <entities/spaceship.hpp>
#include <iostream>

Spaceship::Spaceship(int x, int y, const char* texturePath)
: Entity(x, y, texturePath), cooldown(0)
{
    this->texture.loadFromFile("assets/Spaceship.png");
    this->sprite.setTexture(texture);
    this->sprite.scale(Entity::spriteScale);
}

void Spaceship::shoot()
{
    std::cout << "Add shooting implementation here\n";
    int speed = 5;

    if (cooldown > 0)
    {
        puts("Not ready yet");
        return;
    }

    // Create a new Projectile object using std::make_unique
    auto projectile = std::make_unique<Projectile>(this->x, this->y, "assets/super_projectile_sheet.png", speed);
    fired.push_back(std::move(projectile)); // Move the unique_ptr into the vector
    cooldown = maxCooldown;
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
    sprite.setPosition(sf::Vector2f(x, y));
}