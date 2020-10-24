#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "headers/graphics.h"
#include "headers/globals.h"
using namespace std;

/* Graphics class
 * Holds all information dealing with graphics for the game
 */

Graphics::Graphics() {
    //Uint32 flag = SDL_RENDERER_ACCELERATED;
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Tetris");
    SDL_SetRenderDrawColor(this->_renderer, 255, 255, 255, 255);
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
    
    if (this->_spriteSheets.count(filePath) == 0) {
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_spriteSheets[filePath];
}

SDL_Surface* Graphics::loadText(const std::string &fontPath, const std::string &text, int fontSize) {

    if (TTF_Init() < 0) {
        std::cout << "Init No work" << std::endl;
    }

    SDL_Color text_color = {0,0,0};
    if (this->_fonts.count(fontPath) == 0) {
        
        this->_fonts[fontPath] = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (!this->_fonts[fontPath]) {
            std::cout << TTF_GetError() << std::endl;
        }
    }
    return TTF_RenderText_Solid(this->_fonts[fontPath], text.c_str(), text_color);
}



void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
    SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}


void Graphics::flip() {
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
	return this->_renderer;
}