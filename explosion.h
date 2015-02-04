#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__
#include <vector>

using namespace std;

class Explosion
{
private:
    SDL_Rect rect;
    vector<SDL_Surface *> surface;
    int cnt;   
public:
    Explosion(SDL_Rect _rect,
              vector<SDL_Surface *> _surface);
    Explosion(const Explosion &exp);
    virtual ~Explosion();
    SDL_Rect getRect() const;    
    SDL_Surface *getSurface();
    vector<SDL_Surface *> getAllSurface() const;
    void setPosX(int posx);
    void setPosY(int posy);
    bool isVisible();  
};


Explosion::Explosion(SDL_Rect _rect,
                     vector<SDL_Surface *> _surface)
{
    rect  = _rect;
    surface = _surface;
    cnt = 0;
}

Explosion::Explosion(const Explosion &exp)
{
    rect = exp.getRect();
    surface = exp.getAllSurface();
    cnt = 0;
}

Explosion::~Explosion()
{
    
}

SDL_Rect Explosion::getRect() const
{
    return rect;
}

vector<SDL_Surface *> Explosion::getAllSurface() const
{
    return surface;
}

SDL_Surface* Explosion::getSurface()
{
    ++cnt;
    cnt = cnt < surface.size() ? cnt : surface.size();
    return surface[cnt-1];
}

void Explosion::setPosX(int posx)
{
    rect.x = posx;
}

void Explosion::setPosY(int posy)
{
    rect.y = posy;
}

bool Explosion::isVisible()
{
    return cnt < surface.size();
}

#endif
