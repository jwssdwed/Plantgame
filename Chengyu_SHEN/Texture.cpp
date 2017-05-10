//
//  Texture.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/9/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//



// ----------- CLASSES
#include "Texture.h"
Texture::Texture() {}
Texture::Texture(string filename)
{
    _texture = loadTexture(filename);
}

SDL_Texture* Texture::loadTexture( string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    
    if( loadedSurface == NULL )
    {
        cout << "Error loading image! SDL_image Error: "  << IMG_GetError() << endl;
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            cout << "Error creating texture! SDL Error: " << IMG_GetError() << endl;
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    return newTexture;
}

SDL_Texture* Texture::getTexture()
{
    return _texture;
}

void Texture::free()
{
    if(_texture != NULL)
    {
        SDL_DestroyTexture(_texture);
        _texture = NULL;
    }
}

Texture::~Texture()
{
    //                cout << "Texture destroyed" << endl;
}