#include <entities/projectile.hpp>

Projectile::Projectile(int x, int y, const char *texturePath, struct FrameData *frameInfo, int speed)
    : Animated(x, y, texturePath, frameInfo), speed(speed)
{
}

Projectile::~Projectile()
{
}

void Projectile::update()
{
    animate();
    this->y -= speed * 1;
    sprite.setPosition(sf::Vector2f(this->x, this->y));
}
