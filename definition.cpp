#include <SDL.h>

#include "definition.h"

using namespace std;

SDL_Renderer* renderer = nullptr;
SDL_Rect playerRect = {SCREEN_WIDTH / 2 - CHARACTER_WIDTH / 2, SCREEN_HEIGHT / 2 - CHARACTER_HEIGHT / 2, CHARACTER_WIDTH, CHARACTER_HEIGHT};
Uint32 currentTime = SDL_GetTicks();
vector<Plant> plants;

int score = 0;
