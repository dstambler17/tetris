#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>


class Music {
public:
    Music();
    Music(std::string filePath);
    void play();
private:
    Mix_Music *musique;
};

#endif //MUSIC_H