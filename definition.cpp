#include <SDL.h>

#include "definition.h"

using namespace std;

SDL_Renderer* renderer = nullptr;
SDL_Rect playerRect = {SCREEN_WIDTH / 2 - CHARACTER_WIDTH / 2, SCREEN_HEIGHT / 2 - CHARACTER_HEIGHT / 2, CHARACTER_WIDTH, CHARACTER_HEIGHT};
SDL_Rect playButton = { 100, 450, 150, 120 };
SDL_Rect directionButton = { 250, 450, 150, 120 };
Uint32 currentTime = SDL_GetTicks();
vector<Plant> plants;
vector<Bee> bees;

int score = 0;
