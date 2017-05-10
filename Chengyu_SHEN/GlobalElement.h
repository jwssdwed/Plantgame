//
//  GlobalElement.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/23/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#ifndef __PlaneGame__GlobalElement__
#define __PlaneGame__GlobalElement__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include <string>
using namespace std;

// ----------- GLOBALS
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

//the window we need to render.
extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern Mix_Music *gMusic;

extern bool checkCollision(SDL_Rect a, SDL_Rect b);

#endif /* defined(__PlaneGame__GlobalElement__) */
