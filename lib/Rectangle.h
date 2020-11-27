#ifndef __GAME_RECTANGLE__
#define __GAME_RECTANGLE__

#include "Vector2D.h"
#include <SDL2/SDL.h>

class Rectangle {
    private:

    public:
        Vector2D pos;
        Vector2D size;

        Rectangle(Vector2D pos, Vector2D size);
        Rectangle();
        void Render(SDL_Renderer *renderer);
};

#endif