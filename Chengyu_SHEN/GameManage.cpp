//
//  GameManage.cpp
//  PlaneGame
//
//  Created by Shen Chengyu on 4/23/15.
//  Copyright (c) 2015 Shen Chengyu. All rights reserved.
//

#include "GameManage.h"

GameManage::GameManage(){
    hitSound = Mix_LoadWAV("audio/boom1.wav");
    boomSound = Mix_LoadWAV("audio/hit.wav");
    plane_boom_Sound = Mix_LoadWAV("audio/wave.wav");
    round = 1;
    level = 1;
    boss = 1000;
    boss_last_shoot = 0;
    
    textRect_health_help = {60,20,15,30};
    
    bossWarning = new Texture("images/th.png");
    hp = new Texture("images/heart.png");
    black_background = new Texture("images/black.png");
    
    background1 = new Background("images/background3.png");
    background2 = new Background("images/background3.png");
    background3 = new Background("images/background1.png");
    background4 = new Background("images/background1.png");
    background2->set_y(-695);
    background4->set_y(-695);
    
    bomb = Texture("images/bomb.jpg");
    boom1 = Texture("images/boom1.png");
    boom2 = Texture("images/boom2.png");
    
    enemy_man.push_back(new Enemy());
    
    //font
    font=TTF_OpenFont("fonts/lazy.ttf", 16);
    if(!font)
    {
        printf("TTF_OpenFont: Open simsun.ttf %s\n", TTF_GetError());
        exit(1);
        
    }
    
    texColor = {255,215,0};
    text = TTF_RenderUTF8_Solid(font,"0",texColor);
    
    fontText = SDL_CreateTextureFromSurface( gRenderer, text );
    if( fontText == NULL )
    {
        cout << "Error creating texture! SDL Error: "<< endl;
    }
    
    stringstream ss_score;
    ss_score<<0;
    str_score = const_cast<char*>(ss_score.str().c_str());
    textRect_score  = {550-20,20,20,50};
    
    text = TTF_RenderUTF8_Solid(font,str_score,texColor);
    
    fontText = SDL_CreateTextureFromSurface( gRenderer, text);
    
    SDL_FreeSurface(text);
    
    ss_health<<4;
    str_health = const_cast<char*>(ss_health.str().c_str());
    
    textRect_health = {80,20,15*2,30};
    
    text_health = TTF_RenderUTF8_Solid(font,str_health,texColor);
    text_health_help = TTF_RenderUTF8_Solid(font,str_health_help,texColor);
    
    fontText_health = SDL_CreateTextureFromSurface( gRenderer, text_health);
    fontText_health_help = SDL_CreateTextureFromSurface( gRenderer, text_health_help);
    
    SDL_FreeSurface(text_health);
    SDL_FreeSurface(text_health_help);
}

//init
void GameManage::start_game(){
    for (int i=0; i<6; i++) {
        ship[i] = true;
        bullet[i] = true;
    }
    start=clock();
    finish=clock();
}

void GameManage::render(){
    
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic(gMusic, -1); //Play the music
    }
    
    SDL_Rect heart = {20, 20, 30, 30};
    SDL_RenderCopy(gRenderer, hp->getTexture(), NULL, &heart);
    
    //enemy's bullets rubbish bin
    if (enemy_bullet.size()>25) {
        for (int i=0; i<10; i++) {
            delete enemy_bullet.at(0);
            enemy_bullet.erase(enemy_bullet.begin());
        }
    }
    
    //enemy rubbish bin
    int enemy_amo = (int) enemy_man.size();
    if (enemy_amo>15) {
        //not delete from begin own to boss;
        for (int i = 1; i<7; i++) {
            delete enemy_man.at(1);
            enemy_man.erase(enemy_man.begin()+1);
        }
    }
    
    //render all enemies
    for (int i = 0; i<enemy_man.size(); i++) {
        enemy_man.at(i)->render();
    }
    for (int i=0; i<enemy_bullet.size(); i++) {
        enemy_bullet.at(i)->render();
    }
    if (property!=NULL) {
        property->move();
        property->render();
    }
    
    
    SDL_RenderCopy(gRenderer, fontText, NULL, &textRect_score);
    
    SDL_RenderCopy(gRenderer, fontText_health, NULL, &textRect_health);
    SDL_RenderCopy(gRenderer, fontText_health_help, NULL, &textRect_health_help);
}

