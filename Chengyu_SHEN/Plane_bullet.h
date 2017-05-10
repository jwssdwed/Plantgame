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
#include "Enemy.h"

#ifndef __PlaneGame__bullet__
#define __PlaneGame__bullet__

class Plane_bullet{
private:
    //bullet
    int _x;
    int _y;
    int yDir;
    int width;
    int height;
    float _speed;
    SDL_Rect bullet_rect;
    Mix_Chunk *boomSound;
    Mix_Chunk *hitSound;
    
    //oop
    Texture bulletImg;
    
public:
    Plane_bullet(string filename, int width, int heigh);
    
    void render();
    
    void set_x(int x);
    
    void set_y(int y);
    
    void set_rect(int x, int y, int w, int h);
    
    int get_x();
    
    int get_y();
    
    SDL_Rect get_rect();
    
    Texture getBullet();
    
    ~Plane_bullet();
};

#endif