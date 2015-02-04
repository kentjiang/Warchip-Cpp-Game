#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_rotozoom.h"
#include <string>

#include <unordered_set>
#include <unistd.h>

#include "boss.h"
#include "enemy.h"
#include "timer.h"
#include "warship.h"
#include "bomb.h"
#include "bullet.h"
#include "object.h"
#include "constants.h"
#include "explosion.h"

using namespace std; 

unordered_set<Bullet *> enemy_bullets;
unordered_set<Bullet *> friend_bullets; 
unordered_set<Bomb *> friend_bombs;

SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *my_bullet = NULL;
SDL_Surface *enemy_bullet = NULL;
SDL_Surface *warship = NULL;
SDL_Surface *enemy = NULL;
SDL_Surface *game_logo = NULL;
SDL_Surface *game_start_message = NULL;
SDL_Surface *score_surface = NULL;
SDL_Surface *end_die = NULL;
SDL_Surface *end_options1 = NULL;
SDL_Surface *your_score = NULL;
SDL_Surface *end_options2 = NULL;
SDL_Surface *enemy1 = NULL;
SDL_Surface *enemy_explode = NULL;


int score = 0;
char * score_temp;
SDL_Color color;
bool quit;
bool init();
void clean_up();
SDL_Surface *load_image(std::string filename);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
bool load_files();
bool to_game();
bool isCollision(const SDL_Rect &A, const SDL_Rect &B);

int main(int argv, char* argc[])
{
    if(!init())
        return -1;  

    bool loadfile = load_files();
    quit = true;

    bool flag = to_game();
    
    //===========================AFTER-GAME=================================
    while(quit){
        apply_surface(0, 0, background, screen);
        end_die = TTF_RenderText_Solid(font_80, "GAME OVER", color);
        apply_surface(50, 210, end_die, screen);
        end_options1 = TTF_RenderText_Solid(font_28, "Press A to Start Again", color);
        end_options2 = TTF_RenderText_Solid(font_28, "Press Q to Quit Game", color);
        apply_surface(140, 360, score_surface, screen);
        apply_surface(120, 400, end_options1, screen);
        apply_surface(120, 460, end_options2, screen);
        while(SDL_PollEvent( &event)){
            if (event.type == SDL_QUIT){
                quit = false;
            }
            else if (event.type = SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_q){
                    quit = false;
                }
                else if (event.key.keysym.sym == SDLK_a){
                    flag = to_game();
                }
            }
        }
        if (SDL_Flip(screen) == -1) return 0;
    }
    //========================================================================
    clean_up();
  
    return EXIT_SUCCESS;
}

