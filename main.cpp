#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_rotozoom.h"
#include <string>
#define random(x) (rand()%x)
#include <unordered_set>
#include <unistd.h>
#include <string.h>
#include "boss.h"
#include "enemy.h"
#include "timer.h"
#include "warship.h"
#include "bomb.h"
#include "bullet.h"
#include "object.h"
#include "constants.h"
#include "explosion.h"
#include "treasure.h"

#include <assert.h> 
using namespace std; 

unordered_set<Bullet *> enemy_bullets;
unordered_set<Bullet *> friend_bullets; 
unordered_set<Bomb *> friend_bombs;
bool bombexploded;
int bombcount;
int treasure_count = 0;
SDL_Surface *bloodframe = NULL;
SDL_Surface *bloodpix = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *bomb_sign = NULL;
SDL_Surface *bomb_surface = NULL;
SDL_Surface *background = NULL;
SDL_Surface *my_bullet = NULL;
SDL_Surface *enemy_bullet = NULL;
SDL_Surface *super_bullet = NULL;
SDL_Surface *trea1 = NULL;
SDL_Surface *trea2 = NULL;
SDL_Surface *warship = NULL;
SDL_Surface *enemy = NULL;
SDL_Surface *my_boss = NULL;
SDL_Surface *game_logo = NULL;
SDL_Surface *game_start_message = NULL;
SDL_Surface *score_surface = NULL;
SDL_Surface *end_die = NULL;
SDL_Surface *end_options1 = NULL;
SDL_Surface *your_score = NULL;
SDL_Surface *end_options2 = NULL;
SDL_Surface *enemy1 = NULL;
SDL_Surface *enemy_explode = NULL;
SDL_Surface *enemy_explode1 = NULL;
SDL_Surface *boss_explode = NULL;
SDL_Surface *bullet_explode = NULL;
SDL_Surface *my_bomb = NULL;
SDL_Surface *bomb_explode = NULL;
SDL_Surface *game_start_message_ = NULL;
Mix_Music *music = NULL;

int score = 0;
int bombnum = 2;
int boss_limit = 10000;
char * score_temp;
SDL_Color color;
bool quit;
bool init();
int read_highscore();
void write_highscore(int _score, int _high_score);
void clean_up();
SDL_Surface *load_image(std::string filename);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
bool load_files();
bool to_game();
SDL_Surface *your_score_to_surface(int score);
SDL_Surface *highscore_to_surface(int score);
SDL_Surface *num_to_surface(int num);
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
        int pre_high = read_highscore();
        apply_surface(0, 0, background, screen);
        if (score < pre_high)
        {
            if(end_die)
            {
                SDL_FreeSurface(end_die);
                end_die = NULL;
            }
            end_die = TTF_RenderText_Solid(font_80, "GAME OVER", color);
        }
        else
        {
            if(end_die)
            {
                SDL_FreeSurface(end_die);
                end_die = NULL;
            }
            end_die = TTF_RenderText_Solid(font_80, "Highscore!", color);
        }
        apply_surface(90, 210, end_die, screen);
        end_options1 = TTF_RenderText_Solid(font_28, "Press A to Start Again", color);
        end_options2 = TTF_RenderText_Solid(font_28, "Press Q to Quit Game", color);
        write_highscore(score, pre_high);
        if (pre_high <= score) pre_high = score;
        SDL_Surface *score_surface1 = your_score_to_surface(score);
        apply_surface(180, 360, score_surface1, screen);
        SDL_Surface *score_surface2 = highscore_to_surface(pre_high);        
        apply_surface(190, 395, score_surface2, screen);
        apply_surface(140, 430, end_options1, screen);
        apply_surface(140, 465, end_options2, screen);
        
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
        SDL_FreeSurface(end_options2);
        SDL_FreeSurface(end_options1);
        SDL_FreeSurface(score_surface1);
        SDL_FreeSurface(score_surface2);
    }
    //========================================================================
    clean_up();
  
    return EXIT_SUCCESS;
}

