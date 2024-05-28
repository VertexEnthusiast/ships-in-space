#include <entities/entity.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Entity::Entity(int x, int y){
//     this->x = x;
//     this->y = y;
// }
Entity::Entity(int x, int y) : x(x), y(y) {
    std::cout << "Entity constructed at (" << x << ", " << y << ")\n";
}

Entity::~Entity(){
    std::cout << "Called destructor on entity";
}

void Entity::update(){
    sprite.setPosition(sf::Vector2f(x, y));
}

const sf::Vector2f Entity::spriteScale(6.0f, 6.0f);