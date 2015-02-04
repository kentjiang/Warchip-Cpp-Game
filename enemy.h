#ifndef __ENEMY_H__
#define __ENEMY_H__
#include <unordered_set>
#include "bullet.h"
#include "aircraft.h"
using namespace std;
extern unordered_set<Bullet *> enemy_bullets;
extern unordered_set<Bullet *> friend_bullets; 

class Aircraft;
class Bullet;

class Enemy : public Aircraft
{
private:
    Bullet *bullet;
    int fire_count;
    int fire_mod;
public:
    Enemy(int _speed_x,
          int _speed_y,
          SDL_Rect _rect,
          SDL_Surface *_surface,
          int _health_curr,
          int _health_max,
	  vector<SDL_Surface *> *_explosion,
          Bullet *_bullet,
          int _fire_mod);

    Enemy(const Enemy &enemy);
    virtual ~Enemy();
    Bullet *getBullet() const;
    int getFireMod() const;
    void fire(int x, int y);
};

Enemy::Enemy(int _speed_x, 
             int _speed_y, 
             SDL_Rect _rect, 
             SDL_Surface *_surface,
             int _health_curr, 
             int _health_max, 
	     vector<SDL_Surface *> *_explosion,
             Bullet *_bullet, 
             int _fire_mod) // this is the time lapse for each bullet
:Aircraft(_speed_x, _speed_y, _rect, _surface, _health_curr, _health_max, _explosion)
{    
    bullet = _bullet;
    fire_count = 0;
    fire_mod = _fire_mod;
}

Enemy::Enemy(const Enemy &enemy)
:Aircraft(enemy)
{
    bullet = enemy.getBullet();
    fire_count = 0;
    fire_mod = enemy.getFireMod();
}

Enemy::~Enemy()
{
    // do sth
}

Bullet* Enemy::getBullet() const
{
    return bullet;
}

int Enemy::getFireMod() const
{
    return fire_mod;
}

void Enemy::fire(int x, int y)
{
    if(fire_count < fire_mod)
    {
        fire_count++;
        return;
    }
    //Mix_PlayChannel( -1, shoot, 0 );
    fire_count = 0;
    Bullet *new_bullet = new Bullet(*bullet);
    new_bullet->setPosX(getPosX() + x);
    new_bullet->setPosY(getPosY() + y);
    new_bullet->resurrect();
    new_bullet->show();
    enemy_bullets.insert(new_bullet);
}

#endif
