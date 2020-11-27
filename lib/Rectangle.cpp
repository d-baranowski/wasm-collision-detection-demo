#include "Rectangle.h"

Rectangle::Rectangle(Vector2D pos, Vector2D size) {
    this->pos = pos;
    this->size = size;
}

Rectangle::Rectangle() {
    this->pos = Vector2D();
    this->size = Vector2D();
}

void Rectangle::Render(SDL_Renderer *renderer) {
    SDL_Rect r;
    r.x = this->pos.X();
    r.y = this->pos.Y();
    r.w = this->size.X();
    r.h = this->size.Y();
    SDL_RenderFillRect( renderer, &r );
}