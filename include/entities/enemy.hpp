#include <entities/entity.hpp>

class Enemy : public Entity {
public:
    
    Enemy(int x, int y);
    ~Enemy();


    void shoot();
    void move();
};