//
//  Boss1.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/11/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#ifndef __PlaneGame__Boss1__
#define __PlaneGame__Boss1__
#include <iostream>
#include <string>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <time.h>
#include "GlobalElement.h"
#include "Texture.h"
#include "Enemy_bullet.h"
#include "Enemy.h"

class Boss1:public Enemy{
private:
    int bullet_amo;
    int last_shoot;
    SDL_Rect enemy1Rect;
    
    //oop
    Texture enemy;
    
    vector<Enemy_bullet*> bullet;
    
public:
    Boss1(string filename);
    
    void render();
    
    void move(int x, int y);
    
    SDL_Rect position();
    
    vector<Enemy_bullet *> get_eb();
    
    void shoot(int x, int y);
    
    int get_last_shoot();
    
    void destroy_tex();
    
    ~Boss1();
    
};
#endif /* defined(__PlaneGame__Boss1__) */