bool to_game(){
    Timer fps;
    enemy_bullets.clear();
    friend_bullets.clear();
    friend_bombs.clear();
    SDL_Rect rect_bullet;
    rect_bullet.x = 0;
    rect_bullet.y = 0;
    rect_bullet.w = 13; 
    rect_bullet.h = 30;
 
    SDL_Rect rect_ship;
    rect_ship.x = 230;
    rect_ship.y = 600;
    rect_ship.w = 78; 
    rect_ship.h = 96;

    SDL_Rect rect_enemy;
    rect_enemy.x = 300; 
    rect_enemy.y = 0;
    rect_enemy.w = 65;
    rect_enemy.h = 45;

    SDL_Rect rect_enemy1;
    rect_enemy1.x = 200; 
    rect_enemy1.y = -100;
    rect_enemy1.w = 103;
    rect_enemy1.h = 131;

    SDL_Rect rect_boss;
    rect_boss.x = 200;
    rect_boss.y = -150;
    rect_boss.w = 100;
    rect_boss.h = 100;
    
    //Explosion *exp1 = new Explosion(???????);

    bool is_gaming = true;
    bool is_boss = false;
    //warship = zoomSurface(warship, 0.5, 0.5, 1);
 
    Bullet *bullet = new Bullet(0, -20, rect_bullet, NULL, 2);
    bullet->show();

    Bullet *bullet_e = new Bullet(0, 20, rect_bullet, enemy_bullet, 2);
    bullet_e->show();

    Bomb *bomb = new Bomb(0, 20, rect_bullet, NULL, 2);
    Warship *mywarship = new Warship(13, 13, rect_ship, NULL, 5, 5, bullet, bomb);

    Boss *myboss = new Boss(0, 5, rect_boss, enemy1, 2, 2, bullet_e, 30);
    
    Enemy *myenemy = new Enemy(0, 5, rect_enemy, enemy, 1, 1, bullet_e, 30);
    Enemy *myenemy1 = new Enemy(0, 5, rect_enemy1, enemy1, 2, 2, bullet_e, 30);

    unordered_set<Enemy *> enemy_set;

    for(int i = 0; i < NUMBER_ENEMY; i++)
    {
        Enemy *tmp = new Enemy(*myenemy);
        //tmp->setMovemode(rand()%2);
        tmp->setPosX(rand()%WIDTH_SCREEN);
        if(rand()%10 != 0)
            tmp->hide();
        tmp->suiside();
        enemy_set.insert(tmp);
    }
    
    for(int i = 0; i < 4; i++)
    {
        Enemy *tmp = new Enemy(*myenemy1);
        //tmp->setMovemode(rand()%2);
        tmp->setPosX(rand()%WIDTH_SCREEN);
        if(rand()%10 != 0)
            tmp->hide();
        tmp->suiside();
        enemy_set.insert(tmp);
    }


    SDL_EnableKeyRepeat(50,30);
    
    Uint32 enemy_clock = SDL_GetTicks();
    Uint32 my_bullet_clock = SDL_GetTicks();

    //=====================PRE-START================================
    bool st = true;
    while(st){
        apply_surface(0, 0, background, screen);
        game_logo = TTF_RenderText_Solid(font_80, "WARCHIP", color);
        apply_surface(105, 170, game_logo, screen);
        game_start_message = TTF_RenderText_Solid(font_28, "Press Any Key To Start", color);
        apply_surface(105, 300, game_start_message, screen);
        while(SDL_PollEvent( &event)){
            if (event.type == SDL_QUIT){
                st = false;
                is_gaming = false;
                quit = false;
            }
            else if (event.type == SDL_KEYDOWN){
                st = false;
            }
        }
        apply_surface(mywarship->getRect().x, mywarship->getRect().y, warship, screen);
        if (SDL_Flip(screen) == -1) return 0;
    }
    //=================================================================


    //====================START-GAME===================================
    while (is_gaming){
        //=====================EveryTime Init===============
        keystates = SDL_GetKeyState( NULL );
        fps.start();

        //======================score=======================
        int base = 10;
        for (int j = 13; j >= 7; j--){
           score_temp[j] = (score % (base * 10) - score % base) /base + '0';
           base = base * 10;
        }
        score_surface = TTF_RenderText_Solid(font_28, score_temp, color);

        //=======================Event=========================
         while(SDL_PollEvent( &event ))
        {
            
            if (event.type == SDL_QUIT){
                is_gaming = false;
                quit = false;
            }
        }
        if (keystates[SDLK_SPACE] && SDL_GetTicks() - my_bullet_clock > 300){
            my_bullet_clock = SDL_GetTicks();
            mywarship->fire();
        }

        //===================Collision Detection===============
        for(unordered_set<Enemy *>::iterator ite = enemy_set.begin(); ite != enemy_set.end(); )
        {
            if((*ite)->isAlive())
            {
                (*ite)->fire();
                const SDL_Rect &Myship = mywarship->getRect();
                const SDL_Rect &EnemyTemp = (*ite)->getRect();
                if (isCollision(Myship, EnemyTemp)){
                    is_gaming = false;
                    break;
                }
                for(unordered_set<Bullet *>::iterator iite = friend_bullets.begin(); iite != friend_bullets.end(); )
                {
                    const SDL_Rect &MyBullet = (*iite)->getRect();
                    if (isCollision(MyBullet, EnemyTemp))
                    {
                        score += 1000;
                        Enemy *ptr = *ite;
                        Bullet *ptr_b = *iite;
                        iite = friend_bullets.erase(iite);
                        delete ptr_b;
                        ptr->decHealth(1);
                    }
                    else
                        ++iite;
                }
                ite++;
            }
        }

        for(unordered_set<Bullet *>::iterator ite = enemy_bullets.begin(); ite != enemy_bullets.end(); )
        {
            if((*ite)->isAlive())
            {
                const SDL_Rect &Myship = mywarship->getRect();
                const SDL_Rect &EnemyBullet = (*ite)->getRect();
                if (isCollision(Myship, EnemyBullet)){
                    Bullet *ptr = *ite;
                    mywarship->decHealth(1);
                    ite = enemy_bullets.erase(ite);
                    delete ptr;
                    if(!mywarship->isAlive())
                    {
                        is_gaming = false;
                        break;
                    }
                }
                else
                  ite++;
            }
            else 
                ite++;
        }     





        if (is_boss){
            apply_surface(myboss->getRect().x, myboss->getRect().y, myboss->getSurface(), screen);
            myboss->updatePos(mywarship->getRect().x);
            //myboss->fire();
            const SDL_Rect &Myship_rect = mywarship->getRect();
            const SDL_Rect &Myboos_rect = myboss->getRect();
            if (isCollision(Myship_rect, Myboos_rect)){
                is_gaming = false;
            }
            //======check collision between my bullets and boss========
 
        }




        //================Apply_Surface && Update_Position=============
        apply_surface(0,0,background,screen);
        apply_surface(10, 10, score_surface, scraeen);
        apply_surface(mywarship->getRect().x, mywarship->getRect().y, warship, screen);
        mywarship->updatePos();

        for(unordered_set<Enemy *>::iterator ite = enemy_set.begin(); ite != enemy_set.end(); ite++)
        {
            if ((*ite)->isVisible())
                apply_surface((*ite)->getRect().x, (*ite)->getRect().y, (*ite)->getSurface(), screen);
            if ((*ite)->isAlive()){
                (*ite)->updatePos();
            }
            else{
                if (SDL_GetTicks() - enemy_clock > 1000 && !is_boss) {
                    enemy_clock = SDL_GetTicks();
                    Enemy *ptr = *ite;
                    ptr->setPosX(rand()%WIDTH_SCREEN);
                    ptr->setPosY(0);
                    ptr->hide();
                    ptr->resurrect();
                }
            }
        }

        for(unordered_set<Bullet *>::iterator ite = friend_bullets.begin(); ite != friend_bullets.end(); )
        {
            if((*ite)->isAlive())
            {                            
                apply_surface((*ite)->getRect().x, (*ite)->getRect().y, my_bullet, screen); 
                (*ite)->updatePos();  
                ite++;
            }
            else
            {
                Bullet *ptr = *ite;
                delete ptr;
                ite = friend_bullets.erase(ite);
            }
        }

        for(unordered_set<Bullet *>::iterator ite = enemy_bullets.begin(); ite != enemy_bullets.end(); )
        {
            if((*ite)->isAlive())
            {
                apply_surface((*ite)->getRect().x, (*ite)->getRect().y, (*ite)->getSurface(), screen);   
                (*ite)->updatePos(); 
                ite++;
            }
            else 
                ite++;
        }     
 
        if (SDL_Flip(screen) == -1) return 0;
        if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
             SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
        }
        score++;
        if (score > 30000)
            is_boss = true;
    }
    for(unordered_set<Enemy *>::iterator ite = enemy_set.begin(); ite != enemy_set.end(); ){
        delete(*ite);
        ++ite;
    }
    delete(mywarship);
    enemy_bullets.clear();
    friend_bullets.clear();
    friend_bombs.clear();
    score = 0;
}

