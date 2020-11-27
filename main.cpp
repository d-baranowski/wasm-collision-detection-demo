#include "game.hpp"

Uint32 last_time;
Uint32 last_frame_time;
Uint32 current_time;

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Rect dest = {.x = 160, .y = 100, .w = 16, .h = 16 };

SDL_Texture *sprite_texture;

SDL_Event event;

Rectangle rec = Rectangle();
Ray ray = Ray();

bool left_key_down = false;
bool right_key_down = false;
bool up_key_down = false;
bool down_key_down = false;
bool space_key_down = false;
Vector2D mouse_pos = Vector2D(0,0);

double delta_time = 0.0;
int diff_time = 0;

void input() {
     if( SDL_PollEvent( &event ) ){
        switch( event.type ){
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        left_key_down = true;
                        break;
                    case SDLK_RIGHT:
                        right_key_down = true;
                        break;
                    case SDLK_UP:
                        up_key_down = true;
                        break;
                    case SDLK_DOWN:
                        down_key_down = true;
                        break;
                    case SDLK_SPACE:
                        space_key_down = true;
                        break;

                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        left_key_down = false;
                        break;
                    case SDLK_RIGHT:
                        right_key_down = false;
                        break;
                    case SDLK_UP:
                        up_key_down = false;
                        break;
                    case SDLK_DOWN:
                        down_key_down = false;
                        break;
                    case SDLK_SPACE:
                        space_key_down = false;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEMOTION: {
                SDL_MouseMotionEvent *m = (SDL_MouseMotionEvent * ) & event;
                mouse_pos.x = m->x;
                mouse_pos.y = m->y;
                break;
            }
            default:
                break;
        }
    }
}

void move() {
    rec.pos.SetXY(50, 150);
    rec.size.SetXY(50, 150);

    ray.origin.SetXY(0,500);
    ray.direction = mouse_pos - ray.origin;
}

void render() {
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    // Render rect

    ray.Render(renderer);

    CollisionInfo info = RayVsRectangle(&ray, &rec);
    if (info.collision && info.t < 1) {
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
        SDL_Rect r;
        r.x = info.contact_point.x;
        r.y = info.contact_point.y;
        r.w = 10;
        r.h = 10;
        SDL_RenderFillRect( renderer, &r );
        double d = 100;
        Vector2D end = info.contact_point + (d * info.contact_normal);
        SDL_RenderDrawLine(renderer, info.contact_point.x, info.contact_point.y, end.x, end.y);
    }

    rec.Render(renderer);

    SDL_RenderPresent( renderer );
}

void game_loop() {
    input();
    move();
    render();
}

int main() {
    printf("ENEMY\n");
    SDL_Init( SDL_INIT_VIDEO );

    int return_val = SDL_CreateWindowAndRenderer( 320 * 4, 200 * 4, 0, &window, &renderer );

    if( return_val != 0 ) {
        printf("Error creating renderer %d: %s\n", return_val, IMG_GetError() );
        return 0;
    }

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );

    last_frame_time = last_time = SDL_GetTicks();

    emscripten_set_main_loop(game_loop, 0, 0);

    return 1;
}