#include <iostream>
#include <string>
#include <strstream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <cmath>
#include <vector>
#include <unistd.h>
#include <time.h>
#include "GlobalElement.h"
#include "Texture.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Plane_bullet.h"
#include "Background.h"
#include "Plane.h"
#include "Boss1.h"
#include "Property.h"
#include "GameManage.h"
#include "Button.h"

using namespace std;

// ----------- PROTOTYPES
bool init();

// ----------- SDL events
bool quit = false;
bool start = false;
bool next_task = false;
SDL_Event e;

int main(int, char **){
    srand((signed)time(NULL));
    
    if (!init()) {
        cout <<"Couldn't initialize SDL environment"<<endl;
    }
    else{
        //load background music
        gMusic = Mix_LoadMUS( "audio/music2.WAV" );
        
        if(gMusic == NULL){
            cout << "Failed to load background music: " << Mix_GetError() << endl;
        }
        
        
        cout<<"Begin game"<<endl;
        
        GameManage gm;
        
        Button *start_button = new Button(174,256,252,60, "images/game_start1_1.png");
        SDL_Rect start_position = start_button->get_rect();
        
        Button *exit_button = new Button(174,376,252,60, "images/game_end1_1.png");
        SDL_Rect exit_position = exit_button->get_rect();
        Texture black("images/black.png");
        
        //open page.
        while (!quit&&!start){
            
            if( Mix_PlayingMusic() == 0 )
            {
                Mix_PlayMusic(gMusic, -1); //Play the music
            }
            
            SDL_RenderClear(gRenderer);
            gm.background_system();
            
            SDL_Rect black_rect = {0,0,600,695};
            SDL_RenderCopy(gRenderer, black.getTexture(), nullptr, &black_rect);
            
            start_button->render();
            exit_button->render();
            
            while (SDL_PollEvent(&e)!=0) {
                if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                    int x,y;
                    SDL_GetMouseState(&x, &y);
                    switch (e.type) {
                        case SDL_MOUSEMOTION:
                            if (x>=start_button->get_rect().x&&x<=start_button->get_rect().x+start_position.w&&y>=start_button->get_rect().y&&y<=start_button->get_rect().y+start_position.h) {
                                start_button->set_image("images/game_start1_1_1.png");
                            }
                            if (x<=start_button->get_rect().x||x>=start_button->get_rect().x+start_position.w||y<=start_button->get_rect().y||y>=start_button->get_rect().y+start_position.h) {
                                //here is check whether we need to change picture
                                if (start_button->get_image() == "images/game_start1_1_1.png") {
                                    start_button->set_image("images/game_start1_1.png");
                                }
                            }
                            if (x>=exit_position.x&&x<=exit_position.x+exit_position.w&&y>=exit_position.y&&y<=exit_position.y+exit_position.h) {
                                exit_button->set_image("images/game_end1_1_1.png");
                            }
                            if (x<=exit_position.x||x>=exit_position.x+exit_position.w||y<=exit_position.y||y>=exit_position.y+exit_position.h) {
                                //here is check whether we need to change picture
                                if (exit_button->get_image() == "images/game_end1_1_1.png") {
                                    exit_button->set_image("images/game_end1_1.png");
                                }
                            }
                            break;
                            
                        case SDL_MOUSEBUTTONUP:
                            if (x>=start_button->get_rect().x&&x<=start_button->get_rect().x+start_position.w&&y>=start_button->get_rect().y&&y<=start_button->get_rect().y+start_position.h) {
                                start = true;
                            }
                            if (x>=exit_position.x&&x<=exit_position.x+exit_position.w&&y>=exit_position.y&&y<=exit_position.y+exit_position.h) {
                                quit = true;
                            }
                            break;
                            
                        default:
                            break;
                    }
                }
            }
            
            SDL_Delay(7);
            SDL_RenderPresent(gRenderer);
        }
        
        
        Plane *plane = new Plane("images/ship1.png");
        
        cout<<"Create player at "<< plane->get_x()<<", "<<plane->get_y()<< endl;
        int x= plane->get_x();
        int y= plane->get_y();
        
        Mix_FreeMusic(gMusic);
        gMusic = Mix_LoadMUS( "audio/_www.mp3" );
        
        gm.start_game();
        //level 1
        while (!quit&&!next_task) {
            //clean the screen
            SDL_RenderClear(gRenderer);
            gm.background_system();
            
            while (SDL_PollEvent(&e)!=0) {
                if (e.type==SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit=true;
                            break;
                        case SDLK_UP:
                            if (y>=0) {
                                plane->moveUp(6);
                            }
                            break;
                        case SDLK_DOWN:
                            if (y<=SCREEN_HEIGHT-70) {
                                plane->moveDown(6);
                            }
                            break;
                        case SDLK_RIGHT:
                            if (x<=SCREEN_WIDTH-61){
                                plane->moveRight(6);
                            }
                            break;
                        case SDLK_LEFT:
                            if (x>=15) {
                                plane->moveLeft(6);
                            }
                            break;
                        case SDLK_SPACE:
                            plane->shoot();
                        default:
                            break;
                    }
                }
            }
            
            plane->move();
            x= plane->get_x();
            y= plane->get_y();
            
            //check every enemy motivation, including whether shooting or not, move..
            gm.check_all_enemy_motivation(plane,&quit, &next_task);
            
            //check whether the enemys' bullets hit the plane
            gm.check_plane_all_enemyBullet(plane, &quit);
            
            //check property
            gm.check_property_plane(plane);
            
            //enemy system
            gm.enemy_system(plane);
            
            plane->render();
            gm.render();
            SDL_Delay(9);
            
            SDL_RenderPresent(gRenderer);
            
        }
        
        //level 2
        gm.start_game();
        if (next_task){
            SDL_RenderClear(gRenderer);
            Texture round2("images/round2.png");
            SDL_Rect round_rect = {23, 210, 554, 274};
            SDL_RenderCopy(gRenderer, round2.getTexture(), NULL, &round_rect);
            SDL_RenderPresent(gRenderer);
            SDL_Delay(3000);
            round2.free();
            
            Mix_FreeMusic(gMusic);
            gMusic = Mix_LoadMUS( "audio/Pacific Rim Theme Epic Rock.mp3" );
            gm.start_game();
            plane->set_x(SCREEN_WIDTH/2);
            plane->set_y(SCREEN_HEIGHT-70);
            
            while (!quit&&next_task) {
                //clean the screen
                SDL_RenderClear(gRenderer);
                gm.background2_system();
                
                while (SDL_PollEvent(&e)!=0) {
                    if (e.type==SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_ESCAPE:
                                quit=true;
                                break;
                            case SDLK_UP:
                                if (y>=0) {
                                    plane->moveUp(6);
                                }
                                break;
                            case SDLK_DOWN:
                                if (y<=SCREEN_HEIGHT-70) {
                                    plane->moveDown(6);
                                }
                                break;
                            case SDLK_RIGHT:
                                if (x<=SCREEN_WIDTH-61){
                                    plane->moveRight(6);
                                }
                                break;
                            case SDLK_LEFT:
                                if (x>=15) {
                                    plane->moveLeft(6);
                                }
                                break;
                            case SDLK_SPACE:
                                plane->shoot();
                            default:
                                break;
                        }
                    }
                }
                
                plane->move();
                x= plane->get_x();
                y= plane->get_y();
                
                //check every enemy motivation, including whether shooting or not, move..
                gm.check_all_enemy_motivation(plane,&quit, &next_task);
                
                //check whether the enemys' bullets hit the plane
                gm.check_plane_all_enemyBullet(plane, &quit);
                
                //check property
                gm.check_property_plane(plane);
                
                //enemy system
                gm.enemy_system(plane);
                //
                plane->render();
                gm.render();
                SDL_Delay(9);
                
                SDL_RenderPresent(gRenderer);
            }
        }
        
        start = false;
        Mix_FreeMusic(gMusic);
        gMusic = Mix_LoadMUS("audio/wow_success.wav");
        Mix_PlayMusic(gMusic, 0); //Play the music
        
        char* str_score;
        SDL_Texture * fontText;
        SDL_Texture * fontText_help;
        SDL_Surface *text;
        TTF_Font *font;
        SDL_Color texColor;
        texColor = {255,215,0};
        
        stringstream ss_score;
        str_score = const_cast<char*>(ss_score.str().c_str());
        long score = plane->get_score();
        long score_dup = score;
        int i = 1;
        while ((int)(score_dup/pow(10,i))!=0){
            i++;
        }
        
        //final font system
        font=TTF_OpenFont("fonts/lazy.ttf", 16);
        if(!font)
        {
            printf("TTF_OpenFont: Open simsun.ttf %s\n", TTF_GetError());
            exit(1);
            
        }
        
        SDL_Rect textRect_score_help  = {(SCREEN_WIDTH-20*i-120)/2, 270,120,50};
        
        text = TTF_RenderUTF8_Solid(font,"Score: ",texColor);
        
        fontText_help = SDL_CreateTextureFromSurface( gRenderer, text);
        
        SDL_FreeSurface(text);
        
        ss_score<<score;
        str_score = const_cast<char*>(ss_score.str().c_str());              //change const to non-const.
        SDL_Rect textRect_score  = {(SCREEN_WIDTH-20*i-120)/2+120,270,20*i,50};
        
        text = TTF_RenderUTF8_Solid(font,str_score,texColor);
        
        fontText = SDL_CreateTextureFromSurface( gRenderer, text);
        
        SDL_FreeSurface(text);
        
        //show score, and exit game
        while(!quit&&!start){
            SDL_RenderClear(gRenderer);
            gm.background2_system();
            
            SDL_Rect black_rect = {0,0,600,695};
            SDL_RenderCopy(gRenderer, black.getTexture(), nullptr, &black_rect);
            
            exit_button->render();
            
            while (SDL_PollEvent(&e)!=0) {
                if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                    int x,y;
                    SDL_GetMouseState(&x, &y);
                    switch (e.type) {
                        case SDL_MOUSEMOTION:
                            
                            if (x>=exit_position.x&&x<=exit_position.x+exit_position.w&&y>=exit_position.y&&y<=exit_position.y+exit_position.h) {
                                exit_button->set_image("images/game_end1_1_1.png");
                            }
                            if (x<=exit_position.x||x>=exit_position.x+exit_position.w||y<=exit_position.y||y>=exit_position.y+exit_position.h) {
                                //here is check whether we need to change picture
                                if (exit_button->get_image() == "images/game_end1_1_1.png") {
                                    exit_button->set_image("images/game_end1_1.png");
                                }
                            }
                            break;
                            
                        case SDL_MOUSEBUTTONUP:
                            if (x>=exit_position.x&&x<=exit_position.x+exit_position.w&&y>=exit_position.y&&y<=exit_position.y+exit_position.h) {
                                quit = true;
                            }
                            break;
                            
                        default:
                            break;
                    }
                }
            }
            
            SDL_Delay(7);
            SDL_RenderCopy(gRenderer, fontText_help, NULL, &textRect_score_help);
            SDL_RenderCopy(gRenderer, fontText, NULL, &textRect_score);
            SDL_RenderPresent(gRenderer);
        }
        
        
        //clean all the elements
        start_button->~Button();
        exit_button->~Button();
        
        plane->~Plane();
        for(int i = 0; i<plane->get_bullet().size(); i++){
            delete plane->get_bullet().at(i);
        }
        
        TTF_CloseFont(font);
        gm.cleanup();
        SDL_Quit();
    }
    
}

bool init()
{
    cout << "---- init SDL ----" << endl;
    
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow(
                                   "Plane Game",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH,
                                   SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN
                                   );
        
        if( gWindow == NULL )
        {
            cout <<  "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            //Get window surface
            gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
        }
        
        //Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
            success = false;
        }
        if( TTF_Init() == -1 )
            return -1;
        
    }
    return success;
}




