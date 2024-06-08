#include <entities/entity.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

Entity::Entity(int x, int y, const char *texturePath) : x(x), y(y)
{
    this->texture.loadFromFile(texturePath);
    this->sprite.scale(Entity::spriteScale);
    this->sprite.setTexture(this->texture);
    sprite.setPosition(sf::Vector2f(this->x, this->y));
    std::cout << "Entity constructed at (" << x << ", " << y << ")\n";
}

Entity::~Entity()
{
    std::cout << "Called destructor on entity\n";
}

void Entity::update()
{
    sprite.setPosition(sf::Vector2f(x, y));
}

bool Entity::projectileCollides(Entity *projectile, Entity *entity)
{
    sf::Sprite &sprite1 = projectile->sprite;
    sf::Sprite &sprite2 = entity->sprite;
    // Get the position and size of the first sprite
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();

    // Define the size of the inner 4x4 square
    sf::Vector2f innerSquareSize(4.f, 4.f);

    // Calculate the top-left position of the 4x4 square centered in the 32x32 sprite
    sf::Vector2f innerSquarePosition(
        bounds1.left + (bounds1.width / 2.f) - (innerSquareSize.x / 2.f),
        bounds1.top + (bounds1.height / 2.f) - (innerSquareSize.y / 2.f));

    // Create a FloatRect representing the 4x4 square
    sf::FloatRect innerSquare(innerSquarePosition, innerSquareSize);

    // Get the bounds of the second sprite
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();

    // Check for intersection between the 4x4 square and the 32x32 sprite
    if (innerSquare.intersects(bounds2)){
        std::cout << "Detected collision\n";
        std::cout << "Bounds1: " << bounds1.left << ", " << bounds1.top << ", " << bounds1.width << ", " << bounds1.height << std::endl;
        std::cout << "InnerSquarePosition: " << innerSquarePosition.x << ", " << innerSquarePosition.y << std::endl;
        std::cout << "InnerSquare: " << innerSquare.left << ", " << innerSquare.top << ", " << innerSquare.width << ", " << innerSquare.height << std::endl;
        std::cout << "Bounds2: " << bounds2.left << ", " << bounds2.top << ", " << bounds2.width << ", " << bounds2.height << std::endl;

    }
    return innerSquare.intersects(bounds2);
}

const sf::Vector2f Entity::spriteScale(3.0f, 3.0f);
