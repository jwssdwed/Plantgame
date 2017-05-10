//
//  Button.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/27/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#include "Button.h"

Button::Button(int x, int y, int w, int h, string path){
    _x = x;
    _y = y;
    _width = w;
    _height = h;
    buttonImg = Texture(path);
    par = path;
    
    button_rect = {_x, _y, _width, _height};
}

//change button's image
void Button::set_image(string path){
    buttonImg = Texture(path);
    par = path;
}

string Button::get_image(){
    return  par;
}

void Button::render(){
    button_rect = {_x, _y, _width, _height};
    
    SDL_RenderCopy(gRenderer, buttonImg.getTexture(), NULL, &button_rect);
}

SDL_Rect Button::get_rect(){
    return button_rect;
}

Button::~Button(){
    buttonImg.free();
}