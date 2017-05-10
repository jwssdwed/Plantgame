//
//  Enemy1.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/9/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#ifndef __PlaneGame__Enemy1__
#define __PlaneGame__Enemy1__

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

class Enemy1:public Enemy{
private:
    //    int _x;
    //    int _y;
    //    int _width;
    //    int _height;
    //    double _speed;
    //    int yDir;
    //    int xDir;
    //    int health;
    //    int value;
    SDL_Rect enemy1Rect;
    bool canShoot;
    
    //oop
    Texture enemy1;
    //    Enemy_bullet eb;
    
    
public:
    Enemy1(string filename);
    
    void render();
    
    void move(int x, int y);
    
    SDL_Rect position();
    
    void destroy_tex();
    
    ~Enemy1();
    
};
#endif /* defined(__PlaneGame__Enemy1__) */
