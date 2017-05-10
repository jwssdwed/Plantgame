//
//  GameManage.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/23/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#ifndef __PlaneGame__GameManage__
#define __PlaneGame__GameManage__

#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <cmath>
#include <vector>
#include <unistd.h>
#include <time.h>
#include "GlobalElement.h"
#include "Texture.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Plane_bullet.h"
#include "Background.h"
#include "Plane.h"
#include "Boss1.h"
#include "Property.h"
#include "Button.h"

class GameManage{
private:
    Mix_Chunk *hitSound ;
    Mix_Chunk *boomSound;
    Mix_Chunk *plane_boom_Sound ;
    clock_t start;
    bool ship[6];
    bool bullet[6];
    int round;
    int level;
    clock_t finish;
    
    //boss
    long boss;
    int boss_last_shoot;
    
    //boom visual
    Texture bomb;
    Texture boom1 ;
    Texture boom2;
    
    //    stringstream ss_score;
    stringstream ss_health;
    stringstream ss_health_help;
    char* str_score;
    char* str_health;
    const char* str_health_help = "x";
    
    SDL_Rect textRect_score;
    SDL_Rect textRect_health;
    SDL_Rect textRect_health_help;
    
    //font
    SDL_Texture * fontText;
    SDL_Surface *text;
    TTF_Font *font;
    SDL_Color texColor;
    
    SDL_Texture *fontText_health;
    SDL_Surface *text_health;
    SDL_Texture *fontText_health_help;
    SDL_Surface *text_health_help;
    
    
    //oop
    Texture *bossWarning;
    Texture *hp;
    Property * property;
    vector<Enemy*> enemy_man;
    vector<Enemy_bullet *> enemy_bullet;
    Background *background1;
    Background *background2;
    Background *background3;
    Background *background4;
    Texture *black_background;
    
    
public:
    GameManage();
    
    void start_game();
    
    void render();
    
    void check_all_enemy_motivation(Plane *plane, bool *quit, bool *next);
    
    void check_plane_all_enemyBullet(Plane *plane, bool *quit);
    
    void check_enemy_each_planeBullet(vector<Plane_bullet *> plane_bullet, Enemy * enemy, int index, bool *next, Plane *plane);
    
    bool check_plane_each_enemyBullet(Enemy_bullet * enemy_bullet, Plane *plane);
    
    bool check_each_enemy_plane_hit(Enemy * enemy, Plane *plane);
    
    void check_property_plane(Plane *plane);
    
    void enemy_system(Plane *plane);
    
    void background_system();
    
    void background2_system();
    
    void score_system(Plane *plane);
    
    void health_system(Plane *plane);
    
    void boom_visual(SDL_Rect r1, SDL_Rect r2);
    
    void cleanup();
    
    void continue_game(bool *quit);
};

#endif /* defined(__PlaneGame__GameManage__) */