bool to_game(){
  int bullet_lapse = 200;
    score = 0;
    Timer fps;
    enemy_bullets.clear();
    friend_bullets.clear();
    friend_bombs.clear();
    SDL_Rect rect_bullet;
    bzero(&rect_bullet, sizeof(rect_bullet));
    rect_bullet.x = 0;
    rect_bullet.y = 0;
    rect_bullet.w = 13; 
    rect_bullet.h = 30;
 
    SDL_Rect rect_ship;
    rect_ship.x = 270;
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
    rect_boss.y = -254;
    rect_boss.w = 169;
    rect_boss.h = 254;

    SDL_Rect rect_treasure;
    rect_treasure.x = 200;
    rect_treasure.y = -20;
    rect_treasure.w = 40;
    rect_treasure.h = 40;


    bombexploded = false;
    treasure_count = 0;
    //Explosion *exp1 = new Explosion(???????);
    bombcount = 0; 
    bool is_gaming = true;
    bool is_boss = false; 
    //warship = zoomSurface(warship, 0.5, 0.5, 1);
 
    Bullet *bullet1 = new Bullet(0, -20, rect_bullet, enemy_bullet, 1);
    bullet1->show();
    bullet1->updatePos();
    Bullet *bullet2 = new Bullet(0, -20, rect_bullet, super_bullet, 2);
    bullet2->show();

    Bullet *bullet_e = new Bullet(0, 20, rect_bullet, enemy_bullet, 2);
    bullet_e->show();

    vector<SDL_Surface *> *explosion = new vector<SDL_Surface *>();
    explosion->push_back(enemy_explode);

    vector<SDL_Surface *> *bossexplosion = new vector<SDL_Surface *>();
    bossexplosion->push_back(boss_explode);

    vector<SDL_Surface *> *explosion1 = new vector<SDL_Surface *>();
    explosion1->push_back(enemy_explode1);

    vector<SDL_Surface *> *bombexplosion = new vector<SDL_Surface *>();
    bombexplosion->push_back(bomb_explode);

    Bomb *bomb = new Bomb(0, 20, rect_bullet, my_bomb, bombexplosion, 10);
    vector<Warship *> mywarship;
    mywarship.push_back(new Warship(13, 13, rect_ship, warship, 10, 10, explosion, bullet1, bomb, 0, 2));
///////////////////////////////////--------------------
    
    int boss_counter = 0;

    Treasure *treasure = new Treasure(0, -20, rect_treasure, trea1, 0);
 
    Boss *myboss = new Boss(0, 5, rect_boss, my_boss, 20, 20, bossexplosion, bullet_e, 30);
    
    Enemy *myenemy = new Enemy(0, 5, rect_enemy, enemy, 2, 2, explosion, bullet_e, 30);
    Enemy *myenemy1 = new Enemy(0, 5, rect_enemy1, enemy1, 4, 4, explosion1, bullet_e, 30);

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
    Uint32 my_bullet_clock0 = SDL_GetTicks();
    Uint32 my_bullet_clock1 = SDL_GetTicks();

    bool single = true;
    //=====================PRE-START================================
    bool st = true;
    apply_surface(0, 0, background, screen);
    game_logo = TTF_RenderText_Solid(font_80, "WARCHIP", color);
    apply_surface(145, 170, game_logo, screen);
    game_start_message = TTF_RenderText_Solid(font_20, "Single Player Mode : Press Any Key", color);
    game_start_message_= TTF_RenderText_Solid(font_20, "Multi-Player Mode : Press Z", color);
    apply_surface(115, 300, game_start_message, screen);
    apply_surface(140, 320, game_start_message_, screen);
    while(st){
        while(SDL_PollEvent( &event)){
            if (event.type == SDL_QUIT){
                st = false;
                is_gaming = false;
                quit = false;
            }            
            else if(event.key.keysym.sym == SDLK_z)
            {
                single = false;
                st = false;
                mywarship.push_back(new Warship(13, 13, rect_ship, warship, 10, 10, explosion, bullet1, bomb, 1, 2));
            }
            else if (event.type == SDL_KEYDOWN){
                st = false;
            }
        }
        for(int z = 0; z < mywarship.size(); ++z)
            apply_surface(mywarship[z]->getRect().x, mywarship[z]->getRect().y, mywarship[z]->getSurface(), screen);
        if (SDL_Flip(screen) == -1) return 0;
    }
    //SDL_FreeSurface(game_logo);
    //SDL_FreeSurface(game_start_message);
    //SDL_FreeSurface(game_start_message_);
    //=================================================================
    Mix_PlayMusic( music, -1 );

    //====================START-GAME===================================
    while (is_gaming){
        //cout<<score<<endl;
        keystates = SDL_GetKeyState( NULL );
        apply_surface(0,0,background,screen);

    //===================blood===========================
      
      
      apply_surface(390, 20, bloodframe, screen);
      switch(mywarship[0]->getHealth()) {
      case 10:
        apply_surface(400, 25, bloodpix, screen);
      case 9:
	    apply_surface(420, 25, bloodpix, screen);
      case 8:
	    apply_surface(440, 25, bloodpix, screen);
      case 7:
	    apply_surface(460, 25, bloodpix, screen);
      case 6:
	    apply_surface(480, 25, bloodpix, screen);
      case 5:
	    apply_surface(500, 25, bloodpix, screen);
      case 4:
	    apply_surface(520, 25, bloodpix, screen);
      case 3:
	    apply_surface(540, 25, bloodpix, screen);
      case 2:
	    apply_surface(560, 25, bloodpix, screen);
      case 1:
	    apply_surface(580, 25, bloodpix, screen);      
      } 
      if(mywarship.size() > 1) {
	apply_surface(390, 45, bloodframe, screen);
	switch(mywarship[1]->getHealth()) {
	case 10:
	  apply_surface(400, 50, bloodpix, screen);
	case 9:
	  apply_surface(420, 50, bloodpix, screen);
	case 8:
	  apply_surface(440, 50, bloodpix, screen);
	case 7:
	  apply_surface(460, 50, bloodpix, screen);
	case 6:
	  apply_surface(480, 50, bloodpix, screen);
	case 5:
	  apply_surface(500, 50, bloodpix, screen);
	case 4:
	  apply_surface(520, 50, bloodpix, screen);
	case 3:
	  apply_surface(540, 50, bloodpix, screen);
	case 2:
	  apply_surface(560, 50, bloodpix, screen);
	case 1:
	  apply_surface(580, 50, bloodpix, screen);
	} 
	
      }

        //=============score!!!!=======================
        int base = 10;
        for (int j = 13; j >= 7; j--){
           score_temp[j] = (score % (base * 10) - score % base) /base + '0';
           base = base * 10;
        }
        SDL_Surface *score_surface3  = NULL;
        score_surface3 = TTF_RenderText_Solid(font_28, score_temp, color);
        apply_surface(10, 10, score_surface3, screen);
        //free(score_surface);
        apply_surface(20, 745, bomb_sign, screen);
        bomb_surface = num_to_surface(mywarship[0]->getNumBomb());
        apply_surface(70, 750, bomb_surface, screen);
        //SDL_FreeSurface(bomb_surface);
        if(mywarship.size() > 1) {
            apply_surface(100, 745, bomb_sign, screen);
            SDL_FreeSurface(bomb_surface);
            bomb_surface = num_to_surface(mywarship[1]->getNumBomb());
            apply_surface(150, 750, bomb_surface, screen);
        }
        //==============================================
        fps.start();

        while(SDL_PollEvent( &event ))
        {
            
            if (event.type == SDL_QUIT){
                is_gaming = false;
                quit = false;
            } 
            else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_RIGHTBRACKET){
                    mywarship[0]->launch();
                    mywarship[0]->decNumBomb();
                } 
                if (event.key.keysym.sym == SDLK_u){
                    if(mywarship.size() > 1)
                    {
                        mywarship[1]->launch();
                        mywarship[1]->decNumBomb();
                    }
                } 
            } 
        }

        if (keystates[SDLK_LEFTBRACKET] && SDL_GetTicks() - my_bullet_clock0 > bullet_lapse){
            my_bullet_clock0 = SDL_GetTicks();
            //Mix_PlayChannel( -1, shoot, 0 );
            mywarship[0]->fire();
        }
        if (keystates[SDLK_y] && SDL_GetTicks() - my_bullet_clock1 > bullet_lapse){
            my_bullet_clock1 = SDL_GetTicks();
            //Mix_PlayChannel( -1, shoot, 0 );
            if(mywarship.size() > 1)
                mywarship[1]->fire();
        }
        //mywarship->updatePos();
        //cout<<"@@"<<mywarship->getRect().x<<endl;
        for(int z = 0; z < mywarship.size(); ++z)
            apply_surface(mywarship[z]->getRect().x, mywarship[z]->getRect().y, mywarship[z]->getSurface(), screen);


        if (is_boss){
            int tmp_x = mywarship[0]->getRect().x;
            for(int z = 1; z < mywarship.size(); ++z)
                tmp_x  = (tmp_x + mywarship[z]->getRect().x)/2;
            myboss->updatePos(tmp_x);
            boss_counter++;
            if (boss_counter > 14){
                myboss->fire();
                boss_counter = 0;
            }
            for(int z = 0; z < mywarship.size(); ++z)
                if (isCollision(mywarship[z]->getRect(), myboss->getRect()))
                    is_gaming = false; 
           // ======check collision between my bullets and boss========
            for(unordered_set<Bullet *>::iterator ite = friend_bullets.begin(); ite != friend_bullets.end();){
                if ((*ite)->isAlive()){
                    const SDL_Rect &bullet_rect = (*ite)->getRect();
                    if (isCollision(bullet_rect, myboss->getRect())){
                        myboss->decHealth((*ite)->getDamage());
                        Bullet *ptr_b = *ite;
                        score+=1000;
                        apply_surface((*ite)->getRect().x, (*ite)->getRect().y, bullet_explode, screen);   
                        ite = friend_bullets.erase(ite);
                        delete ptr_b;
                    }else
                        ++ite;
                }
                else
                    ++ite;
            }
            apply_surface(myboss->getRect().x, myboss->getRect().y, myboss->getSurface(), screen);

            if (!myboss->isAlive()){
                is_boss = false;
                * myboss = Boss(0, 5, rect_boss, my_boss, 20, 20, bossexplosion, bullet_e, 30);
            }
        }


