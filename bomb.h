#ifndef __BOMB_H__
#define __BOMB_H__

#include "constants.h"
#include "object.h"
#include <iostream>

using namespace std;

//----------------copy to constants.h
#define BOMB_MODEL_0 0 
#define BOMB_MODEL_1 1

#define BOMB_DAMAGE_0 20
#define BOMB_DAMAGE_1 30

class Object;

class Bomb : public Object
{
private:
    int time;
    vector<SDL_Surface *> *explosion;
    int count;
    int distance;
public:
    Bomb(int _speed_x,
         int _speed_y,
         SDL_Rect rect,
         SDL_Surface *_surface,
	 vector<SDL_Surface *> *_explosion,
         int _time);
    Bomb(const Bomb& bomb);
    virtual ~Bomb();
    int getTime() const;
    void setTime(int _time);
    vector<SDL_Surface *> * getExplosion() const;
    SDL_Surface * getSurface();
    void updatePos();
};

Bomb::Bomb(int _speed_x, 
           int _speed_y, 
           SDL_Rect _rect, 
           SDL_Surface *_surface,
	   vector<SDL_Surface *> *_explosion,
           int _time)
:Object(_speed_x, _speed_y, _rect, _surface)
{
    time = _time;
    explosion = _explosion;
    count = 0;
    distance = 0;
}

Bomb::Bomb(const Bomb &bomb)
:Object(bomb)
{    
    time = bomb.getTime();
    explosion = bomb.getExplosion();
    distance = 0;
    count = 0;
}

Bomb::~Bomb()
{
    // do something?
}

int Bomb::getTime() const
{
    return time;
}

void Bomb::setTime(int _time)
{
    time = _time;
}

vector<SDL_Surface *> * Bomb::getExplosion() const
{
    return explosion;
}

SDL_Surface * Bomb::getSurface()
{
    if(isAlive())
    {
        return::Object::getSurface();
    }
    else
    {
        if(count < explosion->size())
	      {
	         return (*explosion)[count];
	         ++count;
	      }
	      else
	      {
	         hide();
	    return NULL;
	}
    }
}

void Bomb::updatePos()
{
    setPosY(getPosY()-4);
    distance += 4;
    if (distance > 100)
      suiside();
}
#endif
