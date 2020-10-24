#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <vector>
#include <iostream>
using std::pair;
using std::vector;

namespace globals {
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	const float SPRITE_SCALE = 2.0f;
}

namespace sides {
	enum Side {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};

	inline Side getOppositeSide(Side side) {
		return
				side == TOP ? BOTTOM :
				side == BOTTOM ? TOP :
				side == LEFT ? RIGHT :
				side == RIGHT ? LEFT :
				NONE;
	}

}

namespace directions {
	enum Direction {
		DOWN,
		LEFT,
		RIGHT
	};

	inline pair<int,int> getDirectionChange(Direction dir) {
		switch (dir){
		case DOWN:
			return std::make_pair(0,1);
			break;
		case LEFT:
			return std::make_pair(-1,0);;
			break;
		case RIGHT:
			return std::make_pair(1,0);;
			break;
		default:
			return std::make_pair(0,0);;
		}
	}

}



namespace colors {
	enum Color {
		RED,
		GREEN,
		BLUE,
	};

	inline std::string getColorString(Color color){
		if (color == RED){
			return "red.png";
		} else if (color == BLUE){
			return "blue.png";
		} else {
			return "green.png";
		}
	}

	inline Color getColorFromNum(int num){
		if (num == 1){
			return RED;
		} else if (num == 2){
			return GREEN;
		} else {
			return BLUE;
		}
	}

	inline int getNumFromColor(Color color){
		if (color == RED){
			return 1;
		} else if (color == GREEN){
			return 2;
		} else {
			return 3;
		}
	}
}

namespace tetro {
	enum TetrominoType {
		LINE,
		TSHAPE,
		LSHAPE,
		BOX,
		JAGGED
	};

	inline TetrominoType getTetroFromNum(int num){
		switch (num){
		case 0:
			return LINE;
			break;
		case 1:
			return TSHAPE;
			break;
		case 2:
			return LSHAPE;
			break;
		case 3:
			return BOX;
			break;
		default:
			return JAGGED;
			break;
		}
	}
}

namespace rotations {
	enum rotation {
		ZERO_DEG,
		NINETY_DEG,
		ONE_EIGHTY_DEG,
		TWO_SEVENTY_DEG,
	};

	inline rotation getNextRotation(rotation r ){
		switch (r)
		{
		case ZERO_DEG:
			return NINETY_DEG;
			break;
		case NINETY_DEG:
			return ONE_EIGHTY_DEG;
			break;
		case ONE_EIGHTY_DEG:
			return TWO_SEVENTY_DEG;
			break;
		case TWO_SEVENTY_DEG:
			return ZERO_DEG;
			break;
		default:
			break;
		}
	}

	inline bool checkValidRotationVert(int i, int j, int a[][10], int sub_rotation[4][2], vector<pair<int,int>> &activeBlocks, int color){
		bool valid = true;
		for (int x = 0; x < 4; x++){
			for (int y = 0; y < 2; y++){
				int new_i = x + i;
				int new_j = y + j;
				if (new_j >= 10 || new_j < 0 || new_i >= 20 || new_i < 0){
					valid = false;
				}
				if (a[new_i][new_j] != 0){
					valid = false;
				}
			}
		}

		if (valid){
			return true;
		}

		//restore the blocks
		for (int vecInt = 0; vecInt < activeBlocks.size(); vecInt++){
			int old_j = activeBlocks.at(vecInt).first;
			int old_i = activeBlocks.at(vecInt).second;
			a[old_i][old_j] = color;
		}
		return valid;
		
	}


	inline bool rotateToVertical(int i, int j, int a[][10], vector<pair<int,int>> &activeBlocks){
			int color;
		    int sub_rotation[4][2] = {0};
			for (int x = 0; x < 2; x++){
				for (int y = 0; y < 4; y++){
					int val = a[x + i][y + j];
					if (a[x + i][y + j] != 0){
						color = a[x + i][y + j];
					}
					a[x + i][y + j] = 0;
					sub_rotation[y][(x + 1)%2] = val;
				}
			}

			if (!checkValidRotationVert(i, j, a, sub_rotation, activeBlocks, color)){
				return false;
			}

			//Check rotation collision 

			activeBlocks.clear();
			for (int x = 0; x < 4; x++){
				for (int y = 0; y < 2; y++){
					a[x + i][y + j] = sub_rotation[x][y];
					if (sub_rotation[x][y] != 0){
						activeBlocks.push_back(std::make_pair(y + j, x + i));
					}
					std::cout << sub_rotation[x][y] << " ";
				}
				std::cout << std::endl;
			}
			return true;
	}

