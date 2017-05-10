//
//  Enemy1.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/9/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#include "Enemy1.h"

Enemy1::Enemy1(string filename){
    srand((unsigned)time(NULL));
    
    _x=rand()%(SCREEN_WIDTH-60);
    _y=10;
    _width=65;
    _height=44;
    _speed=2;
    health=1;
    value = health*100;
    canShoot=false;
    enemy1 = Texture(filename);
    
    //set enemy's move randomly
    int b = 1+rand()%10;
    if (b<=5) {
        xDir=-rand()%3;
    }
    else{
        xDir=rand()%3;
    }
    yDir=2+rand()%2;
}

void Enemy1::render(){
    enemy1Rect = {_x,_y,_width,_height};
    
    SDL_RenderCopy(gRenderer, enemy1.getTexture(), NULL, &enemy1Rect);
    
}

void Enemy1::move(int x, int y){
    _y+=_speed*yDir;
    _x+=_speed*xDir;
    if (_x<=0||_x>=600) {
        srand((unsigned)time(nullptr));
        double turn = rand()%5;
        if (turn>=3) {
            xDir=-xDir;
        }
    }
}

SDL_Rect Enemy1::position(){
    return enemy1Rect;
}

void Enemy1::destroy_tex(){
    enemy1.free();
    _x=1000;
    _y=1000;
}

Enemy1::~Enemy1(){
    enemy1.free();
}