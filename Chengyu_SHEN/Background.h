//
//  Background.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/9/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#ifndef __PlaneGame__Background__
#define __PlaneGame__Background__
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <SDL2_mixer/SDL_mixer.h>
#include "GlobalElement.h"
#include "Texture.h"

class Background{
private:
    int _x;
    int _y;
    int _width;
    int _height;
    double _speed;
    
    Texture backIMG;
public:
    Background(string filename);
    
    void render();
    
    void set_y(int y);
    
    void move();
    
    int get_y();
    
    ~Background();
};
#endif /* defined(__PlaneGame__Background__) */
