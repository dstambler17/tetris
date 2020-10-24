#include "headers/level.h"
#include "headers/graphics.h"
#include "headers/audio.h"
#include "headers/music.h"
#include "headers/globals.h"
#include "headers/tetromino.h"
#include "headers/block.h"



#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include <map>
#include <set>


using std::vector;
using std::pair;
using std::map;
using std::set;
using namespace colors;
using namespace directions;
using namespace rotations;

namespace fs = std::__fs::filesystem;

Level::Level() {}
Level::Level(Graphics &graphics) {
    //Populate color textures map
    for ( int col = RED; col <= BLUE; col++ ){
        SDL_Surface* bgSurface = graphics.loadImage("content/sprites/tetris_blocks/" + getColorString(static_cast<Color>(col)));
        this->_colorTextures[static_cast<Color>(col)] = SDL_CreateTextureFromSurface(graphics.getRenderer(), bgSurface);
    }


    fs::path pathToShow("content/backgrounds/");
    for (const auto& entry : fs::directory_iterator(pathToShow)) {
        auto file = entry.path().filename();
        std::string pathString = "content/backgrounds/" + file.u8string();
        SDL_Surface* bgSurface = graphics.loadImage(pathString);
        if (!bgSurface){
            std::cout << "ERROR WITH BG SURFACE" << std::endl;
        } else {
            this->_backgroundTextures.push_back(SDL_CreateTextureFromSurface(graphics.getRenderer(), bgSurface));
        }
    }
        
}

void Level::loadNewTetrimino(Tetromino &t){
    this->blockConfiguration = ZERO_DEG;
    this->gravitytimer = this->currentGravity;
    this->_active_blocks.clear();
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 4; j++){
            if (t.shape[i][j] == 1){
                this->blocks[0 + i][3 + j] = t.getColorInt();
                this->_active_blocks.push_back(std::make_pair(j + 3, i));
            }
        }
    } 
}

 /*Check if block touches floor or if it touches another block below it*/
bool Level::blockHasExpired(){
    for (int x = 0; x < this->_active_blocks.size(); x++){
        pair<int, int> coord = this->_active_blocks.at(x);
        int j = coord.first;
        int i = coord.second;

        int below = i + 1;

        //Check if touches floor
        if (below >= 20){
            return true;
        }

        if (blockExpirationHelper(below, true, j)){
            return true;
        }
    }

    return false;
}

bool Level::rotateActiveBlocks(){
    pair<int, int> coord = this->_active_blocks.at(0);
    int j = coord.first;
    int i = coord.second;

    rotation nextConfig = getNextRotation(this->blockConfiguration);
    int j_val; 
    /*Handle rotation*/
    bool valid = true;
    switch (nextConfig)
    {
    case ZERO_DEG:
        j_val = (this->blocks[i][_active_blocks.at(1).first] != 0) ? j : j - 1;
        if (j == j_val){
            //Edge case for L shape tetrinome
            j_val = (this->blocks[i][j - 1] == 0 && this->blocks[i +1][j] != 0 && this->blocks[i +2][j] != 0  && this->blocks[i +2][j - 1] != 0) ? j - 1 : j;
        }
        std::cout << "JVAL: "<< j_val << " J: " << j << " FIRST: " << _active_blocks.at(1).first << std::endl;
        valid = rotateToHorizontal(i, j_val, this->blocks, this->_active_blocks);
        break;
    case NINETY_DEG:
        valid = rotateToVertical(i, j, this->blocks, this->_active_blocks);
        break;
    case ONE_EIGHTY_DEG:
        j_val = (this->blocks[i][_active_blocks.at(1).first] != 0) ? j : j - 1;
        //std::cout << "JVAL: "<< j_val << "J: " << j << std::endl;
        valid = rotateToHorizontal(i, j_val, this->blocks, this->_active_blocks);
        break;
    case TWO_SEVENTY_DEG:
        //SET J-VAL FOR T SHAPE
        if (this->blocks[i + 1][j] != 0 && this->blocks[i + 1][j + 1] != 0 && this->blocks[i + 1][j - 1] != 0){
            j_val = j - 1;
        } else {
            j_val = j;
        }
        valid = rotateToVertical(i, j_val, this->blocks, this->_active_blocks);
        break;
    default:
        valid = true;
        break;
    }    
    if (valid){
        this->blockConfiguration = nextConfig;
    }
    return valid;
    
}