//=================Collision Check=================
        for(unordered_set<Enemy *>::iterator ite = enemy_set.begin(); ite != enemy_set.end(); )
        {
            if((*ite)->isAlive())
            {
                if (bombexploded){
                    (*ite)->decHealth(4);
                    score+=1000;
                }
                if ((*ite)->getRect().w == rect_enemy.w) (*ite)->fire(25, 30);
                else (*ite)->fire(44, 125);

                const SDL_Rect &EnemyTemp = (*ite)->getRect();
                for(int z = 0; z < mywarship.size(); ++z)
                    if (isCollision(mywarship[z]->getRect(), EnemyTemp))
                        is_gaming = false; 

                for(unordered_set<Bullet *>::iterator iite = friend_bullets.begin(); iite != friend_bullets.end(); )
                {
                    const SDL_Rect &MyBullet = (*iite)->getRect();
                    if (isCollision(MyBullet, EnemyTemp))
                    {
                        score += 1000;
                        Enemy *ptr = *ite;
                        Bullet *ptr_b = *iite;
                        ptr->decHealth((*iite)->getDamage());
                        apply_surface(ptr_b->getRect().x, (*iite)->getRect().y - 5, bullet_explode, screen);   
                        iite = friend_bullets.erase(iite);
                        delete ptr_b;
                        if (!(*ite)->isAlive())
                            apply_surface((*ite)->getRect().x, (*ite)->getRect().y, (*ite)->getSurface(), screen);   

                    }
                    else
                        ++iite;
                }
                ite++;
            }
            else
            {
                if (SDL_GetTicks() - enemy_clock > 1000 && !is_boss) {
                    enemy_clock = SDL_GetTicks();
                    Enemy *ptr = *ite;
                    ptr->setPosX(rand()%WIDTH_SCREEN);
                    if (ptr->getRect().h < 100)
                        ptr->setPosY(-42);
                    else
                        ptr->setPosY(-130);
                    ptr->hide();
                    ptr->resurrect();
                }
                ite++;               
            }
        }


        for(unordered_set<Bullet *>::iterator ite = enemy_bullets.begin(); ite != enemy_bullets.end(); )
        {
            if((*ite)->isAlive())
            {                
                const SDL_Rect &EnemyBullet = (*ite)->getRect();
                for(int z = 0; z < mywarship.size(); ++z)
                {
                    const SDL_Rect &Myship = mywarship[z]->getRect();
                    if (isCollision(Myship, EnemyBullet)){
                        Bullet *ptr = *ite;
                        mywarship[z]->decHealth(1);
                        apply_surface((*ite)->getRect().x, (*ite)->getRect().y + 4, bullet_explode, screen);   
                        cout<<mywarship[z]->getHealth()<<endl;
                        ite = enemy_bullets.erase(ite);                        
                        delete ptr;                    
                        if(!mywarship[z]->isAlive())
                        {
                            is_gaming = false;
                            break;
                        }
                        if(ite == enemy_bullets.end())
                            break;
                    }                     
                }
                // else
                // {
                //     ite++;
                // }
                // ++ite;
            }
            if(ite == enemy_bullets.end())
                break;
            ite++;
        }     
        bombexploded = false;
        treasure_count++;