	inline bool checkValidRotationHoriz(int i, int j, int a[][10], int sub_rotation[2][4], vector<pair<int,int>> &activeBlocks, int color){
		bool valid = true;
		for (int x = 0; x < 2; x++){
			for (int y = 0; y < 4; y++){
				int new_i = x + i;
				int new_j = y + j;
				if (new_j >= 10 || new_j < 0 || new_i >= 20 || new_i < 0){
					valid = false;
				}
				if (a[new_i][new_j] != 0){
					valid = false;
				}
			}
		}

		if (valid){
			return true;
		}

		//restore the blocks
		for (int vecInt = 0; vecInt < activeBlocks.size(); vecInt++){
			int old_j = activeBlocks.at(vecInt).first;
			int old_i = activeBlocks.at(vecInt).second;
			a[old_i][old_j] = color;
		}
		return valid;
	}

	inline bool rotateToHorizontal(int i, int j, int a[][10], vector<pair<int,int>> &activeBlocks){
		int color;
		int sub_rotation[2][4] = {0};
			for (int x = 0; x < 4; x++){
				for (int y = 0; y < 2; y++){
					int val = a[x + i][y + j];
					//std::cout << val << " " << x << " " << y << std::endl;
					if (a[x + i][y + j] != 0){
						color = a[x + i][y + j];
					}
					a[x + i][y + j] = 0;
					int new_x = 0;
					switch (x){
						case 0:
							new_x = 3;
							break;
						case 1:
							new_x = 2;
							break;
						case 2:
							new_x = 1;
							break;
						case 3:
							new_x = 0;
							break;
						default:
							break;
					}
					sub_rotation[y][new_x] = val;
				}
			}

			if (!checkValidRotationHoriz(i, j, a, sub_rotation, activeBlocks, color)){
				return false;
			}

			activeBlocks.clear();
			for (int x = 0; x < 2; x++){
				for (int y = 0; y < 4; y++){
					a[x + i][y + j] = sub_rotation[x][y];
					if (sub_rotation[x][y] != 0){
						activeBlocks.push_back(std::make_pair(y + j, x + i));
					}
					std::cout << sub_rotation[x][y] << " ";
				}
				std::cout << std::endl;
			}

		return true;
	}

}

namespace scoreCalc {
	/*Based on real tetris scoring system*/
	inline int calcTetrisScoreBonus(int level, int linescleared){
		int baseMultiplier;  
		switch (linescleared)
		{
		case(0):
			baseMultiplier = 0;
		case (1):
			baseMultiplier = 40;
			break;
		case (2):
			baseMultiplier = 100;
			break;
		case (3):
			baseMultiplier = 300;
			break;
		default:
			baseMultiplier = 1200;
			break;
		} 

		return (level + 1) * baseMultiplier;
	}
}

namespace gravityCalc {

	inline int getGravityByLevel(int level){
		int gravity;
		switch (level)
		{
		case (0):
			gravity = 1000;
			break;
		case (1):
			gravity = 200;
		case (2):
			gravity = 100;
			break;
		case (3):
			gravity = 50;
			break;
		case (4):
			gravity = 40;
			break;
		case (5):
			gravity = 30;
			break;
		case (6):
			gravity = 20;
			break;
		case (7):
			gravity = 10;
			break;
		case (8):
			gravity = 8;
			break;
		case (9):
			gravity = 6;
			break;
		case (10):
			gravity = 4;
			break;
		default:
			gravity = 2;
			break;
		}
		return gravity;
	}
	
}



struct Vector2 {
	int x, y;
	Vector2() :
		x(0), y(0)
	{}
	Vector2(int x, int y) :
		x(x), y(y)
	{}
	Vector2 zero() {
		return Vector2(0, 0);
	}
};

#endif
