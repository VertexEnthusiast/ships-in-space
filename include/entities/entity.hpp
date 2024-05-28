#pragma once
#include <SFML/Graphics.hpp>

class Entity {
    public:
        int x;
        int y;
        sf::Texture texture;
        sf::Sprite sprite;
        static const sf::Vector2f spriteScale;

        Entity(int x, int y);
        ~Entity();

        virtual void update();
};

// Initialize the static const member