//==================Treasure Collision==============
        if (treasure_count > 300){
            for(int z = 0; z < mywarship.size(); ++z)
            {
                const SDL_Rect &warship_temp_rect = mywarship[z]->getRect();
                const SDL_Rect &treasure_temp_rect = treasure->getRect();
                if (isCollision(warship_temp_rect, treasure_temp_rect)){
                    int temp = treasure->getMode();
                    //cout<<"trea"<<temp<<endl;
                    treasure_count = 0;
                    if (temp == 0){
                        mywarship[z]->setBullet(bullet2);
                    }
                    else if (temp == 1){
                        mywarship[z]->incNumBomb();
                    }
                    *treasure = Treasure(0, -20, rect_treasure, NULL, random(2)); 
                    temp = treasure->getMode();
                    if (temp == 0)
                        treasure->setSurface(trea1);
                    else if (temp == 1)
                        treasure->setSurface(trea2);       
                }
                apply_surface(treasure->getRect().x, treasure->getRect().y, treasure->getSurface(), screen);
                treasure->updatePos();
            }
        }


//==================apply surface && upPos=====
            



        for(int z = 0; z < mywarship.size(); ++z)
            mywarship[z]->updatePos();
        for(unordered_set<Bomb *>::iterator ite = friend_bombs.begin(); ite != friend_bombs.end(); )
        {
            (*ite)->updatePos();
            apply_surface((*ite)->getRect().x, (*ite)->getRect().y, (*ite)->getSurface(), screen);
            if (!(*ite)->isAlive()){
                Bomb *tmp = *ite;
                ite = friend_bombs.erase(ite);
                delete tmp;
                bombexploded = true;
            }
            else
                ++ite;
        }

        for(unordered_set<Enemy *>::iterator ite = enemy_set.begin(); ite != enemy_set.end(); ite++)
        {
            //if ((*ite)->isAlive()){
                if((*ite)->isVisible())
                    apply_surface((*ite)->getRect().x, (*ite)->getRect().y, (*ite)->getSurface(), screen);   
                else if(rand()%3 == 0)
                    (*ite)->show();
                (*ite)->updatePos();
                if (!(*ite)->isAlive())
                    (*ite)->hide();
            //}sa
        }


        for(unordered_set<Bullet *>::iterator ite = friend_bullets.begin(); ite != friend_bullets.end(); )
        {
            if((*ite)->isAlive())
            {                            
                apply_surface((*ite)->getRect().x, (*ite)->getRect().y, (*ite)->getSurface(), screen);   
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

        for(unordered_set<Bullet *>::iterator ite = enemy_bullets.begin(); ite != enemy_bullets.end(); ite++)
        {
            if((*ite)->isAlive()){
                apply_surface((*ite)->getRect().x, (*ite)->getRect().y, (*ite)->getSurface(), screen);
                (*ite)->updatePos(); 
            }
        }
//================================================


        if (SDL_Flip(screen) == -1) return 0;
        if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND) {
             SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
        }
        score++;
        if (score > boss_limit){
            is_boss = true;
            boss_limit += 1.2 * boss_limit;
        }
        SDL_FreeSurface(bomb_surface);
        SDL_FreeSurface(score_surface3);
    }
    for(unordered_set<Enemy *>::iterator ite = enemy_set.begin(); ite != enemy_set.end(); ){
        delete(*ite);
        ++ite;
    }
    for(unordered_set<Bullet *>::iterator ite = enemy_bullets.begin(); ite != enemy_bullets.end(); ){
        delete(*ite);
        ++ite;
    }
    for(unordered_set<Bullet *>::iterator ite = friend_bullets.begin(); ite != friend_bullets.end(); ){
        delete(*ite);
        ++ite;
    }


    for(int z = 0; z < mywarship.size(); ++z)
        delete(mywarship[z]);