void GameManage::check_all_enemy_motivation( Plane *plane, bool *quit, bool *next){
    int enemy_amo = (int)enemy_man.size();
    for (int i=0; i<enemy_amo; i++) {
        if (enemy_man.at(i)->position().x<=-300||enemy_man.at(i)->position().x>=600||enemy_man.at(i)->position().y>=695) {
            enemy_man.at(i)->destroy_tex();
        }
        else{
            enemy_man.at(i)->move(plane->get_x(),plane->get_y());
            
            //check whether the plane's bullets hit this enemy
            check_enemy_each_planeBullet(plane->get_bullet(), enemy_man.at(i), i, next, plane);
            
            //player and enemy collide.
            if (i!=0||boss!=0) {
                if (check_each_enemy_plane_hit(enemy_man.at(i), plane)) {
                    //continue page
                    continue_game(quit);
                    //init
                    plane->set_health(3);
                    plane->set_bullet(1);
                    health_system(plane);
                }
            }
            
            //specially, check collision with boss
            else{
                if(checkCollision(plane->get_rect(), enemy_man.at(0)->position())){
                    Mix_PlayChannel(-1, plane_boom_Sound, 0);
                    plane->set_health(plane->get_health()-1);
                    boom_visual(plane->get_rect(), enemy_man.at(0)->position());
                    //continue page
                    continue_game(quit);
                    //init
                    plane->set_health(3);
                    plane->set_bullet(1);
                    health_system(plane);
                    plane->set_x(SCREEN_WIDTH/2);
                    plane->set_y(SCREEN_HEIGHT-70);
                    
                }
            }
            
        }
    }
}

void GameManage::check_plane_all_enemyBullet(Plane *plane, bool *quit){
    for (int i=0; i<enemy_bullet.size(); i++) {
        enemy_bullet.at(i)->render();
        if (check_plane_each_enemyBullet(enemy_bullet.at(i), plane)) {
            //continue page
            continue_game(quit);
            plane->set_health(3);
            plane->set_bullet(1);
            health_system(plane);
        }
    }
}

//check collision between enemy and plane's bullets
void GameManage::check_enemy_each_planeBullet(vector<Plane_bullet *> plane_bullet, Enemy * enemy, int index,bool *next, Plane *plane){
    for (int i = 0; i<plane_bullet.size(); i++) {
        if(checkCollision(plane_bullet.at(i)->get_rect(), enemy->position())){
            enemy->set_health(enemy->get_health()-1);
            
            if (enemy->get_health()==0) {
                plane->add_score(enemy->get_value());
                
                score_system(plane);
                //destory the enemy
                enemy->destroy_tex();
                Mix_PlayChannel(-1, boomSound, 0);
                SDL_Rect boom = {enemy->position().x,enemy->position().y,50,50};
                boom = {enemy->position().x,enemy->position().y,80,80};
                SDL_RenderCopy(gRenderer, boom1.getTexture(), NULL, &boom);
                boom = {enemy->position().x,enemy->position().y,105,105};
                SDL_RenderCopy(gRenderer, boom2.getTexture(), NULL, &boom);
                
                //this bullet is useless
                plane_bullet.at(i)->set_x(-100);
                plane_bullet.at(i)->set_y(-100);
                plane_bullet.at(i)-> set_rect(-100,-100, 0, 0);
                plane_bullet.at(i)->getBullet().~Texture();
                plane_bullet.at(i)->getBullet().free();
                //boss was dead
                if (index==0&&boss==0) {
                    enemy_bullet.clear();
                    int size = (int)enemy_man.size();
                    for (int k = 0; k<size; k++) {
                        enemy_man.at(k)->destroy_tex();
                    }
                    size = (int)plane->get_bullet().size();
                    for (int k = 0; k<size; k++) {
                        plane->get_bullet().at(k)->getBullet().free();
                        plane->get_bullet().at(k)->set_x(-100);
                        plane->get_bullet().at(k)->set_y(-100);
                    }
                    *next = !(*next);
                    boss = 1000;
                    boss_last_shoot = 0;
                    round = 1;
                    level = 2;
                    Mix_FreeMusic(gMusic);
                    gMusic = Mix_LoadMUS( "audio/Success.wav" );
                    Mix_PlayMusic(gMusic, 0); //Play the music
                }
            }
            else{
                Mix_PlayChannel(-1, hitSound, 0);
                SDL_Rect boom = {plane_bullet.at(i)->get_x(),plane_bullet.at(i)->get_y()-30,60,60};
                SDL_RenderCopy(gRenderer, boom1.getTexture(), NULL, &boom);
                
                //this bullet is useless
                plane_bullet.at(i)->set_x(-100);
                plane_bullet.at(i)->set_y(-100);
                plane_bullet.at(i)->set_rect(-100,-100, 0, 0);
                plane_bullet.at(i)->getBullet().~Texture();
                plane_bullet.at(i)->getBullet().free();
            }
        }
    }
}

