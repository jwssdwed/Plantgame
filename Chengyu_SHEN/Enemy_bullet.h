//
//  Enemy_bullet.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/10/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#ifndef __PlaneGame__Enemy_bullet__
#define __PlaneGame__Enemy_bullet__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cmath>
#include <vector>
#include <unistd.h>
#include "GlobalElement.h"
#include "Texture.h"
using namespace std;

class Enemy_bullet{
private:
    //bullet
    int _x=-100;
    int _y=-100;
    double yDir = 1;
    double xDir = 1;
    int width = 14;
    int height = 14;
    float _speed=0.007;
    SDL_Rect bullet_rect;
    
    
    //oop
    Texture bulletImg;
    
public:
    Enemy_bullet(string filename);
    
    void render();
    
    void set_x(int x);
    
    void set_y(int y);
    
    void set_Dir(int x, int y);
    
    void set_rect(int x, int y, int w, int h);
    
    void set_xDir(int x);
    
    void set_yDir(int y);
    
    void set_speed(float s);
    
    int get_y();
    
    SDL_Rect get_rect();
    
    Texture getBullet();
    
    ~Enemy_bullet();
};

#endif /* defined(__PlaneGame__Enemy_bullet__) */
