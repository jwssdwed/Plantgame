//
//  Background.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/9/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#include "Background.h"

Background::Background(string filename){
    backIMG = Texture(filename);
    _x=0;
    _y=0;
    _width=600;
    _height=695;
    _speed=1;
}

void Background::render(){
    move();
    SDL_Rect backRect = {_x,_y,_width, _height};
    
    SDL_RenderCopy(gRenderer, backIMG.getTexture(), NULL, &backRect);
}

void Background::set_y(int y){
    _y=y;
}

int Background::get_y(){
    return _y;
}

void Background::move(){
    _y += _speed;
}

Background::~Background(){
    backIMG.free();
}