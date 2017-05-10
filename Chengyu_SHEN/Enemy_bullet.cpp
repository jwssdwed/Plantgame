//
//  Plane_bullet.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/9/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#include "Enemy_bullet.h"

Enemy_bullet::Enemy_bullet(string filename){
    bulletImg = Texture(filename);
}

void Enemy_bullet::render(){
    _y += _speed*yDir;
    _x += _speed*xDir;
    
    //bullet is out of screen
    if (_y<=0) {
        _y=1000;
        _speed = 0;
    }
    if (_x<=0) {
        _x=1000;
        _speed = 0;
    }
    
    bullet_rect = {_x,_y,width,height};
    
    SDL_RenderCopy(gRenderer, bulletImg.getTexture(), NULL, &bullet_rect);
}


void Enemy_bullet::set_x(int x){
    _x = x;
}

void Enemy_bullet::set_y(int y){
    _y = y;
}

void Enemy_bullet::set_Dir(int x, int y){
    xDir=x-_x;
    yDir=y-_y;
    
}

void Enemy_bullet::set_xDir(int x){
    xDir = x;
}

void Enemy_bullet::set_yDir(int y){
    yDir = y;
}

void Enemy_bullet::set_rect(int x, int y, int w, int h){
    bullet_rect = {x,y,w,h};
}

int Enemy_bullet::get_y(){
    return _y;
}

void Enemy_bullet::set_speed(float s){
    _speed = s;
}

SDL_Rect Enemy_bullet::get_rect(){
    return bullet_rect;
}

Texture Enemy_bullet::getBullet(){
    return bulletImg;
}

Enemy_bullet::~Enemy_bullet(){
    bulletImg.free();
}
