CC=gcc
CXX=g++
CPPFLAGS= -I include -L lib -l SDL2-2.0.0 -I include -L lib -l SDL2_image-2.0.0 -I include -L lib -l SDL2_ttf-2.0.0 \
-I include -L lib -l SDL2_mixer-2.0.0
#COMPILEFLAGS = -I include -L lib -l SDL2_ttf-2.0.0
#CPPFLAGS=-I include -l SDL2-2.0.0 -I include -l SDL2_image-2.0.0
DEPS = src/headers/game.h src/headers/graphics.h src/headers/sprite.h src/headers/rectangle.h \
	src/headers/textmanager.h src/headers/music.h src/headers/audio.h src/headers/globals.h src/headers/level.h \
	src/headers/block.h src/headers/tetromino.h
OBJ = main.o game.o graphics.o sprite.o textmanager.o music.o audio.o level.o block.o tetromino.o

%.o: src/%.cpp $(DEPS)
	$(CXX) -std=c++11 -c -o $@ $<

play: $(OBJ)
	$(CXX) -o $@ $^ $(CPPFLAGS)

clean:
	rm -f *.o play
