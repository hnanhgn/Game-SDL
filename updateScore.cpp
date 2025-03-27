#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "definition.h"

void drawLevelInfo(SDL_Renderer* renderer, TTF_Font* font, int level, int plantedFlowers, int beeCount, int lives, Uint32 levelStartTime, int seeds, bool isPaused, Uint32 pausedTime)
{
    SDL_Color white = {255, 255, 255, 255};
    char textBuffer[100];
    Uint32 currentTime = SDL_GetTicks();
    float elapsedTime;

    // Tính thời gian đã trôi qua
    if (isPaused) {
        elapsedTime = pausedTime / 1000.0f; // Dừng thời gian tại pausedTime
    } else {
        elapsedTime = (currentTime - levelStartTime) / 1000.0f; // Thời gian bình thường
    }

    float timeLimit = 0.0f;
    int flowerGoal = 0;
    switch (level) {
        case 1: timeLimit = 40.0f; flowerGoal = 10; break;
        case 2: timeLimit = 70.0f; flowerGoal = 20; break;
        case 3: timeLimit = 100.0f; flowerGoal = 30; break;
        case 4: timeLimit = 150.0f; flowerGoal = 50; break;
    }

    float timeLeft = timeLimit - elapsedTime;
    if (timeLeft < 0) timeLeft = 0;

    sprintf(textBuffer, "%d", level);
    SDL_Surface* levelSurface = TTF_RenderText_Solid(font, textBuffer, white);
    SDL_Texture* levelTexture = SDL_CreateTextureFromSurface(renderer, levelSurface);
    SDL_Rect levelRect = {275, 50, static_cast<int>(levelSurface->w * 2.0f), static_cast<int>(levelSurface->h * 1.5f)};
    SDL_RenderCopy(renderer, levelTexture, nullptr, &levelRect);

    sprintf(textBuffer, " %.1f s", timeLeft);
    SDL_Surface* timeSurface = TTF_RenderText_Solid(font, textBuffer, white);
    SDL_Texture* timeTexture = SDL_CreateTextureFromSurface(renderer, timeSurface);
    SDL_Rect timeRect = {420, 35, timeSurface->w, timeSurface->h};
    SDL_RenderCopy(renderer, timeTexture, nullptr, &timeRect);

    sprintf(textBuffer, "%d", beeCount);
    SDL_Surface* beeSurface = TTF_RenderText_Solid(font, textBuffer, white);
    SDL_Texture* beeTexture = SDL_CreateTextureFromSurface(renderer, beeSurface);
    SDL_Rect beeRect = {590, 35, beeSurface->w, beeSurface->h};
    SDL_RenderCopy(renderer, beeTexture, nullptr, &beeRect);

    sprintf(textBuffer, "%d", lives);
    SDL_Surface* livesSurface = TTF_RenderText_Solid(font, textBuffer, white);
    SDL_Texture* livesTexture = SDL_CreateTextureFromSurface(renderer, livesSurface);
    SDL_Rect livesRect = {690, 35, livesSurface->w, livesSurface->h};
    SDL_RenderCopy(renderer, livesTexture, nullptr, &livesRect);

    sprintf(textBuffer, " %d / %d", plantedFlowers, flowerGoal);
    SDL_Surface* flowerSurface = TTF_RenderText_Solid(font, textBuffer, white);
    SDL_Texture* flowerTexture = SDL_CreateTextureFromSurface(renderer, flowerSurface);
    SDL_Rect flowerRect = {880, 145, flowerSurface->w, flowerSurface->h};
    SDL_RenderCopy(renderer, flowerTexture, nullptr, &flowerRect);

    sprintf(textBuffer, "%d", seeds);
    SDL_Surface* seedSurface = TTF_RenderText_Solid(font, textBuffer, white);
    SDL_Texture* seedTexture = SDL_CreateTextureFromSurface(renderer, seedSurface);
    SDL_Rect seedRect = {890, 240, seedSurface->w, seedSurface->h};
    SDL_RenderCopy(renderer, seedTexture, nullptr, &seedRect);


}

bool checkLevelWinLose(int level, int plantedFlowers, int& beeCount, Uint32 levelStartTime, int& lives, bool& gameWon, bool& gameLost) {
    Uint32 currentTime = SDL_GetTicks();
    float elapsedTime = (currentTime - levelStartTime) / 1000.0f;

    switch (level) {
    case 1:
        beeCount = 0;
        if (elapsedTime > 40.0f) {
            if (plantedFlowers >= 10) gameWon = true;
            else gameLost = true;
        }
        break;
    case 2:
        beeCount = 1;
        if (elapsedTime > 70.0f) {
            if (plantedFlowers >= 20) gameWon = true;
            else gameLost = true;
        }
        break;
    case 3:
        beeCount = 2;
        if (elapsedTime > 100.0f) {
            if (plantedFlowers >= 20) gameWon = true;
            else gameLost = true;
        }
        break;
    case 4:
        beeCount = 3;
        if (elapsedTime > 150.0f) {
            if (plantedFlowers >= 30) gameWon = true;
            else gameLost = true;
        }
        break;
    }


    if (lives <= 0) {
        gameLost = true;
    }

    return (gameWon || gameLost); // Trả về true khi level kết thúc
}

