

#include "headers/sprite.h"
#include "headers/block.h"
#include "headers/tetromino.h"
#include "headers/globals.h"

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using namespace colors;
using namespace sides;


Tetromino::Tetromino() {}
Tetromino::Tetromino(Graphics &graphics, int spawnX, int spawnY, Color color){
    this->_blocks.push_back(new Block(graphics, color));  
    this->_blocks.push_back(new Block(graphics, color)); 
    this->_blocks.push_back(new Block(graphics, color));  
    this->_blocks.push_back(new Block(graphics, color));
    this->color = color;
}

void Tetromino::update(){
    for (int c = 0; c < this->_blocks.size(); c++){
        _blocks.at(c)->update();
    }
}

void Tetromino::draw(Graphics &graphics){
    int startX = 50;
    int startY = 200;
    int idx = 0;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 4; j++){
            if (this->shape[i][j] == 1){
                _blocks.at(idx)->draw(graphics, startX + j * 20, startY + i * 20);
                idx++;
            }
        }
        
    } 
}


/* Line */
Line::Line(){}
Line::Line(Graphics &graphics, int spawnX, int spawnY, Color color):
    Tetromino(graphics, spawnX, spawnY, color){
        this->shape[0][0] = 1;
        this->shape[0][1] = 1;
        this->shape[0][2] = 1;
        this->shape[0][3] = 1;
    }
void Line::draw(Graphics &graphics){
    Tetromino::draw(graphics);
}


/* T Shape */
TShape::TShape(){}
TShape::TShape(Graphics &graphics, int spawnX, int spawnY, Color color):
    Tetromino(graphics, spawnX, spawnY, color){
        this->shape[0][0] = 1;
        this->shape[0][1] = 1;
        this->shape[0][2] = 1;
        this->shape[1][1] = 1;
    }
void TShape::draw(Graphics &graphics){
    Tetromino::draw(graphics);
}


/* Chess Knight Shape */
LShape::LShape(){}
LShape::LShape(Graphics &graphics, int spawnX, int spawnY, Color color):
    Tetromino(graphics, spawnX, spawnY, color){
        this->shape[0][0] = 1;
        this->shape[1][0] = 1;
        this->shape[1][1] = 1;
        this->shape[1][2] = 1;
    }
void LShape::draw(Graphics &graphics){
    Tetromino::draw(graphics);
}


/* Box Shape */
Box::Box(){}
Box::Box(Graphics &graphics, int spawnX, int spawnY, Color color):
    Tetromino(graphics, spawnX, spawnY, color){
        this->shape[0][1] = 1;
        this->shape[0][2] = 1;
        this->shape[1][1] = 1;
        this->shape[1][2] = 1;
    }
void Box::draw(Graphics &graphics){
    Tetromino::draw(graphics);
}

/*Sort of Zigzag shape */
Jagged::Jagged(){}
Jagged::Jagged(Graphics &graphics, int spawnX, int spawnY, Color color):
    Tetromino(graphics, spawnX, spawnY, color){
        this->shape[0][0] = 1;
        this->shape[0][1] = 1;
        this->shape[1][1] = 1;
        this->shape[1][2] = 1;
    }
void Jagged::draw(Graphics &graphics){
    Tetromino::draw(graphics);
}

