//
//  Enemy2.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/10/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#ifndef __PlaneGame__Enemy2__
#define __PlaneGame__Enemy2__

#include <iostream>
#include <string>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include "GlobalElement.h"
#include "Texture.h"
#include "Enemy_bullet.h"
#include "Enemy.h"

class Enemy2:public Enemy{
private:
    float bullet_speed;
    int bullet_amo=1;
    bool canShoot=true;
    SDL_Rect enemy2Rect;
    
    //oop
    Texture enemy;
    
    vector<Enemy_bullet*> bullet;
    
public:
    Enemy2(string filename, int x, int y, int w, int h, int yDir, int s, int hea, float bullet_s);
    
    void render();
    
    void move(int x, int y);
    
    SDL_Rect position();
    
    vector<Enemy_bullet *> get_eb();
    
    void shoot(int x, int y);
    
    void destroy_tex();
    
    ~Enemy2();
    
};

#endif /* defined(__PlaneGame__Enemy2__) */
