#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Entity
{
public:
    int x;
    int y;
    sf::Texture texture;
    sf::Sprite sprite;
    static const sf::Vector2f spriteScale;

    Entity(int x, int y, const char *texturePath);
    virtual ~Entity();

    virtual void update();

    static bool projectileCollides(Entity *a, Entity *b);
};

// Initialize the static const member