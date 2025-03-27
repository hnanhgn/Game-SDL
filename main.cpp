#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string.h>
#include <vector>

#include "definition.h"
#include "textureManager.h"
#include "characterMovement.h"
#include "flowerGrowth.h"
#include "updateScore.h"
#include "beeOperation.h"
#include "button.h"

using namespace std;

void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    TTF_Init();
    TTF_Font* font = TTF_OpenFont("LoveDays-2v7Oe.ttf", 24);

    loadTextures(renderer);
    bool running = true;
    bool facingLeft = false;
    bool showWelcomeScreen = true;
    bool showLoadingScreen = true;
    bool loaded = false;
    bool inContactWithBee = false  ;
    bool gameWon = false;
    bool gameLost = false;
    bool showDirection = false;
    bool showLevelPreview = false;
    bool isPaused = false;
    Uint32 levelStartTime = 0;
    Uint32 dizzyStartTime = 0;
    Uint32 currentTime = 0;
    Uint32 pausedTime = 0;
    SDL_Event event;

    while (running) {
        currentTime = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;

            if (showWelcomeScreen) {
                handleWelcomeScreenEvents(event, showWelcomeScreen, showLoadingScreen, showDirection, currentPage);
            }

            if (showLevelPreview) {
                chooseLevel(renderer, levelPreview, showLevelPreview, level,
                            level1Button, level2Button, level3Button, level4Button,
                            event, loaded, levelStartTime, lives, seeds, plantedFlower,
                            beeCount, bees, plants);
            }

            if (!showWelcomeScreen && loaded && !showLevelPreview) {
                handleGameEvents(event, showDirection, currentPage, facingLeft, playerRect, seeds, plantedFlower, isPaused, running);

                // Cập nhật thời gian tạm dừng
                if (isPaused && pausedTime == 0) {
                    pausedTime = currentTime - levelStartTime; // Lưu thời gian đã trôi qua
                }
                else if (!isPaused && pausedTime != 0) {
                    levelStartTime = currentTime - pausedTime; // Khôi phục thời gian bắt đầu
                    pausedTime = 0;
                }
            }
        }

        SDL_RenderClear(renderer);

        if (showWelcomeScreen) {
            drawWelcomeScreen(renderer, welcome, playIcon, directionIcon);
            if (showDirection) {
                drawDirection(renderer, showDirection, currentPage, nextRect, backRect, closeRect);
            }
            SDL_RenderPresent(renderer);
        }
        else if (showLoadingScreen && !loaded && !showLevelPreview) {
            drawLoadingScreen(renderer, beforeGame);
            showLoadingScreen = false;
            showLevelPreview = true;
            SDL_RenderPresent(renderer);
        }
        else if (showLevelPreview) {
            SDL_RenderCopy(renderer, levelPreview, nullptr, nullptr);
            SDL_RenderPresent(renderer);
        }
        else if (!showWelcomeScreen && loaded && !showLevelPreview) {
            if (levelStartTime == 0) {
                levelStartTime = SDL_GetTicks();
            }

            if (!showDirection && !isPaused) { // Chỉ cập nhật khi không tạm dừng
                updateMovement(playerRect);
                bool contactNow = checkContactWithBee(playerRect, bees);
                if (contactNow) { // Chỉ xử lý va chạm khi không tạm dừng
                    handleCollisionWithBee(lives, inContactWithBee, dizzyStartTime);
                }
                updateFlowerGrowth(plants);
                moveBee(bees, plants);

                if (checkLevelWinLose(level, plantedFlower, beeCount, levelStartTime, lives, gameWon, gameLost)) {
                    if (gameWon && level < 4) {
                        level++;
                        plantedFlower = 0;
                        levelStartTime = SDL_GetTicks();
                        gameWon = false;
                        bees.clear();
                    }
                }
            }

            SDL_RenderCopy(renderer, background, nullptr, nullptr);
            addBees(level);
            drawBees(renderer, bee);
            drawPlants(renderer, flowerGrowthStep);
            drawCharacter(renderer, character1, character2, character3, dizzy1, dizzy2, facingLeft, inContactWithBee, dizzyStartTime);
            // Truyền thêm isPaused và pausedTime vào drawLevelInfo
            drawLevelInfo(renderer, font, level, plantedFlower, beeCount, lives, levelStartTime, seeds, isPaused, pausedTime);

            SDL_RenderCopy(renderer, pauseButton, nullptr, &pauseRect);

            if (isPaused) {
                SDL_RenderCopy(renderer, pausing, nullptr, &pausingRect);
                SDL_RenderCopy(renderer, continueButton, nullptr, &continueRect);
                SDL_RenderCopy(renderer, exitButton, nullptr, &exitRect);
            }
            if (showDirection) {
                drawDirection(renderer, showDirection, currentPage, nextRect, backRect, closeRect);
            }

            if (gameLost) {
                SDL_Rect gameOverRect = {SCREEN_WIDTH / 2 - 750 / 2, SCREEN_HEIGHT / 2 - 550 / 2, 750, 550};
                SDL_RenderCopy(renderer, gameOver, nullptr, &gameOverRect);
                SDL_Delay(2000);
                running = false;
            }

            SDL_RenderPresent(renderer);
        }
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(background);
    quitSDL(window, renderer);
    return 0;
}
