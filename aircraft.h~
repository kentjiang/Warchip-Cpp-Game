#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "object.h"
#include <vector>
#include <iostream>

using namespace std;

class Aircraft : public Object
{
private:
    int health_curr;
    int health_max;
    vector<SDL_Surface *> *explosion;
    int count;
public:
    Aircraft(int _speed_x,
             int _speed_y,
             SDL_Rect _rect,
             SDL_Surface *_surface,
             int _health_curr,
             int _health_max,
	     vector<SDL_Surface *> *_explosion);
    Aircraft(const Aircraft &_aircraft);
    virtual ~Aircraft();
    void incHealth(int num_health);
    void decHealth(int num_health);
    int getHealth() const;
    int getMaxHealth() const;
    vector<SDL_Surface *> * getExplosion() const;
    virtual SDL_Surface * getSurface();
    void resurrect();
};

Aircraft::Aircraft(int _speed_x, 
                   int _speed_y, 
                   SDL_Rect _rect, 
                   SDL_Surface *_surface, 
                   int _health_curr, 
                   int _health_max,
		   vector<SDL_Surface *> *_explosion)
:Object(_speed_x, _speed_y, _rect, _surface)
{
    health_curr = _health_curr;
    health_max = _health_max;
    explosion = _explosion;
    count = 0;
}

Aircraft::Aircraft(const Aircraft& _aircraft)
:Object(_aircraft)
{
    health_curr = _aircraft.getHealth();
    health_max = _aircraft.getMaxHealth();
    explosion = _aircraft.getExplosion();
    count = 0;
}

Aircraft::~Aircraft()
{
    // ææ...
}

void Aircraft::incHealth(int num_health)
{
    if(!isAlive())
        return;
    health_curr += num_health;
    health_curr = health_curr < health_max ? health_curr : health_max;
}

void Aircraft::decHealth(int num_health)
{
    if(!isAlive())
        return;
    health_curr -= num_health;
    if(health_curr <= 0)
    {
        suiside();
	cout<<"$$$$"<<isVisible()<<endl;
    }
}

int Aircraft::getHealth() const
{
    return health_curr;
}

int Aircraft::getMaxHealth() const
{
    return health_max;
}

vector<SDL_Surface *> * Aircraft::getExplosion() const
{
    return explosion;
}

SDL_Surface * Aircraft::getSurface()
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
	    cout<<"@@@@@@@@@@"<<endl;
	}
	else
	{
	    hide();
	    cout<<"#########"<<endl;
	    return NULL;
	}
    }
}

void Aircraft::resurrect()
{
    Object::resurrect();
    health_curr = health_max;
    count = 0;
}

#endif
