//
//  Button.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/27/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#ifndef __PlaneGame__Button__
#define __PlaneGame__Button__

#include <stdio.h>
#include <iostream>
#include <string>
#include <strstream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "GlobalElement.h"
#include "Texture.h"

class Button{
private:
    int _x;
    int _y;
    int _width;
    int _height;
    SDL_Rect button_rect;
    
    string par;
    
    //oop
    Texture buttonImg;
    
public:
    Button(int x, int y, int w, int h, string path);
    
    void set_image(string path);
    
    string get_image();
    
    SDL_Rect get_rect();
    
    void render();
    
    ~Button();
};
#endif /* defined(__PlaneGame__Button__) */
