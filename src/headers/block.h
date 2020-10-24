#ifndef Block_h
#define Block_h
#include "graphics.h"
#include "globals.h"
#include "sprite.h"

#include <string>
#include <iostream>

class Graphics;

class Block : Sprite {
    public:
        Block();
        Block(Graphics &graphics, colors::Color color);

        void update();
        void draw(Graphics &graphics, int x, int y);


    private:
        colors::Color color;
};

#endif