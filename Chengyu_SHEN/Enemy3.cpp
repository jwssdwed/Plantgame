//
//  Enemy3.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/15/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#include "Enemy3.h"

Enemy3::Enemy3(string filename){
    _x=rand()%(SCREEN_WIDTH-60);
    _y=10;
    _width=42;
    _height=85;
    _speed=5;
    health=3;
    value = health*200;
    enemy3 = Texture(filename);
    
    //set enemy's move randomly
    xDir =1;
    yDir=2;
    canShoot=false;
}

void Enemy3::render(){
    enemy3Rect = {_x,_y,_width,_height};
    SDL_Point p = {_width/2, _height/2};
    SDL_RenderCopyEx(gRenderer, enemy3.getTexture(), NULL, &enemy3Rect, -_angle, &p, SDL_FLIP_NONE);
    
}

void Enemy3::move(int x, int y){
    double xDis = x-_x;     //distance between this enemy with target.
    double yDis = y-_y;
    //angle is smaller than 90.
    if (yDis>=0) {
        _angle = atan(xDis/yDis);
        _x += _speed*sin(_angle);
        _y += _speed*cos(_angle);
        _angle = _angle*180/3.14;
    }
    //angle is bigger than 90.
    else{
        _x += _speed*xDir/4;
        _y += _speed*yDir/4;
        _angle = 0;
    }
    
    
}

SDL_Rect Enemy3::position(){
    return enemy3Rect;
}

void Enemy3::destroy_tex(){
    enemy3.~Texture();
    enemy3.free();
    _x=1000;
    _y=1000;
}


Enemy3::~Enemy3(){
    enemy3.free();
}