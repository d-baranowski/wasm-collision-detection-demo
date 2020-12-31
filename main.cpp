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

auto particleWorld = cyclone::ParticleWorld(100000, 1000000000);
auto player_particle = cyclone::Particle();
auto attached_particle = cyclone::Particle();

auto stifflerOne = cyclone::Particle();
auto stifflerTwo = cyclone::Particle();

SDL_Rect player_rect;
auto spring = cyclone::ParticleSpring(&player_particle, 0.8, 5);
auto springTwo = cyclone::ParticleSpring(&attached_particle, 0.8, 5);

auto joinOne = new cyclone::ParticleRod();
auto joinTwo = new cyclone::ParticleRod();

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
                //SDL_MouseMotionEvent *m = (SDL_MouseMotionEvent * ) & event;
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
    particleWorld.runPhysics(d);
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // the rect color (solid red)

    player_rect.x = player_particle.getPosition().x;
    player_rect.y = player_particle.getPosition().y;
    player_rect.w = 10;
    player_rect.h = 10;
    SDL_RenderFillRect(renderer, &player_rect);

    player_rect.x = attached_particle.getPosition().x;
    player_rect.y = attached_particle.getPosition().y;
    player_rect.w = 10;
    player_rect.h = 10;
    SDL_RenderFillRect(renderer, &player_rect);

    player_rect.x = stifflerOne.getPosition().x;
    player_rect.y = stifflerOne.getPosition().y;
    player_rect.w = 10;
    player_rect.h = 10;
    SDL_RenderFillRect(renderer, &player_rect);

    player_rect.x = stifflerTwo.getPosition().x;
    player_rect.y = stifflerTwo.getPosition().y;
    player_rect.w = 10;
    player_rect.h = 10;
    SDL_RenderFillRect(renderer, &player_rect);

    SDL_RenderPresent(renderer);
}

void game_loop() {
    particleWorld.startFrame();

    current_time = SDL_GetTicks();

    diff_time = current_time - last_time;
    delta_time = diff_time / 1000.0;
    last_time = current_time;

    input();

    if (left_key_down) {
        player_particle.addForce(cyclone::Vector3(-1, 0, 0) * 1000);
    }

    if (right_key_down) {
        player_particle.addForce(cyclone::Vector3(1, 0, 0) * 1000);
    }

    if (up_key_down) {
        player_particle.addForce(cyclone::Vector3(0, -1, 0) * 1000);
    }

    if (down_key_down) {
        player_particle.addForce(cyclone::Vector3(0, 1, 0) * 1000);
    }

    move(delta_time);
    render();
}

int main() {
    player_particle.setPosition(500, 500, 0);
    player_particle.setMass(20);
    player_particle.setDamping(0.98);

    attached_particle.setPosition(200, 200, 0);
    attached_particle.setMass(0.9);
    attached_particle.setDamping(0.98);

    particleWorld.addParticle(&player_particle);
    particleWorld.addParticle(&attached_particle);

    stifflerOne.setPosition(30, 30,0);
    stifflerOne.setMass(15);
    stifflerTwo.setPosition(60,60, 0);
    stifflerTwo.setMass(15);

    particleWorld.getForceRegistry().add(&attached_particle, &spring);
    particleWorld.getForceRegistry().add(&player_particle, &springTwo);

    particleWorld.addContact(joinTwo);
    particleWorld.addContact(joinOne);

    joinOne->particle[0] = &player_particle;
    joinOne->particle[1] = &stifflerOne;
    joinOne->length = 30;

    joinTwo->particle[0] = &stifflerOne;
    joinTwo->particle[1] = &stifflerTwo;
    joinTwo->length = 50;

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