bool Level::moveActiveBlocks(Direction dir){
    if (!this->isValidMoveBoundry(dir)){
        return false;
    }
    std::cout << _active_blocks.size() << std::endl;
    int color = 0;
    for (int x = 0; x < this->_active_blocks.size(); x++){
        pair<int, int> coord = this->_active_blocks.at(x);

        //std::cout << coord.first << coord.second << std::endl;
        
        if (x == 0){
            color = this->blocks[coord.second][coord.first];
        }
        this->blocks[coord.second][coord.first] = 0;
        //Change dir
        pair<int, int>  dirChange = getDirectionChange(dir);

        int j = coord.first + dirChange.first;
        int i = coord.second + dirChange.second;
        //std::cout << j << i << std::endl;

        this->_active_blocks.at(x) = std::make_pair(j,i);
        //std::cout << _active_blocks.at(x).first << _active_blocks.at(x).second << " color: " << blocks[i][j] << std::endl;
        //std::cout << "BRICK BREAK" << std::endl;  
    }

    for (int x = 0; x < this->_active_blocks.size(); x++){
        pair<int, int> new_coord = this->_active_blocks.at(x);
        this->blocks[new_coord.second][new_coord.first] = color;
    }
    return true;

}

int Level::clearLines(){
    //build a set of unique rows represented by the tetriminoes
    set<int> uniqueLines;
    for (int vecInt = 0; vecInt < this->_active_blocks.size(); vecInt++){
        int i_pos = this->_active_blocks.at(vecInt).second;
        uniqueLines.insert(i_pos);
	}

    //check number of lines_cleared and handle_shift
    int linesCleared = 0;
    for (int lineNum : uniqueLines){
        //std::cout << lineNum << ": ";
        bool isCleared = true;
        for  (int j = 0; j < 10; j++){
            //std::cout << blocks[lineNum][j];
            if (!(this->blocks[lineNum][j] > 0)){
                isCleared = false;
            }
        }
        //handle line clear and shift down
        if (isCleared){
            //std::cout << "LINE IS CLEAR" <<std::endl;
            linesCleared += 1;
            for (int j = 0; j < 10; j++){
                this->blocks[lineNum][j] = 0;
            }
            for (int i = lineNum - 1; i >= 0;i --){
                for (int j = 0; j < 10; j++){
                    this->blocks[i + 1][j] = this->blocks[i][j];
                    this->blocks[i][j] = 0;
                }
            }
        }
        //handle clear end
    } 
    return linesCleared;
}

bool Level::checkGameIsOver(Tetromino& t){
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 4; j++){
            //If blocks exist in loaded area, then game is done
            if (t.shape[i][j] == 1 && this->blocks[0 + i][3 + j] != 0){
               return true;
            }
        }
    }
    return false; 
}

void Level::update() {
    //Handle gravity (move the blocks down every few turns)
    if (this->gravitytimer == 0){
        this->moveActiveBlocks(DOWN);
        this->gravitytimer = currentGravity;
    } else {
        this->gravitytimer -= 1;
    }
}

void Level::draw(Graphics &graphics) {
    //Draw First Line
    SDL_Rect bgTile = {228,0,20, 20};
    int tile_num = 0;
    for (int x = 0; x < 30; x++){
        bgTile.y = x * 20;
        graphics.blitSurface(this->_backgroundTextures.at(tile_num), NULL, &bgTile);
        tile_num = (tile_num + 1) % this->_backgroundTextures.size(); 
    }
    //Draw Second Line
    tile_num = 0;
    bgTile.x = 548;
    for (int x = 0; x < 30; x++){
        bgTile.y = x * 20;
        graphics.blitSurface(this->_backgroundTextures.at(tile_num), NULL, &bgTile);
        tile_num = (tile_num + 1) % this->_backgroundTextures.size(); 
    }
    this->displayArray(graphics);
}
