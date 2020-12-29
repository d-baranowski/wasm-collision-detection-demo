#ifndef __GAME_H__
#define __GAME_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string>
#include <vector>
#include <cstdlib>
#include "lib/physics/particle.h"

#define MAX_VELOCITY 2.0

#define PI 3.14159
#define TWO_PI 6.28318

extern Uint32 last_time;
extern Uint32 last_frame_time;
extern Uint32 current_time;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern SDL_Rect dest;

extern SDL_Event event;

extern bool left_key_down;
extern bool right_key_down;
extern bool up_key_down;
extern bool down_key_down;
extern bool space_key_down;

extern double delta_time;
extern int diff_time;

enum FSM_STUB {
    SHOOT = 0,
    TURN_LEFT = 1,
    TURN_RIGHT = 2,
    ACCELERATE = 3,
    DECELERATE = 4
};

#endif