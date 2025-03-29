#ifndef UPDATESCORE_H_INCLUDED
#define UPDATESCORE_H_INCLUDED

#include <SDL_ttf.h>

#include "definition.h"

void drawLevelInfo(SDL_Renderer* renderer, TTF_Font* font, int level, int plantedFlowers, int beeCount, int lives, Uint32 levelStartTime, int seeds, bool isPaused, Uint32 pausedTime, bool state);
bool checkLevelWinLose(int level, int plantedFlowers, int& beeCount, Uint32 levelStartTime, int& lives, bool& gameWon, bool& gameLost, bool& state);

#endif // UPDATESCORE_H_INCLUDED
