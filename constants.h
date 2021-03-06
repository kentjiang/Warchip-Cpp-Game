#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

const int WIDTH_SCREEN = 640;
const int HEIGHT_SCREEN = 800;
const int BPP_SCREEN = 32;  // ?

const int NUMBER_ENEMY = 20;

const int STANDARD_SPEED = 5; // the speed of enemy would be 1~3 times of this speed.
const int STANDARD_SPEED_WEAPON = 10;
const int WARSHIP_SPEED = 10;

const int SPEED_TREASURE = -6;
const int TREASURE_WIDTH = 20;
const int TREASURE_HEIGHT = 20;
const int INCREASE_POWER = 0;
const int INCREASE_LIFE = 1;
const int Y_POSITION_WARSHIP = 275;

const int AIRCRAFT_WIDTH = 84;
const int AIRCRAFT_HEIGHT = 34;
const int SUBMARINE_WIDTH = 87;
const int SUBMARINE_HEIGHT = 42;
const int WARSHIP_WIDTH = 120;
const int WARSHIP_HEIGHT = 48;
int bomb_count;

const int NUMBER_BOMB_BOSS = 6;
const int BOSS_HEIGHT = 140;
const int BOSS_WIDTH = 255;
const int STANDARD_SPEED_WEAPON_BOSS = 18;
const int BOSS_SPEED = 20;

const int WEAPON_UP_WIDTH = 20;
const int WEAPON_UP_HEIGHT = 20;
const int WEAPON_UP_WIDTH_POWERFUL = 30;
const int WEAPON_UP_HEIGHT_POWERFUL = 30;
const int WEAPON_DOWN_WIDTH = 25;
const int WEAPON_DOWN_HEIGHT = 32;

const int FRAME_EXPLOSION = 60; //time of explosion 60/20 = 3s

const int FRAMES_PER_SECOND = 20;

const int NUMBER_BOMB = 3;
const int NUMBER_MISSILE = 3;
const int NUMBER_BOMB_ENEMY = 3;

const int TYPE_MISSILE_0 = 0;
const int TYPE_MISSILE_1 = 5;
const int TYPE_BOMB = 1;
const int TYPE_BOMB_SUBMARINE = 2;
const int TYPE_BOMB_AIRCRAFT = 3;
const int TYPE_BOMB_BOSS = 4;

const int EXPLOSION_TYPE_1 = 1;
const int EXPLOSION_TYPE_2 = 2;

SDL_Event event;
Uint8 *keystates;
int boss_offset_x;

SDL_Surface *warship_1 = NULL;
SDL_Surface *warship_2 = NULL;
SDL_Surface *warship_3 = NULL;
SDL_Surface *submarine_1 = NULL;
SDL_Surface *submarine_2 = NULL;
SDL_Surface *aircraft_1 = NULL;
SDL_Surface *aircraft_2 = NULL;
SDL_Surface *weapon_1 = NULL;
SDL_Surface *weapon_2 = NULL;
SDL_Surface *weapon_3 = NULL;
SDL_Surface *weapon_4 = NULL;
SDL_Surface *weapon_5 = NULL;
SDL_Surface *explosion = NULL;
SDL_Surface *boss = NULL;
SDL_Surface *treasure = NULL;
SDL_Surface *weapon_6 = NULL;
Mix_Chunk *shoot = NULL;

Mix_Music *music_background = NULL;
Mix_Chunk *music_urgent = NULL;
Mix_Chunk *music_explosion = NULL;
Mix_Chunk *music_decrease_life = NULL;
Mix_Chunk *music_get_box = NULL;
Mix_Chunk *music_missile_emit = NULL;
Mix_Chunk *music_bomb_emit = NULL;


TTF_Font *font_28 = NULL;
TTF_Font *font_20 = NULL;
TTF_Font *font_80 = NULL;
TTF_Font *font_36 = NULL;
TTF_Font *font_over = NULL;
SDL_Surface *message = NULL;
SDL_Surface *message_over = NULL;
SDL_Color textColor = {255, 0, 0};

#endif
