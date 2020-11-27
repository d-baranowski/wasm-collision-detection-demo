#include "Ray.h"

Ray::Ray(Vector2D origin, Vector2D direction) {
    this->origin = origin;
    this->direction = direction;
}

Ray::Ray() {
    this->origin = Vector2D();
    this->direction = Vector2D();
}

void Ray::Render(SDL_Renderer *renderer) {
    Vector2D end = this->origin + this->direction;
    SDL_RenderDrawLine(renderer, this->origin.x, this->origin.y, end.x, end.y);
}