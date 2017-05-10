//
//  Enemy2.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/10/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#include "Enemy2.h"

Enemy2::Enemy2(string filename, int x, int y, int w, int h, int yDir, int s, int hea, float bullet_s){
    _x=1+rand()%492;
    _y = 5;
    _width = w;
    _height = h;
    this->yDir = yDir;
    _speed = s;
    health = hea;
    value = health*100;
    bullet_speed = bullet_s;
    canShoot=true;
    enemy = Texture(filename);
    
    for (int i=0; i<bullet_amo; i++) {
        
        bullet.push_back(new Enemy_bullet("images/ship_bullet1.png"));
    }
    
    
    int b = 1+rand()%10;
    if (b<=5) {
        xDir=-1;
    }
    else{
        xDir=1;
    }
}

void Enemy2::render(){
    enemy2Rect = {_x,_y,_width,_height};
    //    bullet->render();
    
    SDL_RenderCopy(gRenderer, enemy.getTexture(), NULL, &enemy2Rect);
    
}

void Enemy2::move(int x, int y){
    _y+=_speed*yDir;
    _x+=_speed*xDir;
}

SDL_Rect Enemy2::position(){
    return enemy2Rect;
}

vector<Enemy_bullet*> Enemy2::get_eb(){
    return bullet;
}

void Enemy2::shoot(int x, int y){
    for (int i=0; i<bullet.size(); i++) {
        if (abs(y-_y)<1000) {
            bullet.at(i)->set_x(_x+_width/2);
            bullet.at(i)->set_y(_y+_height);
            bullet.at(i)->set_Dir(x+35, y+44);
            bullet.at(i)->set_speed(bullet_speed);
        }
        
    }
}

void Enemy2::destroy_tex(){
    enemy.~Texture();
    enemy.free();
    _x=2000;
    _y=2000;
    
    
}

Enemy2::~Enemy2(){
    enemy.free();
}