#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "constants.h"

class Object
{
private:
    int speed_x;
    int speed_y;
    int move_mod;
    SDL_Rect rect;
    SDL_Surface *surface;
    bool alive; // should delete this object or not
    bool visible;    
public:
    Object(int _speed_x,
           int _speed_y,
           SDL_Rect _rect,
           SDL_Surface *_surface);
    Object(const Object &obj);
    virtual ~Object();
    void setSpeedX(int _speed_x);
    void setSpeedY(int _speed_y);
    void setPosX(int _pos_x);
    void setPosY(int _pos_y);
    int getSpeedX() const;
    int getSpeedY() const;
    int getPosX() const;
    int getPosY() const;
    int getWidth() const;
    int getHeight() const;
    SDL_Rect getRect() const;
    virtual SDL_Surface *getSurface() const;
    void setSurface(SDL_Surface * _surface);
    virtual void setMovemod(int _move_mod);
    virtual void updatePos();
    void resurrect();
    void suiside();
    bool isAlive() const;
    void show();
    void hide();
    bool isVisible();
  
};

Object::Object(int _speed_x, 
               int _speed_y, 
               SDL_Rect _rect, 
               SDL_Surface *_surface)
{
    speed_x = _speed_x;
    speed_y = _speed_y;
    rect = _rect;
    surface = _surface;
    alive = true;
    visible = false;
}

Object::Object(const Object &obj)
{
    speed_x = obj.getSpeedX();
    speed_y = obj.getSpeedY();
    rect = obj.getRect();
    surface = obj.getSurface();
    alive = true;
    visible = false;
}

Object::~Object()
{
    // hehehe?
}

void Object::setSpeedX(int _speed_x)
{
    speed_x = _speed_x;
}

void Object::setSpeedY(int _speed_y)
{
    speed_y = _speed_y;
}

void Object::setPosX(int _pos_x)
{
    rect.x = _pos_x;
    if(rect.x < -rect.w/2)
        rect.x = -rect.w/2;
    if(rect.x > WIDTH_SCREEN-rect.w/2)
        rect.x = WIDTH_SCREEN-rect.w/2;
}

void Object::setPosY(int _pos_y)
{
    rect.y = _pos_y;
    // if(rect.y < 0)
    //     rect.y = 0;
    if(rect.y > HEIGHT_SCREEN)
        rect.y = HEIGHT_SCREEN;
}

int Object::getSpeedX() const
{
    return speed_x;
}

int Object::getSpeedY() const
{
    return speed_y;
}

int Object::getPosX() const
{
    return rect.x;
}

int Object::getPosY() const
{
    return rect.y;
}

int Object::getWidth() const
{
    return rect.w;
}

int Object::getHeight() const
{
    return rect.h;
}

SDL_Rect Object::getRect() const
{
    return rect;
}

SDL_Surface * Object::getSurface() const
{
    return surface;
}

void Object::setSurface(SDL_Surface * _surface)
{
    surface = _surface;
}

void Object::setMovemod(int _move_mod)
{
    move_mod = _move_mod;
}

void Object::updatePos()
{
    if(!isAlive())
        return;
    if(!isVisible())
       return;
    
    rect.x += speed_x;
    rect.y += speed_y;


    if(rect.x+rect.w < 0)
        alive = false;
    else if(rect.x >= WIDTH_SCREEN)
        alive = false;
    
    if(rect.y+rect.h < 0)
        alive = false;
    else if(rect.y >= HEIGHT_SCREEN)
        alive = false;

}

void Object::resurrect()
{
    alive = true;
}

void Object::suiside()
{
    alive = false;
}

bool Object::isAlive() const
{
    return alive;
}

void Object::show()
{
    visible = true;
}

void Object::hide()
{
    visible = false;
}

bool Object::isVisible()
{
    return visible;
}

#endif