bool init() {
    if (SDL_Init (SDL_INIT_EVERYTHING ) == -1)
        return false;

    screen = SDL_SetVideoMode(WIDTH_SCREEN, HEIGHT_SCREEN, BPP_SCREEN, SDL_SWSURFACE);

    if (screen == NULL)
        return false;

    /*if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        return false;
    */
    if ( TTF_Init() == -1 ) 
        return false;

    SDL_WM_SetCaption ("Warship", NULL);
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 128 ) == -1 )
    {
        return false;    
    }
    if( initted & flags != flags) {
        cout<<"could not init SDL_Image" << endl;
        cout<<"Reason: " << IMG_GetError() << endl;
    }
    score_temp = new char[14];
    score_temp[0] = 'S';
    score_temp[1] = 'C';
    score_temp[2] = 'O';
    score_temp[3] = 'R';
    score_temp[4] = 'E';
    score_temp[5] = ':';
    score_temp[6] = ' ';
    for (int i = 7; i < 14; i++)
        score_temp[i] = '0';
    return true;
}
void clean_up(){
    SDL_FreeSurface(background);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(warship);
    //SDL_FreeSurface();                                                
    //SDL_FreeSurface();                                                
    //SDL_FreeSurface();                                                
    SDL_FreeSurface(enemy);
    SDL_FreeSurface(my_bullet);
    SDL_FreeSurface(enemy_bullet);
    TTF_CloseFont(font_28);
    TTF_CloseFont(font_80);
    TTF_CloseFont(font_36);
    SDL_FreeSurface(enemy1);
    SDL_FreeSurface(enemy_explode);
    TTF_Quit();
    SDL_Quit();
}

