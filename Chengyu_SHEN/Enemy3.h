//
//  Enemy3.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/15/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#ifndef __PlaneGame__Enemy3__
#define __PlaneGame__Enemy3__

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

class Enemy3:public Enemy{
private:
    double _angle;
    SDL_Rect enemy3Rect;
    
    //oop
    Texture enemy3;
    
    
public:
    Enemy3(string filename);
    
    void render();
    
    void move(int x, int y);
    
    SDL_Rect position();
    
    void destroy_tex();
    
    ~Enemy3();
    
};
#endif /* defined(__PlaneGame__Enemy3__) */
