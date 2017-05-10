//
//  Texture.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/9/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#ifndef __PlaneGame__Texture__
#define __PlaneGame__Texture__

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cmath>
#include <vector>
#include <unistd.h>
#include "GlobalElement.h"

using namespace std;
class Texture{
private:
    SDL_Texture *_texture;
    int _width;
    int _height;
public:
    Texture();
    Texture(string);
    SDL_Texture* loadTexture(string);
    SDL_Texture* getTexture();
    void free();
    ~Texture();
    
};

#endif /* defined(__PlaneGame__Texture__) */
