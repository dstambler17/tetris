#ifndef Tetromino_H
#define Tetromino_H

#include "sprite.h"
#include "block.h"
#include "globals.h"

#include <vector>
#include <string>

using std::vector;
using namespace colors;
using namespace tetro;


class Graphics;


class Tetromino : public Sprite {
public:
	Tetromino();
	Tetromino(Graphics &graphics, int spawnX, int spawnY, Color color);
	void update();
	virtual void draw(Graphics &graphics);

    int getColorInt(){ return getNumFromColor(this->color);}

    int shape[2][4] = {{0,0,0,0}, {0,0,0,0}};


protected:
    Color color;
	vector<Block*> _blocks;
};


class Line : public Tetromino {
public:
	Line();
	Line(Graphics &graphics, int spawnX, int spawnY, Color color);
	void draw(Graphics &graphics);


private:
	float _startingX, _startingY;
};


class TShape : public Tetromino {
public:
	TShape();
	TShape(Graphics &graphics, int spawnX, int spawnY, Color color);
	void draw(Graphics &graphics);


private:
	float _startingX, _startingY;
};


class Box : public Tetromino {
public:
	Box();
	Box(Graphics &graphics, int spawnX, int spawnY, Color color);
	void draw(Graphics &graphics);


private:
	float _startingX, _startingY;
};



class LShape : public Tetromino {
public:
	LShape();
	LShape(Graphics &graphics, int spawnX, int spawnY, Color color);
	void draw(Graphics &graphics);


private:
	float _startingX, _startingY;
};


class Jagged : public Tetromino {
public:
	Jagged();
	Jagged(Graphics &graphics, int spawnX, int spawnY, Color color);
	void draw(Graphics &graphics);


private:
	float _startingX, _startingY;
};

/*Factory Pattern for initializing the Tetrominos*/
class TetrominoFactory {
public:
    TetrominoFactory(){}

    Tetromino getTetromino(int typeInt, Graphics &graphics, int spawnX, int spawnY, int colorInt){
        TetrominoType tType = getTetroFromNum(typeInt);
        Color color = getColorFromNum(colorInt);
        switch (tType)
        {
        case LINE:
            return Line(graphics, spawnX, spawnY, color);
            break;
        case TSHAPE:
            return TShape(graphics, spawnX, spawnY, color);
            break;
        case LSHAPE:
            return LShape(graphics, spawnX, spawnY, color);
            break;
        case BOX:
            return Box(graphics, spawnX, spawnY, color);
            break;
        default:
            return Jagged(graphics, spawnX, spawnY, color);
            break;
        }
    }
    
};



#endif
