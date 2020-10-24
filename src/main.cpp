#include <iostream>
#include "headers/game.h"

using namespace std;

Game *game = nullptr;
int main(){
    
    //Limit FrameRate
    const int FPS = 60;
    const int FrameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    while (game->running()){
        frameStart = SDL_GetTicks();
        if (game->gameIsOver()){
            game->handleGameEndEvents();
        } else {
            game->handleEvents();
            game->update();
        }
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (FrameDelay > frameTime){
            SDL_Delay(FrameDelay - frameTime);
        }

    }
    return 0;
}
