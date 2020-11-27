//
// Created by Daniel Baranowski on 21/11/2020.
//

#ifndef HAMDS_ON_GAME_DEVELOPMENT_WITH_WEBASSEMBLY_BOOK_RAY_H
#define HAMDS_ON_GAME_DEVELOPMENT_WITH_WEBASSEMBLY_BOOK_RAY_H

#import "Vector2D.h"
#include <SDL2/SDL.h>


class Ray {
public:
    Vector2D origin;
    Vector2D direction;


    Ray(Vector2D origin, Vector2D direction);
    Ray();
    void Render(SDL_Renderer *renderer);
};


#endif //HAMDS_ON_GAME_DEVELOPMENT_WITH_WEBASSEMBLY_BOOK_RAY_H
