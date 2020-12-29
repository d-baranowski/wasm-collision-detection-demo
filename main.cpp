#include "game.hpp"

Uint32 last_time;
Uint32 last_frame_time;
Uint32 current_time;

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Rect dest = {.x = 160, .y = 100, .w = 16, .h = 16};

SDL_Texture *sprite_texture;

SDL_Event event;

bool left_key_down = false;
bool right_key_down = false;
bool up_key_down = false;
bool down_key_down = false;
bool space_key_down = false;

double delta_time = 0.0;
int diff_time = 0;

auto player_particle = cyclone::Particle();

void input() {
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
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
                switch (event.key.keysym.sym) {
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
//                mouse_pos.x = m->x;
//                mouse_pos.y = m->y;
                break;
            }
            default:
                break;
        }
    }
}

void move(double d) {
    player_particle.integrate(d);
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // the rect color (solid red)
    SDL_Rect rect;
    rect.x = player_particle.getPosition().x;
    rect.y = player_particle.getPosition().y;
    rect.w = 10;
    rect.h = 10;
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void game_loop() {
    current_time = SDL_GetTicks();

    diff_time = current_time - last_time;
    delta_time = diff_time / 1000.0;
    last_time = current_time;

    input();

    if (left_key_down) {
        player_particle.addForce(cyclone::Vector3(-1, 0, 0) * 100);
    }

    if (right_key_down) {
        player_particle.addForce(cyclone::Vector3(1, 0, 0) * 100);
    }

    if (up_key_down) {
        player_particle.addForce(cyclone::Vector3(0, 1, 0) * 100);
    }

    if (down_key_down) {
        player_particle.addForce(cyclone::Vector3(0, -1, 0) * 100);
    }

    move(delta_time);
    render();
}

int main() {
    player_particle.setPosition(300, 100, 0);
    player_particle.setMass(1);
    player_particle.setDamping(0.99);

    SDL_Init(SDL_INIT_VIDEO);

    int return_val = SDL_CreateWindowAndRenderer(320 * 4, 200 * 4, 0, &window, &renderer);

    if (return_val != 0) {
        printf("Error creating renderer %d: %s\n", return_val, IMG_GetError());
        return 0;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    last_frame_time = last_time = SDL_GetTicks();

    emscripten_set_main_loop(game_loop, 0, 0);

    return 1;
}