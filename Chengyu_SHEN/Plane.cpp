//
//  Plane.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/9/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#include "Plane.h"

Plane::Plane(string filename){
    plantImg = Texture(filename);
    _x = SCREEN_WIDTH/2;
    _y = SCREEN_HEIGHT-70;
    width=70;
    heigh =50;
    _dx = 0;
    _dy = 0;
    score = 0;
    health = 4;
    _speedLimit = 5;
    _friction=0.94f;
    _speedLimit = 5;
    bullet_type = 1;
    
    shootSound = Mix_LoadWAV( "audio/shoot.wav" );
}

void Plane::render(){
    SDL_Rect planeRect = {_x,_y,width,heigh};
    if (bulletImg1.size()>40) {
        for (int i=0; i<20; i++) {
            bulletImg1.at(0)->~Plane_bullet();
//            delete bulletImg1.at(0);
            bulletImg1.erase(bulletImg1.begin());
        }
    }
    
    for (int i = 0; i<bulletImg1.size(); i++) {
        bulletImg1.at(i)->render();
    }
    SDL_RenderCopy(gRenderer, plantImg.getTexture(), NULL, &planeRect);
}

void Plane::shoot(){
    if (bullet_type == 1) {
        bulletImg1.push_back(new Plane_bullet("images/plane_bullet.png", 20, 40));
        //set the bullet position
        bulletImg1.at(bulletImg1.size()-1)->set_x(_x+25);
        bulletImg1.at(bulletImg1.size()-1)->set_y(_y-20);
        Mix_PlayChannel(-1, shootSound, 0);
    }
    else{
        bulletImg1.push_back(new Plane_bullet("images/plane_bullet.png", 15, 40));
        
        //set the bullet position
        bulletImg1.at(bulletImg1.size()-1)->set_x(_x+8);
        bulletImg1.at(bulletImg1.size()-1)->set_y(_y-20);
        
        bulletImg1.push_back(new Plane_bullet("images/plane_bullet.png", 15, 40));
        bulletImg1.at(bulletImg1.size()-1)->set_x(_x+47);
        bulletImg1.at(bulletImg1.size()-1)->set_y(_y-20);
        Mix_PlayChannel(-1, shootSound, 0);
    }
    
}

void Plane::move()
{
    _speed *= _friction;
    if(_speed > _speedLimit) _speed = 5;
    if(_speed < 1) _speed = 0;
    
    _x += _speed * _dx;
    _y += _speed * _dy;
}

void Plane::moveUp(float a){
    _speed=a;
    _dy=-1;
    _dx=0;
}

void Plane::moveDown(float a){
    _speed=a;
    _dy=1;
    _dx=0;
}

void Plane::moveLeft(float a){
    _speed=a;
    _dx=-1;
    _dy=0;
}

void Plane::moveRight(float a){
    _speed = a;
    _dx = 1;
    _dy=0;
}

void Plane::add_score(int a){
    score += a;
}

long Plane::get_score(){
    return  score;
}

void Plane::set_health(int a){
    health = a;
}

int  Plane::get_health(){
    return health;
}

int Plane::get_x(){
    return _x;
}

int Plane::get_y(){
    return _y;
}

void Plane::set_x(int x){
    _x = x;
}

void Plane::set_y(int y){
    _y = y;
}

void Plane::set_bullet(int a){
    bullet_type = a;
}

SDL_Rect Plane::get_rect(){
    SDL_Rect a = {_x, _y, width, heigh};
    return a;
}

vector<Plane_bullet*> Plane::get_bullet(){
    return bulletImg1;
}

Plane::~Plane(){
    plantImg.free();
    cout<<"delete plane"<<endl;
}