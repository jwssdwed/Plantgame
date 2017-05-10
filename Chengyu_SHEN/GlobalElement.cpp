//
//  GameManage.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/10/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#include "GlobalElement.h"

int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 695;
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
Mix_Music *gMusic = NULL;

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    bool collide = true;
    
    // calculate a rect;
    int aleft = a.x;
    int aright = a.x + a.w;
    int atop = a.y;
    int abottom = a.y + a.h;
    
    // calculate b rect;
    int bleft = b.x;
    int bright = b.x + b.w;
    int btop = b.y;
    int bbottom = b.y + b.h;
    
    if(aleft >= bright) collide = false;
    if(abottom <= btop) collide = false;
    if(aright <= bleft) collide = false;
    if(atop >= bbottom) collide = false;
    
    return collide;
}