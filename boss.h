#ifndef __BOSS_H__
#define __BOSS_H__
#include <unordered_set>
#include "bullet.h"
#include "aircraft.h"
#include <vector>

using namespace std;
extern unordered_set<Bullet *> enemy_bullets;
extern unordered_set<Bullet *> friend_bullets; 

class Aircraft;
class Bullet;

class Boss : public Aircraft
{
private:
    Bullet *bullet;
    int fire_count;
    int fire_mod;
    //int bomb_count;
    //int bomb_mod;
public:
    Boss(int _speed_x,
         int _speed_y,
         SDL_Rect _rect,
         SDL_Surface *_surface,
         int _health_curr,
         int _health_max,
	 vector<SDL_Surface *> *_explosion,
         Bullet *_bullet,
         int _fire_mod);
    Boss(const Boss &boss);
    virtual ~Boss();
    Bullet *getBullet() const;
    int getFireMod() const;
    void fire();    
    virtual void updatePos(int mywarship_x);
    void reborn();
    /* int getBombMod() const; */
    /* void launch(); */
};

Boss::Boss(int _speed_x, 
           int _speed_y, 
           SDL_Rect _rect, 
           SDL_Surface *_surface,
           int _health_curr, 
           int _health_max, 
	   vector<SDL_Surface * > *_explosion,
           Bullet *_bullet,
           int _fire_mod)
:Aircraft(_speed_x, _speed_y, _rect, _surface, _health_curr, _health_max, _explosion)
{    
    bullet = _bullet;
    fire_count = 0;
    fire_mod = _fire_mod;
    /* bomb_count = _bomb_count; */
    /* bomb_mod = _bomb_count; */
}

Boss::Boss(const Boss &boss)
:Aircraft(boss)
{
    bullet = boss.getBullet();
    fire_count = 0;
    fire_mod = boss.getFireMod();
    /* bomb_count = 0; */
    /* bomb_mod = boss.getBombMod(); */
}

Boss::~Boss()
{
    // do sth
}

Bullet* Boss::getBullet() const
{
    return bullet;
}

int Boss::getFireMod() const
{
    return fire_mod;
}

void Boss::fire()
{
    //if(fire_count < fire_mod)
    //{
    //    fire_count++;
    //    return;
    //}
    Bullet *new_bullet = new Bullet(*bullet);
    new_bullet->setPosX(getPosX() + 10);
    new_bullet->setSpeedX(-10);
    new_bullet->setPosY(getPosY() + 60);
    new_bullet->resurrect();
    new_bullet->show();
    enemy_bullets.insert(new_bullet);

    new_bullet = NULL;
    new_bullet = new Bullet(*bullet);
    new_bullet->setPosX(getPosX() + 10);
    new_bullet->setSpeedX(-4);
    new_bullet->setPosY(getPosY() + 60);
    new_bullet->resurrect();
    new_bullet->show();
    enemy_bullets.insert(new_bullet);

    new_bullet = NULL;
    new_bullet = new Bullet(*bullet);
    new_bullet->setSpeedX(10);
    new_bullet->setPosX(getPosX() + 140);
    new_bullet->setPosY(getPosY() + 60);
    new_bullet->resurrect();
    new_bullet->show();
    enemy_bullets.insert(new_bullet);

    new_bullet = NULL;
    new_bullet = new Bullet(*bullet);
    new_bullet->setSpeedX(4);
    new_bullet->setPosX(getPosX() + 140);
    new_bullet->setPosY(getPosY() + 60);
    new_bullet->resurrect();
    new_bullet->show();
    enemy_bullets.insert(new_bullet);

    new_bullet = NULL;
    new_bullet = new Bullet(*bullet);
    new_bullet->setSpeedX(0);
    new_bullet->setPosX(getPosX() + 75);
    new_bullet->setPosY(getPosY() + 100);
    new_bullet->resurrect();
    new_bullet->show();
    enemy_bullets.insert(new_bullet);
}
void Boss::updatePos(int mywarship_x)
{
    if (getPosY() < 160){
        setPosY(getPosY() + 2);
    }
    else{
        if (getPosX() < mywarship_x + 4 && getPosX() > mywarship_x - 4) return;
        else if (getPosX() < mywarship_x)
            setPosX(getPosX() + 4);
        else setPosX(getPosX() - 4);
    }
}

void Boss::reborn(){
    
}
/* int Boss::getBombMod() */
/* { */
/*     return bomb_mod; */
/* } */

#endif
