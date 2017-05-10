//
//  Property.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/19/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#ifndef __PlaneGame__Property__
#define __PlaneGame__Property__

#include <iostream>
#include <string>
#include <strstream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <cmath>
#include <vector>
#include <unistd.h>
#include <time.h>
#include "GlobalElement.h"
#include "Texture.h"

class Property{
private:
    int _x;
    int _y;
    int width;
    int height;
    int _speed;
    string type;
    
    SDL_Rect propertyRect;
    
    //OOP
    Texture property;
public:
    Property(string filename, string type);
    void render();
    SDL_Rect get_rect();
    void move();
    string get_type();
    ~Property();
    
};

#endif /* defined(__PlaneGame__Property__) */
