SDL2=$HOMEBREW_CELLAR/sdl2/2.28.5
image=$HOMEBREW_CELLAR/sdl2_image/2.8.2
src=./myheaders
clang++ -std=c++20 main.cpp -I$SDL2/include/SDL2 -L$SDL2/lib -lSDL2-2.0.0 -I$image/include/SDL2 -L$image/lib -lSDL2_Image-2.0.0 -ogame.o
