#ifndef UPDATESCORE_H_INCLUDED
#define UPDATESCORE_H_INCLUDED

void drawLevelInfo(SDL_Renderer* renderer, TTF_Font* font, int level, int plantedFlowers, int beeCount, int lives, Uint32 levelStartTime, int seeds);
bool checkLevelWinLose(int level, int plantedFlowers, int& beeCount, Uint32 levelStartTime, int& lives, bool& gameWon, bool& gameLost);

#endif // UPDATESCORE_H_INCLUDED