//check collision between enemy and plane
bool GameManage::check_each_enemy_plane_hit(Enemy * enemy, Plane *plane){
    bool a = false;
    if(checkCollision(plane->get_rect(), enemy->position())){
        Mix_PlayChannel(-1, plane_boom_Sound, 0);
        // destory both enemy and plane.
        plane->set_health(plane->get_health()-1);
        int health=plane->get_health();
        health_system(plane);
        if (health!=0) {
            //the enemy doesn't exist.
            enemy->destroy_tex();
            
            boom_visual(plane->get_rect(), enemy->position());
        }
        else{
            enemy->destroy_tex();
            
            //destory visual effect.
            boom_visual(plane->get_rect(), enemy->position());
            
            //return true
            a = true;
        }
    }
    return a;
}

//check collision between plane and enemies' bullets
bool GameManage::check_plane_each_enemyBullet(Enemy_bullet * enemy_bullet, Plane *plane){
    bool a = false;
    if (checkCollision(enemy_bullet->get_rect(),plane->get_rect())) {
        Mix_PlayChannel(-1, plane_boom_Sound, 0);
        plane->set_health(plane->get_health()-1);
        int health=plane->get_health();
        health_system(plane);
        if (health!=0) {
            //this bullet is useless
            enemy_bullet->set_x(1000);
            enemy_bullet->set_y(1000);
            enemy_bullet->set_speed(0);
            enemy_bullet->set_rect(1000, 1000, 0, 0);
            enemy_bullet->getBullet().~Texture();
            enemy_bullet->getBullet().free();
            boom_visual(plane->get_rect(), enemy_bullet->get_rect());
        }
        else{
            boom_visual(plane->get_rect(), enemy_bullet->get_rect());
            enemy_bullet->getBullet().~Texture();
            enemy_bullet->getBullet().free();
            
            boom_visual(plane->get_rect(), enemy_bullet->get_rect());
            
            //clean all the elements
            a = true;
        }
    }
    return a;
}

//check whether player gets property.
void GameManage::check_property_plane(Plane *plane ){
    if (property!=NULL) {
        if (checkCollision(property->get_rect(), plane->get_rect())) {
            property->~Property();
            if (property->get_type()=="hp") {
                plane->set_health(plane->get_health()+1);
                health_system(plane);
            }
            else{
                plane->set_bullet(2);
            }
        }
        
    }
}

