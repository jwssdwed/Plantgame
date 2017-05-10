//
//  Enemy.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/9/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//
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

#ifndef __PlaneGame__Enemy__
#define __PlaneGame__Enemy__
class Enemy{
protected:
    int _x;
    int _y;
    int _width;
    int _height;
    int _speed;
    bool canShoot;
    int health;
    int value;
    int yDir;
    int xDir;
    SDL_Rect rect;
    
    
    Texture enemy;
public:
    //    virtual void checkCollision();
    //    Enemy(string filename, int a);
    
    virtual void render();
    
    //    virtual void move();
    
    virtual void move(int x,int y);
    
    virtual SDL_Rect position();
    
    virtual void destroy_tex();
    
    virtual void set_health(int a);
    
    virtual int get_health();
    
    virtual int get_value();
    
    virtual vector<Enemy_bullet*> get_eb();
    
    //    virtual Enemy_bullet get_eb();
    
    virtual void shoot(int x, int y);
};

#endif /* defined(__PlaneGame__Enemy__) */
