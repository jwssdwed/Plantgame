//
//  Plane.h
//  PlaneGame
//
//  Created by Shen Chengyu on 4/9/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#ifndef __PlaneGame__Plane__
#define __PlaneGame__Plane__
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <vector>
#include "GlobalElement.h"
#include "Texture.h"
#include "Plane_bullet.h"

class Plane{
private:
    //guard
    int _x;
    int _y;
    int width;
    int heigh;
    float _speed;
    float _friction;
    int _dx;
    int _dy;
    float _speedLimit;
    long score;
    int health;
    int bullet_type;
    
    Mix_Chunk *shootSound;
    
    //oop
    Texture plantImg;
    vector<Plane_bullet*> bulletImg1;
    
public:
    Plane(string filename);
    
    void render();
    
    void shoot();
    
    void move();
    
    void moveUp(float a);
    void moveDown(float a);
    void moveLeft(float a);
    void moveRight(float a);
    
    int get_x();
    
    int get_y();
    
    void set_x(int x);
    
    void set_y(int y);
    
    void set_bullet(int a);
    
    void add_score(int a);
    
    long get_score();
    
    void set_health(int a);
    
    int get_health();
    
    SDL_Rect get_rect();
    
    vector<Plane_bullet*> get_bullet();
    
    ~Plane();
};

#endif /* defined(__PlaneGame__Plane__) */
