#ifndef Level_h
#define Level_h
#include "graphics.h"
#include "audio.h"
#include "music.h"
#include "globals.h"
#include "tetromino.h"



#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
using std::vector;
using std::pair;
using std::map;
using namespace colors;
using namespace directions;
using namespace rotations;
using namespace gravityCalc;

class Graphics;

class Level {
    public:
        Level();
        Level(Graphics &graphics);

        void loadNewTetrimino(Tetromino& t);
        bool moveActiveBlocks(Direction dir);
        bool rotateActiveBlocks();

        bool blockHasExpired();

        int clearLines();

        void setGravity(int level){this->currentGravity = getGravityByLevel(level); }

        bool checkGameIsOver(Tetromino& t);
        void update();
        void draw(Graphics &graphics);

        Music levelBGMusic;


    private:
       
        vector<SDL_Texture*> _backgroundTextures;
        vector<pair<int,int>> _active_blocks;
        map<Color, SDL_Texture*> _colorTextures;

        rotation blockConfiguration = ZERO_DEG;

        //NOTE: REPRESENTS BOARD WHICH WILL BE 20 ROWS BY 10 COLUMNS
        int blocks[20][10] = {0};
        
        vector<pair<int, int>> activeCoordinates;
        int xStart = 195;
        int yStart = -36;

        //Gravity units
        int currentGravity = getGravityByLevel(0);
        int gravitytimer = currentGravity;


        /*Checks if move collides with boundries*/
        bool isValidMoveBoundry(Direction dir){
            for (int x = 0; x < this->_active_blocks.size(); x++){
                pair<int, int> coord = this->_active_blocks.at(x);
                pair<int, int>  dirChange = getDirectionChange(dir);
                int j = coord.first + dirChange.first;
                int i = coord.second + dirChange.second;

                if (j >= 10 || j < 0 || i >= 20){
                    return false;
                }

                //Check same left, right block collision
                int below_left_right = j;

                if (this->blockExpirationHelper(below_left_right, false, i)){
                    std::cout << "hit here" << std::endl;
                    return false;
                }

                //Sanity check that no block exists below
                if (this->blockExpirationHelper(i, true, j)){
                    std::cout << "hit here" << std::endl;
                    return false;
                }

            }
            return true;
        }

        bool blockExpirationHelper(int below, bool isDown, int numTwo){
            bool hasExpired = false;

            int compNum = (isDown) ? this->blocks[below][numTwo] : this->blocks[numTwo][below];
            //Check if block below is not in 'Active Blocks' but is in array
            if (compNum != 0){
                
                hasExpired = true;
                for (int y = 0; y < this->_active_blocks.size(); y++){
                    pair<int, int> coord_two = this->_active_blocks.at(y);
                    if (isDown){
                        if (coord_two.second == below && coord_two.first == numTwo){
                            //std::cout << coord_two.second << " And: " << below << " And: " << compNum<< this->blocks[below][numTwo] << std::endl;
                            hasExpired = false;
                        }
                    } else {
                        if (coord_two.first == below){
                            hasExpired = false;
                        }
                    }
                    
                }
            }

            if (hasExpired){
                
                return true;
            }
            return false;
        }

        void displayArray(Graphics &graphics){
            SDL_Rect bgTile = {xStart,yStart,150, 150};
            for (int i = 0; i < 20; i++){
                for (int j = 0; j < 10; j++){
                    //blocks[i][j] = 2; TEST THE DRAW FUNCTION
                    if (blocks[i][j] > 0){
                        //std::cout << blocks[i][j] << " " <<i << " " << j << " BOOGIE";
                        
                        Color c = getColorFromNum(blocks[i][j]);
                        bgTile.x = xStart + j * 30;
                        bgTile.y = yStart + i * 30;
                        graphics.blitSurface(this->_colorTextures[c], NULL, &bgTile);
                    }
                    
                }
                //std::cout <<"  "<<std::endl;
            }
            //std::cout <<"WOOO"<<std::endl;
        }

};

#endif