SDL_Surface *load_image(std::string filename) {
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;

  loadedImage = IMG_Load(filename.c_str());

  if (loadedImage != NULL) {
    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);

    /*if (optimizedImage != NULL) {
      // Uint32 colorket = SDL_MapRGB( optimizedImage->format, 0, 0xFF,\
 0xFF);                                                                 
      SDL_SetColorKey (optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 255 , 255, 255));
    }*/
  }

  return optimizedImage;
}

void apply_surface (int x, int y, SDL_Surface* source, SDL_Surface* destination) {
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface( source, NULL, destination, &offset);
}

bool load_files(){

    background = load_image("background.png");
    warship = IMG_Load("myaircrf.png");
    enemy = IMG_Load("enemy.png");
    my_bullet = IMG_Load("bullet.png");
    enemy_bullet = IMG_Load("enemy_bullet.png");
    font_28 = TTF_OpenFont("ChalkDust.ttf", 28);
    font_80 = TTF_OpenFont("ChalkDust.ttf", 80);
    font_36 = TTF_OpenFont("ChalkDust.ttf", 36);
    enemy1 = IMG_Load("enemy1.png");
    color = { 0, 0, 0 };
    shoot = Mix_LoadWAV("shoot.wav");
    enemy_explode = IMG_Load("enemy_explode.png");
    //weapon = load_image("");
    //boss = load_image("");

    //======= music =========                                           
    if (background == NULL) return false;
    if (warship == NULL) return false;
    //if (enemy == NULL) return false;
    //if (weapon == NULL) return false;
    //if (boss == NULL) return false;
    return true;

}

bool isCollision(const SDL_Rect &A, const SDL_Rect &B)
{
    bool intersectVertical = false;
    bool intersectHorizontal = false;
    int wideLeft, wideRight, narrowLeft, narrowRight;
    int highTop, highBottom, shortTop, shortBottom;

    if(A.w < B.w)
    {
        wideLeft = B.x;
        wideRight = B.x+B.w;
        narrowLeft = A.x;
        narrowRight = A.x+A.w;
    }
    else
    {
        wideLeft = A.x;
        wideRight= A.x+A.w;
        narrowLeft = B.x;
        narrowRight = B.x+B.w;
    }

    if(A.h < B.h)
    {
        highTop = B.y;
        highBottom = B.y+B.h;
        shortTop = A.y;
        shortBottom = A.y+A.h;
    }
    else
    {
        highTop = A.y;
        highBottom = A.y+A.h;
        shortTop = B.y;
        shortBottom = B.y+B.h;
    }

    if((wideLeft <= narrowLeft && narrowLeft <= wideRight) ||
       (wideLeft <= narrowRight && narrowRight <= wideRight))
        intersectHorizontal = true;
  
    if((highTop <= shortTop && shortTop <= highBottom) ||
       (highTop <= shortBottom && shortBottom <= highBottom))
        intersectVertical = true;
    return intersectVertical && intersectHorizontal;
}
