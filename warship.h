#ifndef __WARSHIP_H__
#define __WARSHIP_H__
#include <unordered_set>
#include <iostream>
#include "bomb.h"
#include "bullet.h"
#include "aircraft.h"

using namespace std;

extern unordered_set<Bullet *> enemy_bullets;
extern unordered_set<Bullet *> friend_bullets; 
extern unordered_set<Bomb *> friend_bombs;

class Aircraft;
class Bullet;
class Bomb;

class Warship : public Aircraft
{
private:
    int serial;
    Bullet *bullet;
    Bomb *bomb;
    int num_bomb;
public:
    Warship(int _speed_x,
            int _speed_y,
            SDL_Rect rect,
            SDL_Surface *_surface,
            int _health_curr,
            int _health_max,
	    vector<SDL_Surface *> *_explosion,
            Bullet *_bullet,
            Bomb *_bomb,
            int _serial,
            int _num_bomb);
    Warship(const Warship& warship);
    ~Warship();
    Bullet *getBullet() const;
    void setBullet(Bullet *_bulet);
    Bomb *getBomb() const;    
    void setBomb(Bomb *_bomb);
    void launch();
    void fire();
    void updateBullet(Bullet *_bullet);
    virtual void updatePos();
    int getSerial() const;
    int getNumBomb() const;
    void incNumBomb();
    void decNumBomb();
};

Warship::Warship(int _speed_x, 
                 int _speed_y, 
                 SDL_Rect _rect, 
                 SDL_Surface *_surface,
                 int _health_curr, 
                 int _health_max,
		 vector<SDL_Surface *> *_explosion,
                 Bullet *_bullet,
                 Bomb *_bomb,
                 int _serial,
                 int _num_bomb)
:Aircraft(_speed_x, _speed_y, _rect, _surface, _health_curr, _health_max, _explosion)
{
    bullet = _bullet;
    bomb = _bomb;
    serial = _serial;
    num_bomb = _num_bomb;
}

Warship::Warship(const Warship& warship)
:Aircraft(warship)
{    
    bullet = warship.getBullet();
    bomb = warship.getBomb();
    serial = 1+warship.getSerial();
    num_bomb = warship.getNumBomb();
}


Warship::~Warship()
{
    // do sth
}

Bullet * Warship::getBullet() const
{
    return bullet;
}

void Warship::setBullet(Bullet *_bullet)
{
    bullet = _bullet;
}
    
Bomb * Warship::getBomb() const
{
    return bomb;
}

void Warship::setBomb(Bomb *_bomb)
{
    bomb = _bomb;
}

void Warship::launch()
{
    if(num_bomb <= 0)
        return;
    Bomb *new_bomb = new Bomb(*bomb);
    new_bomb->setPosX(this->getPosX() + 35);
    new_bomb->setPosY(this->getPosY() - 10);
    new_bomb->show();
    friend_bombs.insert(new_bomb);
}

void Warship::fire()
{
    Bullet *new_bullet = new Bullet(*bullet);
    new_bullet->setPosX(this->getPosX() + 38);
    new_bullet->setPosY(this->getPosY() - 10);
    new_bullet->show();
    friend_bullets.insert(new_bullet);
}

void Warship::updateBullet(Bullet *_bullet)
{
    bullet = _bullet;
}

void Warship::updatePos()
{
    switch(serial)
    {
    case 0:
        if (keystates[SDLK_LEFT]){
            setPosX(getPosX()-getSpeedX()); 
        }
        if (keystates[SDLK_RIGHT]){
            setPosX(getPosX()+getSpeedX()); 
        }
        if (keystates[SDLK_DOWN]){
            setPosY(getPosY()+getSpeedY());  
        }
        if (keystates[SDLK_UP]){
            setPosY(getPosY()-getSpeedY()); 
        }
        break;
    case 1:
        if (keystates[SDLK_a]){
            setPosX(getPosX()-getSpeedX()); 
        }
        if (keystates[SDLK_d]){
            setPosX(getPosX()+getSpeedX()); 
        }
        if (keystates[SDLK_s]){
            setPosY(getPosY()+getSpeedY());  
        }
        if (keystates[SDLK_w]){
            setPosY(getPosY()-getSpeedY()); 
        }
        break;
    default:
        cout<<"Warship key error"<<endl;
    }
}

int Warship::getSerial() const
{
    return serial;
}

int Warship::getNumBomb() const
{
    return num_bomb;
}

void  Warship::incNumBomb()
{
    ++num_bomb;
}

void  Warship::decNumBomb()
{
    --num_bomb;
    num_bomb = num_bomb < 0 ? 0 : num_bomb;
}
#endif
