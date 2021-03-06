#ifndef __BULLET_H__
#define __BULLET_H__

#include "constants.h"
#include "object.h"

//----------------copy to constants.h
#define BULLET_MODEL_0 0 
#define BULLET_MODEL_1 1
#define BULLET_MODEL_2 2
#define BULLET_MODEL_3 3
#define BULLET_MODEL_4 4
#define BULLET_MODEL_5 5

#define BULLET_DAMAGE_0 0
#define BULLET_DAMAGE_1 1
#define BULLET_DAMAGE_2 2
#define BULLET_DAMAGE_3 3
#define BULLET_DAMAGE_4 4
#define BULLET_DAMAGE_5 5

class Object;

class Bullet : public Object
{
private:
    int damage;
public:
    Bullet(int _speed_x,
           int _speed_y,
           SDL_Rect rect,
           SDL_Surface *_surface,
           int _damage);
    Bullet(const Bullet &bullet);
    virtual ~Bullet();
    int getDamage() const;
    void setDamage(int bullet_model);
};

Bullet::Bullet(int _speed_x, 
               int _speed_y, 
               SDL_Rect _rect, 
               SDL_Surface *_surface,
               int _damage)
:Object(_speed_x, _speed_y, _rect, _surface)
{
    damage = _damage;
}

Bullet::Bullet(const Bullet &bullet)
:Object(bullet)
{      
    damage = bullet.getDamage();
}

Bullet::~Bullet()
{
    // do something?
}

int Bullet::getDamage() const
{
    return damage;
}

void Bullet::setDamage(int bullet_model)
{
    switch(bullet_model)
    {
    case BULLET_MODEL_0:
        damage = BULLET_DAMAGE_0;
        break;
    case BULLET_MODEL_1:
        damage = BULLET_DAMAGE_1;        
        break;
    case BULLET_MODEL_2:
        damage = BULLET_DAMAGE_2;
        break;
    case BULLET_MODEL_3:
        damage = BULLET_DAMAGE_3;
        break;
    case BULLET_MODEL_4:
        damage = BULLET_DAMAGE_4;
        break;
    case BULLET_MODEL_5:
        damage = BULLET_DAMAGE_5;
        break;
    default:
        damage = 0;
    }
}

#endif
