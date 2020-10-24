#include "headers/sprite.h"
#include "headers/graphics.h"
#include "headers/sprite.h"

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

Sprite::Sprite() {}

Sprite::Sprite(Graphics &graphics, std::string filePath, int width, int height, int x_start, int y_start){
    SDL_Surface* spriteSurface = graphics.loadImage(filePath);
    this->_spriteTex =  SDL_CreateTextureFromSurface(graphics.getRenderer(), spriteSurface);
    //SDL_FreeSurface(spriteSurface);
    this->_destRect.w = width;
    this->_destRect.h = height;
    this->_destRect.x = x_start;
    this->_destRect.y = y_start;
    this->_x = x_start;
    this->_y = y_start;
    this->_boundingBox = Rectangle(this->_x, this->_y, width, height);
    
}

Sprite::~Sprite() {
}

void Sprite::draw(Graphics &graphics, int x_pos, int y_pos) {
    this->_destRect.x = x_pos;
    this->_destRect.y = y_pos;
	graphics.blitSurface(this->_spriteTex, NULL, &this->_destRect);
}

const Rectangle Sprite::getBoundingBox() const {
	return this->_boundingBox;
}

void Sprite::update() {
    this->_boundingBox = Rectangle(this->_x, this->_y, this->_destRect.w, this->_destRect.h);
}