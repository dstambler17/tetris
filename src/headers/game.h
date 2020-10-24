#ifndef Game_h
#define Game_h
#include "graphics.h"
#include "level.h"
#include "block.h"
#include "audio.h"
#include "globals.h"
#include "tetromino.h"
#include "textmanager.h"

#include <vector>
#include <algorithm>

class Game {
    public:
        Game();
        ~Game();

        void handleEvents();
        void handleGameEndEvents();
        void update();
        void render();

        bool gameIsOver() { return this->gameEnd;}

        bool running() {return isRunning;}

    private:
        
        bool isRunning;
        bool gameEnd = false;
        Graphics _graphics;
        Level _level;
        TetrominoFactory fac = TetrominoFactory();
        Tetromino _curTetromino;
        Tetromino _nextTetromino;

        int level = 0;
        int lines = 0;
        int score = 0;

        TextManager _nextText;
        TextManager _linesText;
        TextManager _levelText;
        TextManager _scoreText;
        TextManager _gameEndText;

        Audio _tetrisAudio; 
        Audio _landAudio; 
        Audio _levelAudio;
        Audio _moveAudio;
        Audio _rotationAudio;
        Audio _gameEndAudio;

        //Helper function that initilizes the round at the start and after a new level is established
        void initializeRound(){
            this->_level = Level(_graphics);
            this->_curTetromino = this->fac.getTetromino(rand() % 5, _graphics, 110, 300, rand() % 3 + 1);
            this->_nextTetromino = this->fac.getTetromino(rand() % 5, _graphics, 110, 300, rand() % 3 + 1);

            this->_level.loadNewTetrimino(this->_curTetromino);

            this->_nextText = TextManager(_graphics, "NEXT", "content/fonts/Roboto-Medium.ttf");
            this->_linesText = TextManager(_graphics, "Score: 0", "content/fonts/Roboto-Medium.ttf");
            this->_levelText = TextManager(_graphics, "Level: 0", "content/fonts/Roboto-Medium.ttf");
            this->_scoreText = TextManager(_graphics, "Lines: 0", "content/fonts/Roboto-Medium.ttf");
            Music("content/music/Tetris_theme.ogg").play();
        }

        void updateStatisticsData(Graphics &_graphics, int linesClear){
            this->score += scoreCalc::calcTetrisScoreBonus(this->level, linesClear);
            this->lines += linesClear;
            int new_level = std::min(this->lines/10, 20);

            //Play proper audio queue
            if (new_level != this->level){
                this->_levelAudio.play();
                this->_level.setGravity(new_level);
            } else{
                this->_tetrisAudio.play();
            }

            this->level = new_level;
            std::string newScoreText = "Score: " + std::to_string(this->score);
            std::string newLinesText = "Lines: " + std::to_string(this->lines);
            std::string newLevelText = "Level: " + std::to_string(this->level);

            this->_linesText = TextManager(_graphics, newScoreText, "content/fonts/Roboto-Medium.ttf");
            this->_levelText = TextManager(_graphics, newLinesText, "content/fonts/Roboto-Medium.ttf");
            this->_scoreText = TextManager(_graphics, newLevelText, "content/fonts/Roboto-Medium.ttf");
        }

        void drawStatisticsData(Graphics &_graphics){
            SDL_Rect scoreTextRect = {600, 100, 120, 50};
            SDL_Rect levelTextRect = {600, 250, 120, 50};
            SDL_Rect linesTextRect = {600, 400, 120, 50};

            this->_scoreText.draw(_graphics, &scoreTextRect);
            this->_levelText.draw(_graphics, &levelTextRect);
            this->_linesText.draw(_graphics, &linesTextRect);
        }
};

#endif