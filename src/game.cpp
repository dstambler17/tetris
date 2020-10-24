#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "headers/game.h"
#include "headers/graphics.h"

#include "headers/music.h"
#include "headers/audio.h"

#include "headers/level.h"
#include "headers/globals.h"
#include "headers/tetromino.h"
#include "headers/textmanager.h"


#include <stdlib.h> 
#include <string>
#include <iostream>
#include <vector>
using namespace colors;
using namespace tetro;
using namespace directions;


Game::Game(){

    isRunning = true;
    
    this->_gameEndText = TextManager(_graphics, "Game Over, press 's' to retry or 'q' to exit", "content/fonts/Roboto-Medium.ttf");
    
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "init error" <<std::endl;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        std::cout << Mix_GetError() << std::endl;
    }

    this->_tetrisAudio = Audio("content/audio/tetris.wav", 1);
    this->_landAudio = Audio("content/audio/land.wav", 2);
    this->_levelAudio = Audio("content/audio/level.wav", 1);
    this->_moveAudio = Audio("content/audio/move.wav", 3);
    this->_rotationAudio = Audio("content/audio/rotate.wav", 3);
    this->_gameEndAudio = Audio("content/audio/gameend.wav", 3);

    this->initializeRound();
}

Game::~Game()
{}

void Game::handleGameEndEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_q) { // exit game
                isRunning = false;
            }
            if(event.key.keysym.sym == SDLK_s) { // restart
                
                this->_gameEndAudio.pause();
                gameEnd = false;
                this->score = 0;
                this->level = 0;
                this->lines = 0;
                this->initializeRound();
            }
            break;
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}


void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_LEFT) { // move left
                std::cout << "LEFT" <<std::endl;
                if (this->_level.moveActiveBlocks(LEFT)){
                    this->_moveAudio.play();
                }
            }
            if(event.key.keysym.sym == SDLK_RIGHT) { // move right
                std::cout << "RIGHT" <<std::endl;
                if (this->_level.moveActiveBlocks(RIGHT)){
                    this->_moveAudio.play();
                }
            }

            if(event.key.keysym.sym == SDLK_DOWN) { // move down
                std::cout << "DOWN" <<std::endl;
                if (this->_level.moveActiveBlocks(DOWN)){
                    this->_moveAudio.play();
                }
            }
            if(event.key.keysym.sym == SDLK_SPACE) { // fire lazer
                std::cout << "ROTATION" <<std::endl;
                if (this->_level.rotateActiveBlocks()){
                    this->_rotationAudio.play();
                }
            }
            
            break;
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}


void Game::update(){
    //this->_nextText.updateTex(_graphics, "NEXT");
    this->_nextTetromino.update();
    this->_level.update();
    if (this->_level.blockHasExpired()){
        this->_landAudio.play();
        int clearedLines = this->_level.clearLines();
        if (clearedLines > 0){
            this->updateStatisticsData(_graphics, clearedLines);
        }
        this->_curTetromino = this->_nextTetromino;
        this->_nextTetromino = this->fac.getTetromino(rand() % 5, _graphics, 110, 300, rand() % 3 + 1);
        if (this->_level.checkGameIsOver(this->_curTetromino)){
            Mix_HaltMusic();
            this->_gameEndAudio.play();
            gameEnd = true;
        }
        this->_level.loadNewTetrimino(this->_curTetromino);
    }
}

void Game::render(){
    _graphics.clear();
    SDL_Rect nextTextRect = {80, 180, 70, 40};
    this->_level.draw(_graphics);
    this->_nextTetromino.draw(_graphics);
    this->_nextText.draw(_graphics, &nextTextRect);

    if (gameEnd){
        SDL_Rect endGameRect = {230, 200, 360, 60};
        this->_gameEndText.draw(_graphics, &endGameRect);
    }

    this->drawStatisticsData(_graphics);

    _graphics.flip();
}