//==============================
    delete(bullet_e);
    delete(explosion);
    delete(bossexplosion);
    delete(bombexplosion);
    delete(explosion1);
    delete(bomb);
    delete(bullet1);
    delete(bullet2);
    delete(treasure);
    delete(myboss);
    delete(myenemy);
    delete(myenemy1);
    //=============================




    enemy_bullets.clear();
    friend_bullets.clear();
    friend_bombs.clear();
    bombnum = 2;
    // clean_up();
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
    score_temp = new char[15];
    bzero(score_temp, 15);
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
    Mix_FreeMusic( music );
    SDL_FreeSurface(warship);
    //SDL_FreeSurface();                                                
    //SDL_FreeSurface();     
    SDL_FreeSurface(bloodframe);                                      
    SDL_FreeSurface(bloodpix);                                        
    SDL_FreeSurface(bomb_sign);
    //SDL_FreeSurface(bomb_surface);
    SDL_FreeSurface(my_boss);
    
    SDL_FreeSurface(super_bullet);
    SDL_FreeSurface(trea1);
    SDL_FreeSurface(trea2);
    
    SDL_FreeSurface(score_surface);
    SDL_FreeSurface(end_die);
    //SDL_FreeSurface(end_options1);
    SDL_FreeSurface(your_score);
    //SDL_FreeSurface(end_options2);
    SDL_FreeSurface(enemy_explode1);
    SDL_FreeSurface(boss_explode);
    SDL_FreeSurface(bullet_explode);
    SDL_FreeSurface(my_bomb);
    SDL_FreeSurface(bomb_explode);                                           
    //SDL_FreeSurface();                                                
    SDL_FreeSurface(enemy);
    SDL_FreeSurface(my_bullet);
    SDL_FreeSurface(enemy_bullet);
    TTF_CloseFont(font_28);
    TTF_CloseFont(font_80);
    TTF_CloseFont(font_20);
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
    bloodframe = load_image("bloodframe.png");
    bloodpix = load_image("bloodpix.png");
    assert(bloodpix != NULL);
    background = load_image("background.png");
    music = Mix_LoadMUS( "music.wav" );
    warship = IMG_Load("myaircrf.png");
    my_bomb = IMG_Load("bomb.png");
    enemy = IMG_Load("enemy.png");
    my_bullet = IMG_Load("enemy_bullet.png");
    my_boss = IMG_Load("boss.png");
    enemy_bullet = IMG_Load("enemy_bullet.png");
    font_20 = TTF_OpenFont("ChalkDust.ttf", 20);
    font_28 = TTF_OpenFont("ChalkDust.ttf", 28);
    font_80 = TTF_OpenFont("ChalkDust.ttf", 80);
    font_36 = TTF_OpenFont("ChalkDust.ttf", 36);
    boss_explode = IMG_Load("boss_explosion.png");
    bomb_explode = IMG_Load("bomb_explode.png");
    enemy1 = IMG_Load("enemy1.png");
    trea1 = IMG_Load("trea1.png");
    trea2 = IMG_Load("trea2.png");
    super_bullet = IMG_Load("bullet.png");
    color = { 0, 0, 0 };
    bomb_sign = IMG_Load("bomb_sign.png");
    shoot = Mix_LoadWAV("shoot.wav");
    enemy_explode = IMG_Load("enemy_explode.png");
    enemy_explode1 = IMG_Load("enemy_explode1.png");
    //weapon = load_image("");
    //boss = load_image("");
    bullet_explode = IMG_Load("bullet_explode.png");
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

