#include "headers/audio.h"
#include <string>
#include <iostream>

Audio::Audio() {}
Audio::Audio(std::string filePath, int channel) {
    this->soundEffect = Mix_LoadWAV(filePath.c_str());
    this->channel = channel;
}

void Audio::play() {
    Mix_PlayChannel(this->channel, this->soundEffect, 0);
}

void Audio::pause() {
    Mix_HaltChannel(this->channel);
}