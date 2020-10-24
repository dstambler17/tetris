#include "headers/textmanager.h"
#include <string> 
#include <iostream>

//Bat class
TextManager::TextManager() {}

TextManager::TextManager(Graphics &graphics, std::string initText, std::string fontPath)
{   

    this->_fontPath = fontPath;
    SDL_Color color_text = { 0, 0, 0 }; 
    SDL_Surface* surface = graphics.loadText(this->_fontPath, initText, 40);
    this->_tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), surface);
    //std::cout << TTF_GetError() << std::endl;

}

void TextManager::updateTex(Graphics &graphics, std::string newText) {
	SDL_Surface* newSurface = graphics.loadText(this->_fontPath, newText, 50);
    this->_tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), newSurface);
}

void TextManager::draw(Graphics &graphics, SDL_Rect* rect) {
    /*SDL_Rect scoreRect = {720,20,80,40};
    SDL_Rect levelRect = {720, -10, 80, 40};*/
    graphics.blitSurface(this->_tex, NULL, rect);

}