int read_highscore() {
  FILE *f = NULL;
  size_t len;
  char *str = NULL;
  char **endptr = NULL;
  int highscore = 0;
  f = fopen("highscore.txt", "r");
  if ( getline( &str, &len, f) != -1) {
    highscore = strtol(str, endptr, 10);
  }
  free(str);
  fclose(f);
  return highscore;
}

void write_highscore(int _score, int _high_score) {
  if (_score > _high_score) {
    FILE *f = fopen("highscore.txt", "w");
    fprintf(f, "%d\n", _score);
    fclose(f);
  }
}

SDL_Surface *your_score_to_surface(int score){
    char str[80];
    char str1[80];
    bzero(str, 80);
    bzero(str1, 80);
    strcat(str,"Your Score:");
    sprintf(str1, " %d" , score/10);
    strcat(str, str1);
    SDL_Surface *temp = TTF_RenderText_Solid(font_28, str, color);
    return temp;
}

SDL_Surface *highscore_to_surface(int score){
    char str[20];
    char str1[20];
    bzero(str, 20);
    bzero(str1, 20);
    strcat(str,"Highscore:");
    sprintf(str1, " %d" , score/10);
    strcat(str, str1);
    SDL_Surface *temp = TTF_RenderText_Solid(font_28, str, color);
    return temp;
}

SDL_Surface *num_to_surface(int num){
    char str[3];
    sprintf(str, "%d", num);
    SDL_Surface *temp = TTF_RenderText_Solid(font_28, str, color);
    return temp;
}