void GameManage::enemy_system(Plane *plane){
    
    if (round==6) {
        //clean all enemys before boss.
        int amount = (int)enemy_man.size();
        
        //Enemy bullet rubbish bin
        for (int j=0; j<amount; j++) {
            delete enemy_man.at(0);
            enemy_man.erase(enemy_man.begin());
        }
        
        enemy_man.push_back(new Boss1("images/boss.png"));
        boss = enemy_man.size()-1;
        enemy_man.at(boss)->shoot(plane->get_x(), plane->get_y());
        for (int j=boss_last_shoot; j<enemy_man.at(boss)->get_eb().size(); j++) {
            enemy_bullet.push_back(enemy_man.at(boss)->get_eb().at(j));
        }
        boss_last_shoot += 5;
        round++;
    }
    
    finish=clock();
    if (round!=5) {
        //boss shoot
        if ((finish-start)>=200000&&enemy_man.size()-1>=boss&&bullet[1]) {
            enemy_man.at(boss)->shoot(plane->get_x(), plane->get_y());
            for (int j=boss_last_shoot; j<enemy_man.at(boss)->get_eb().size(); j++) {
                enemy_bullet.push_back(enemy_man.at(boss)->get_eb().at(j));
            }
            boss_last_shoot += 5;
            bullet[1]=false;
        }
        //boss shoot
        if ((finish-start)>=700000&&enemy_man.size()-1>=boss&&bullet[2]) {
            enemy_man.at(boss)->shoot(plane->get_x(), plane->get_y());
            for (int j=boss_last_shoot; j<enemy_man.at(boss)->get_eb().size(); j++) {
                enemy_bullet.push_back(enemy_man.at(boss)->get_eb().at(j));
            }
            boss_last_shoot += 5;
            bullet[2]=false;
        }
        if ((finish-start)>=100000&&ship[0]) {
            enemy_man.push_back(new Enemy1("images/enemy1-1.png"));
            ship[0]=false;
        }
        if ((finish-start)>=300000&&ship[1]) {
            enemy_man.push_back(new Enemy1("images/enemy1-2.png"));
            ship[1]=false;
        }
        if ((finish-start)>=500000&&ship[2]) {
            enemy_man.push_back(new Enemy2("images/enemy2-1.png", 0, 0, 108, 80, 2, 1, 5, 0.00501));
            ship[2]=false;
        }
        
        //enemy2 shoot and add a enemy 1
        if ((finish-start)>=550000&&bullet[3]) {
            enemy_man.at(enemy_man.size()-1)->shoot(plane->get_x()+35,plane->get_y()+20);
            for (int j=0; j<enemy_man.at(enemy_man.size()-1)->get_eb().size(); j++) {
                enemy_bullet.push_back(enemy_man.at(enemy_man.size()-1)->get_eb().at(j));
            }
            
            enemy_man.push_back(new Enemy1("images/enemy1-1.png"));
            bullet[3]=false;
        }
        
        //another type of enemy2
        if ((finish-start)>=650000&&ship[4]) {
            enemy_man.push_back(new Enemy2("images/enemy2-2.png", 0, 0, 162, 113, 2, 1, 7, 0.007));
            ship[4]=false;
            
        }
        
        //above type shoot and add a enemy 1
        if ((finish-start)>=750000&&bullet[4]) {
            enemy_man.at(enemy_man.size()-1)->shoot(plane->get_x()+35,plane->get_y()+20);
            for (int j=0; j<enemy_man.at(enemy_man.size()-1)->get_eb().size(); j++) {
                enemy_bullet.push_back(enemy_man.at(enemy_man.size()-1)->get_eb().at(j));
            }
            
            enemy_man.push_back(new Enemy1("images/enemy1-1.png"));
            bullet[4]=false;
            
        }
        
        //enemy 3
        if ((finish-start)>900000&&ship[5]) {
            enemy_man.push_back(new Enemy1("images/enemy1-1.png"));
            enemy_man.push_back(new Enemy3("images/enemy4.png"));
            ship[5]=false;
        }
        
        //property system generate property randomly.
        if ((finish-start)>1000000) {
            enemy_man.push_back(new Enemy1("images/enemy1-2.png"));
            srand((unsigned)time(NULL));
            int aa = rand()%20;
            if (aa>=14) {
                if (aa>= 18) {
                    property = new Property("images/property0.png", "hp");
                }
                else{
                    property = new Property("images/property1.png", "bullet");
                }
            }
            start=finish;
            for (int i=0; i<6; i++) {
                bullet[i]=true;
                ship[i]=true;
            }
            
            //in the end of each round, refresh plane's score and health.
            score_system(plane);
            health_system(plane);
            round++;
        }
        
    }
    
    if (round==5){
        if ((finish-start)>=200000) {
            SDL_Rect warnRect = {0, 200, 600, 200};
            SDL_RenderCopy(gRenderer, bossWarning->getTexture(), NULL, &warnRect);
        }
        if ((finish-start)>=500000) {
            start=finish;
            for (int i=0; i<5; i++) {
                bullet[i]=true;
                ship[i]=true;
            }
            round++;
        }
    }
}

//two different levels has different backgrounds
void GameManage::background_system(){
    background1->render();
    background2->render();
    if (background2->get_y()==5) {
        background1->set_y(4);
        background2->set_y(-691);
    }
}
void GameManage::background2_system(){
    background3->render();
    background4->render();
    if (background4->get_y()==5) {
        background3->set_y(4);
        background4->set_y(-691);
    }
}

//plane's score system
void GameManage::score_system(Plane *plane){
    long score = plane->get_score();
    long score_dup = score;
    int i = 1;
    while ((int)(score_dup/pow(10,i))!=0){
        i++;
    }
    
    stringstream ss_score;
    ss_score<<score;
    str_score = const_cast<char*>(ss_score.str().c_str());
    textRect_score  = {550-20*i,20,20*i,50};
    
    text = TTF_RenderUTF8_Solid(font,str_score,texColor);
    
    fontText = SDL_CreateTextureFromSurface( gRenderer, text);
    
    SDL_FreeSurface(text);
}

