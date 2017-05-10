//
//  Plane_bullet.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/9/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#include "Plane_bullet.h"

Plane_bullet::Plane_bullet(string filename, int width, int height){
    _x=10;
    _y=100;
    yDir = -1;
    this->width = width;
    this->height = height;
    _speed=7;
    bulletImg = Texture(filename);
    hitSound = Mix_LoadWAV("audio/boom1.wav");
    boomSound = Mix_LoadWAV("audio/hit.wav");
}

void Plane_bullet::render(){
    _y +=_speed*yDir;
    bullet_rect = {_x,_y,width,height};
    SDL_RenderCopy(gRenderer, bulletImg.getTexture(), NULL, &bullet_rect);
}

void Plane_bullet::set_x(int x){
    _x = x;
}

void Plane_bullet::set_y(int y){
    _y = y;
}

void Plane_bullet::set_rect(int x, int y, int w, int h){
    bullet_rect = {x,y,w,h};
}

int Plane_bullet::get_x(){
    return _x;
}

int Plane_bullet::get_y(){
    return _y;
}

SDL_Rect Plane_bullet::get_rect(){
    return bullet_rect;
}

Texture Plane_bullet::getBullet(){
    return bulletImg;
}

Plane_bullet::~Plane_bullet(){
    bulletImg.free();
}

