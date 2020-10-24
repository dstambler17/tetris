#include "headers/block.h"
#include "headers/graphics.h"
#include "headers/sprite.h"
#include "headers/globals.h"

#include <string>
#include <iostream>

Block::Block() {}
Block::Block(Graphics &graphics, colors::Color color):
Sprite(graphics, "content/sprites/tetris_blocks/" + colors::getColorString(color), 100, 100, 300, 400)
{

}


void Block::update() {
    Sprite::update();
}

void Block::draw(Graphics &graphics, int x, int y) {
    Sprite::draw(graphics, x, y);
}
