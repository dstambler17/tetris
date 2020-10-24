#ifndef TextManager_h
#define TextManager_h
#include "graphics.h"

#include <string> 

class Graphics;

class TextManager {
    public:
        TextManager();
        TextManager(Graphics &graphics, std::string initText, std::string fontPath);

        void updateTex(Graphics &graphics, std::string newText);

        void draw(Graphics &graphics, SDL_Rect* rect);
        

    private:
        std::string _fontPath;
        SDL_Texture* _tex;
};

#endif