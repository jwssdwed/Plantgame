//
//  Boss1.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/11/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#include "Boss1.h"

Boss1::Boss1(string filename){
    _x=100;
    _y=10;
    _width=380;
    _height=290;
    _speed=1;
    health=50;
    bullet_amo=5;
    last_shoot = 0;
    canShoot=true;
    enemy = Texture(filename);
    value = health*100;
    //set enemy's move randomly
    
    xDir = 1;
    yDir=1;
}

void Boss1::render(){
    enemy1Rect = {_x,_y,_width,_height};
    //    bullet->render();
    
    SDL_RenderCopy(gRenderer, enemy.getTexture(), NULL, &enemy1Rect);
    
}

void Boss1::move(int x, int y){
    if (_x<=0||_x>=200) {
        xDir = -xDir;
    }
    _x+=_speed*xDir;
}

SDL_Rect Boss1::position(){
    return enemy1Rect;
}

vector<Enemy_bullet*> Boss1::get_eb(){
    return bullet;
}

void Boss1::shoot(int x, int y){
    
    for (int i=last_shoot; i<bullet_amo+last_shoot; i++) {
        bullet.push_back(new Enemy_bullet("images/ship_bullet1.png"));
        int which_bullet = i % bullet_amo;
        switch (which_bullet) {
            case 0:
                bullet.at(i)->set_x(_x);
                bullet.at(i)->set_y(_y+_height-50);
                bullet.at(i)->set_xDir(-200);
                bullet.at(i)->set_yDir(400);
                break;
            case 1:
                bullet.at(i)->set_x(_x+100);
                bullet.at(i)->set_y(_y+_height-30);
                bullet.at(i)->set_xDir(-200);
                bullet.at(i)->set_yDir(400);
                break;
            case 2:
                bullet.at(i)->set_x(_x+200);
                bullet.at(i)->set_y(_y+_height);
                bullet.at(i)->set_xDir(0);
                bullet.at(i)->set_yDir(400);
                break;
            case 3:
                bullet.at(i)->set_x(_x+300);
                bullet.at(i)->set_y(_y+_height-30);
                bullet.at(i)->set_xDir(200);
                bullet.at(i)->set_yDir(400);
                break;
            case 4:
                bullet.at(i)->set_x(_x+400);
                bullet.at(i)->set_y(_y+_height-50);
                bullet.at(i)->set_xDir(200);
                bullet.at(i)->set_yDir(400);
            default:
                break;
        }
    }
    last_shoot += bullet_amo;
    
    
}

int Boss1::get_last_shoot(){
    return last_shoot;
}

void Boss1::destroy_tex(){
    enemy.~Texture();
    enemy.free();
    _x=1000;
    _y=1000;
}

Boss1::~Boss1(){
    enemy.free();
}