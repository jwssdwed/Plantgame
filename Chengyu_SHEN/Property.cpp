//
//  Property.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/19/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#include "Property.h"

//Property has an element called type, which represents the type of object created from Property.
Property::Property(string filename, string type){
    _x = rand()%550;
    _y = 10;
    _speed = 2;
    width = 50;
    height = 49;
    this->type = type;
    property = Texture(filename);
    
}

void Property::render(){
    propertyRect = {_x, _y, width, height};
    SDL_RenderCopy(gRenderer, property.getTexture(), NULL, &propertyRect);
}

SDL_Rect Property::get_rect(){
    return propertyRect;
}

void Property::move(){
    if (_y>700) {
        _speed = 0;
    }
    else{
        _y += _speed;
    }
}

string Property::get_type(){
    return type;
}

Property::~Property(){
    _x = 1000;
    _y = 1000;
    property.free();
}