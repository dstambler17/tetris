#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>


class Audio {
public:
    Audio();
    Audio(std::string filePath, int channel);
    void play();
    void pause();
private:
    Mix_Chunk *soundEffect;
    int channel;
};

#endif //AUDIO_H