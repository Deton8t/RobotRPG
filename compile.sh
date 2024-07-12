#!/bin/bash
SDL2=$HOMEBREW_CELLAR/sdl2/2.30.1
image=$HOMEBREW_CELLAR/sdl2_image/2.8.2_1
mixer=$HOMEBREW_CELLAR/sdl2_mixer/2.8.0
ttf=$HOMEBREW_CELLAR/sdl2_ttf/2.22.0
src=./myheaders
clang++ -std=gnu++20 main.cpp -I$SDL2/include/SDL2 -L$SDL2/lib -lSDL2-2.0.0 -I$image/include/SDL2 -L$image/lib -lSDL2_image-2.0.0 -I$mixer/include/SDL2 -L$mixer/lib -lSDL2_mixer-2.0.0 -I$ttf/include/SDL2 -L$ttf/lib -lSDL2_ttf-2.0.0  -ogame.o 