//plane's hp system
void GameManage::health_system(Plane *plane){
    
    long health = plane->get_health();
    long health_dup = health;
    int i = 1;
    while ((int)(health_dup/pow(10,i))!=0){
        i++;
    }
    
    ss_health.str("");
    ss_health<<plane->get_health();
    str_health = const_cast<char*>(ss_health.str().c_str());
    
    textRect_health = {80,20,15*(i+1),30};
    
    text_health = TTF_RenderUTF8_Solid(font,str_health,texColor);
    text_health_help = TTF_RenderUTF8_Solid(font,str_health_help,texColor);
    
    fontText_health = SDL_CreateTextureFromSurface( gRenderer, text_health);
    fontText_health_help = SDL_CreateTextureFromSurface( gRenderer, text_health_help);
    
    SDL_FreeSurface(text_health);
    SDL_FreeSurface(text_health_help);
}

//the boom visual when plane is attacked
void GameManage::boom_visual(SDL_Rect r1, SDL_Rect r2){
    Mix_Chunk *destorySound;
    
    destorySound = Mix_LoadWAV("audio/plane_boom.wav");
    Mix_PlayChannel(-1,destorySound,0);
    
    SDL_Rect boom = {r1.x,r1.y,80,80};
    SDL_RenderCopy(gRenderer, boom1.getTexture(), NULL, &boom);
    boom = {r2.x,r2.y,80,80};
    SDL_RenderCopy(gRenderer, boom1.getTexture(), NULL, &boom);
    boom = {r1.x,r1.y,105,105};
    SDL_RenderCopy(gRenderer, boom2.getTexture(), NULL, &boom);
    boom = {r2.x,r2.y,105,105};
    SDL_RenderCopy(gRenderer, boom2.getTexture(), NULL, &boom);
    SDL_RenderPresent(gRenderer);
}

//clean up
void GameManage::cleanup()
{
    cout << "Exit game" << endl;
    cout << "---- cleaning up ----" << endl;
    
    for (int i = 0; i<enemy_man.size(); i++) {
        delete enemy_man.at(i);
    }
    
    for (int i = 0; i<enemy_bullet.size(); i++) {
        delete enemy_bullet.at(i);
    }
    
    TTF_CloseFont(font);
    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gRenderer = NULL;
    gWindow = NULL;
    
    SDL_Quit();
}


void GameManage::continue_game(bool *quit){
    SDL_Event e;
    bool cont = false;
    Button *start_button = new Button(174,256,252,60, "images/game_continue1_1.png");
    SDL_Rect start_position = start_button->get_rect();
    
    Button *exit_button = new Button(174,376,252,60, "images/game_end1_1.png");
    SDL_Rect exit_position = exit_button->get_rect();
    while (!*quit&&!cont) {
        SDL_RenderClear(gRenderer);
        
        //diferent background in different level
        if (level == 1){
            background_system();
        }
        else{
            background2_system();
        }
        
        SDL_Rect black_rect = {0,0,600,695};
        SDL_RenderCopy(gRenderer, black_background->getTexture(), NULL, &black_rect);
        start_button->render();
        exit_button->render();
        while (SDL_PollEvent(&e)!=0) {
            if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
                int x,y;
                SDL_GetMouseState(&x, &y);
                switch (e.type) {
                    case SDL_MOUSEMOTION:
                        if (x>=start_button->get_rect().x&&x<=start_button->get_rect().x+start_position.w&&y>=start_button->get_rect().y&&y<=start_button->get_rect().y+start_position.h) {
                            start_button->set_image("images/game_continue_wan.png");
                        }
                        if (x<=start_button->get_rect().x||x>=start_button->get_rect().x+start_position.w||y<=start_button->get_rect().y||y>=start_button->get_rect().y+start_position.h) {
                            //here is check whether we need to change picture
                            if (start_button->get_image() == "images/game_continue_wan.png") {
                                start_button->set_image("images/game_continue1_1.png");
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
                            cont = true;
                        }
                        if (x>=exit_position.x&&x<=exit_position.x+exit_position.w&&y>=exit_position.y&&y<=exit_position.y+exit_position.h) {
                            *quit = true;
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
    
    start_game();
    if (round <6) {
        
        round = round-1;
    }
}