//
//  Enemy.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/9/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//
#include "Enemy.h"

//    virtual void checkCollision();

void Enemy::render(){
}

void Enemy::move(int x, int y){
    //    cout<<"forth one move"<<endl;
}

SDL_Rect Enemy::position(){
    return rect;
}

void Enemy::shoot(int x, int y){
    
}

vector<Enemy_bullet*> Enemy::get_eb(){
    vector<Enemy_bullet* > a;
    return a;
}

int Enemy::get_health(){
    return health;
}

int Enemy::get_value(){
    return value;
}

void Enemy::set_health(int a){
    health = a;
}

void Enemy::destroy_tex(){
    cout<<"destroy enemy"<<endl;
    _x = 1000;
    _y = 1000;
    enemy.free();
}