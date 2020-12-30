em++ *.cpp lib/**/*.cpp -std=c++17 --preload-file sprites -s USE_WEBGL2=1 -s \
--shell-file new_shell.html \
USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=["png"] -o \
build/index.html