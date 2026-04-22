/*
** EPITECH PROJECT, 2026
** game design
** File description:
** expedition 33 X borne d'arcane
*/

#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Dimensions
#define SCREEN_W        900
#define SCREEN_H        600
#define TILE_SIZE       40
#define MAP_COLS        (SCREEN_W / TILE_SIZE)
#define MAP_ROWS        (SCREEN_H / TILE_SIZE)

//Physique & gameplay
#define PLAYER_SPEED    4
#define BULLET_SPEED    9
#define ENEMY_SPEED     1
#define GRAVITY         0.5f
#define JUMP_FORCE     -13.0f
#define MAX_BULLETS     32
#define MAX_ENEMIES     16
#define MAX_PARTICLES   128
#define MAX_PLATFORMS   20
#define FPS             60

//Couleurs (Expedition 33)
#define C_BG_TOP        { 10,  8, 28, 255}
#define C_BG_BOT        { 25, 15, 50, 255}
#define C_PLATFORM      { 80, 55,120, 255}
#define C_PLAT_TOP      {140,100,200, 255}
#define C_PLAYER        {220,190, 80, 255}  /* Gustave - doré */
#define C_PLAYER_COAT   {180, 60, 60, 255}  /* Manteau rouge */
#define C_SWORD         {200,220,255, 255}
#define C_BULLET        {255,100,200, 255}  /* Peinture magique */
#define C_ENEMY         {200, 80, 40, 255}  /* Ennemi - orange */
#define C_ENEMY2        {100, 40,160, 255}  /* Fantôme - violet */
#define C_HP_BAR        {220, 60, 60, 255}
#define C_HP_BG         { 60, 20, 20, 255}
#define C_PAINT_TRAIL   {255,180,240, 255}
#define C_STAR          {255,240,200, 255}
#define C_GROUND        { 50, 35, 80, 255}

//Etats
typedef enum {
    STATE_MENU = 0,
    STATE_PLAYING,
    STATE_GAMEOVER,
    STATE_WIN
} GameState;

typedef enum {
    DIR_LEFT = -1,
    DIR_RIGHT = 1
} Direction;

// Structures
typedef struct {
    float x, y, vx, vy;
    float r, g, b, a;
    int   life, max_life;
} Particle;

typedef struct {
    float x, y, vx, vy;
    int   active;
    int   is_paint; // 1 = sort peinture, 0 = slash
    float angle;
} Bullet;

typedef struct {
    float x, y;
    int   w, h;
} Platform;

typedef struct {
    float    x, y, vx, vy;
    int      hp, max_hp;
    int      active;
    int      on_ground;
    int      type;       // 0=soldat, 1=fantôme
    int      anim_tick;
    Direction dir;
    float    aggro_range;
    int      attack_cd;
} Enemy;

typedef struct {
    float    x, y, vx, vy;
    int      hp, max_hp;
    int      on_ground;
    int      attack_cd;   // cooldown attaque épée
    int      paint_cd;    // cooldown peinture
    int      invincible;  // frames d'invincibilité
    int      anim_tick;
    Direction dir;
    int      is_attacking;
    int      attack_anim; // durée animation
} Player;

typedef struct {
    float x, y;
    float blink;
} Star;

typedef struct {
    SDL_Window*   window;
    SDL_Renderer* renderer;
    TTF_Font*     font_big;
    TTF_Font*     font_med;
    TTF_Font*     font_sm;

    GameState state;
    int       running;
    int       tick;
    int       score;
    int       wave;
    int       enemies_left;

    Player    player;
    Bullet    bullets[MAX_BULLETS];
    Enemy     enemies[MAX_ENEMIES];
    Particle  particles[MAX_PARTICLES];
    Platform  platforms[MAX_PLATFORMS];
    int       num_platforms;

    Star      stars[80];

    //Shake caméra
    int       cam_shake;
    float     cam_ox, cam_oy;
} Game;

//Prototypes
Game* game_create(void);
void  game_destroy(Game* g);
void  game_run(Game* g);

#endif /* GAME_H */
