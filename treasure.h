#ifndef __TREASURE_H__
#define __TREASURE_H__

#include "constants.h"
#include "object.h"

class Object;

class Treasure : public Object
{
private:
    int mode;
public:
    Treasure(int _speed_x,
           int _speed_y,
           SDL_Rect rect,
           SDL_Surface *_surface,
           int _mode);
    Treasure(const Treasure &treasure);
    virtual ~Treasure();
    int getMode() const;
    void setMode(int _mode);
    void updatePos();
    int count;
};

Treasure::Treasure(int _speed_x, 
                   int _speed_y, 
                   SDL_Rect _rect, 
                   SDL_Surface *_surface,
                   int _mode)
:Object(_speed_x, _speed_y, _rect, _surface)
{
    mode = _mode;
    count = 0;
}

Treasure::Treasure(const Treasure &treasure)
:Object(treasure)
{      
    mode = treasure.getMode();
}

Treasure::~Treasure()
{
    // do something?
}

int Treasure::getMode() const
{
    return mode;
}

void Treasure::setMode(int _mode)
{
    mode = _mode;
}

void Treasure::updatePos()
{
    count++;
    if (count < 2) return;
    else{
      setPosX(getPosX()+(rand()%2 == 0 ? 1 : -1)*rand()%15);
      setPosY(getPosY()+(rand()%2 == 0 ? 1 : -1)*rand()%15 + 6);
      count = 0;
    }
}

#endif
