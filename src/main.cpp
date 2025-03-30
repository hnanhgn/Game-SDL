#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string.h>
#include <vector>

#include "include/definition.h"
#include "include/textureManager.h"
#include "include/characterMovement.h"
#include "include/flowerGrowth.h"
#include "include/updateScore.h"
#include "include/beeOperation.h"
#include "include/button.h"

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

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    logSDLError(cout, "Mix_OpenAudio", true);

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

    Mix_Music* backgroundMusic = Mix_LoadMUS("sounds/music.mp3");
    Mix_Chunk* clickSound = Mix_LoadWAV("sounds/click.wav");
    Mix_Chunk* crySound = Mix_LoadWAV("sounds/cry.wav");
    Mix_Chunk* happySound = Mix_LoadWAV("sounds/happy.wav");



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
    bool showPassScreen = false;
    bool showGameOverScreen = false;
    bool state = false;
    bool isPaused = false;
    bool wasPaused = false;
    bool pausedTimeSet;
    bool isSoundOn = true;
    Uint32 levelStartTime = 0;
    Uint32 dizzyStartTime = 0;
    Uint32 currentTime = 0;
    Uint32 pausedTime = 0;
    SDL_Event event;


    Mix_PlayMusic(backgroundMusic, -1);

    loadLevelProgress();

    while (running) {
        currentTime = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                handleSoundButtonClick(event, isSoundOn);
                Mix_PlayChannel(-1, clickSound, 0);
            }

            if (showWelcomeScreen)
                handleWelcomeScreenEvents(event, showWelcomeScreen, showLoadingScreen, showDirection, currentPage, running);

            if (showLevelPreview){
                chooseLevel(renderer, levelPreview, showLevelPreview, level,
                            event, loaded, levelStartTime, lives, seeds, plantedFlower,
                            beeCount, bees, plants, font, isPaused, wasPaused, pausedTimeSet, pausedTime, running);
            }
            if (!showWelcomeScreen && loaded && !showLevelPreview) {
                handleGameEvents(event, showDirection, currentPage, facingLeft, playerRect, seeds, plantedFlower,
                                 isPaused, running, showPassScreen, showLevelPreview, loaded, level, lives,
                                 showGameOverScreen, state, levelStartTime);

                if (isPaused && !pausedTimeSet) {
                    pausedTime = currentTime - levelStartTime;
                    pausedTimeSet = true;
                    wasPaused = true;
                }
                else if (!isPaused && wasPaused) {
                    levelStartTime = currentTime - pausedTime;
                    wasPaused = false;
                    pausedTimeSet = false;
                }
            }
        }

        SDL_RenderClear(renderer);

        if (showWelcomeScreen) {
            drawWelcomeScreen(renderer, welcome, playIcon, directionIcon);
            drawSoundButton(renderer, isSoundOn);
            if (showDirection)
                drawDirection(renderer, showDirection, currentPage, nextRect, backRect, closeRect);
            SDL_RenderPresent(renderer);
        }
        else if (showLoadingScreen && !loaded && !showLevelPreview) {
            drawLoadingScreen(renderer, beforeGame);
            showLoadingScreen = false;
            showLevelPreview = true;
            drawSoundButton(renderer, isSoundOn);
            SDL_RenderPresent(renderer);
        }
        else if (showLevelPreview) {
            SDL_RenderCopy(renderer, levelPreview, nullptr, nullptr);
            drawStar(renderer, completedLevel);
            lockLevel( renderer);
            if (completedLevel[0] && completedLevel[1] && completedLevel[2] && completedLevel[3]) {
                Mix_PlayChannel(-1, happySound, 0);
                SDL_RenderCopy(renderer, win, nullptr, &winRect);
            }
            SDL_RenderCopy(renderer, exitEarly, nullptr, &exitLevel);
            drawSoundButton(renderer, isSoundOn);
            SDL_RenderPresent(renderer);
        }
        else if (!showWelcomeScreen && loaded && !showLevelPreview) {
            if (levelStartTime == 0) {
                levelStartTime = SDL_GetTicks();
                isPaused = false;
                wasPaused = false;
                pausedTimeSet = false;
            }
            if (!showDirection && !isPaused && !showPassScreen && !showGameOverScreen) {
                updateMovement(playerRect);
                bool contactNow = checkContactWithBee(playerRect, bees);
                if (contactNow) {
                    Mix_PlayChannel(-1, crySound, 0);
                    handleCollisionWithBee(lives, inContactWithBee, dizzyStartTime);
                }
                updateFlowerGrowth(plants);
                moveBee(bees, plants);
            }
            if (checkLevelWinLose(level, plantedFlower, beeCount, levelStartTime, lives, gameWon, gameLost, state)) {
                if (gameWon) {
                    Mix_PlayChannel(-1, happySound, 0);
                    showPassScreen = true;
                    dizzyStartTime = 0;
                    isPaused = true;
                    gameWon = false;
                    levelStartTime = SDL_GetTicks();
                }
                if (gameLost) {
                    Mix_PlayChannel(-1, crySound, 0);
                    showGameOverScreen = true;
                    dizzyStartTime = 0;
                    gameLost = false;
                    isPaused = true;
                    levelStartTime = SDL_GetTicks();
                }
            }


            SDL_RenderCopy(renderer, background, nullptr, nullptr);
            addBees(level);
            drawBees(renderer, bee);
            drawPlants(renderer, flowerGrowthStep);
            drawCharacter(renderer, character1, character2, character3, dizzy1, dizzy2, facingLeft, inContactWithBee, dizzyStartTime);
            drawLevelInfo(renderer, font, level, plantedFlower, beeCount, lives, levelStartTime, seeds, isPaused, pausedTime, state);

            if (!state && isPaused)
                drawPauseNoti(renderer);

            if (showDirection)
                drawDirection(renderer, showDirection, currentPage, nextRect, backRect, closeRect);

            if (showPassScreen)
                drawPassedNoti(renderer);

            if (showGameOverScreen)
                drawGameOverNoti(renderer);

            SDL_RenderCopy(renderer, pauseButton, nullptr, &pauseRect);

            drawSoundButton(renderer, isSoundOn);

            SDL_RenderPresent(renderer);

        }
    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(welcome);
    SDL_DestroyTexture(playIcon);
    SDL_DestroyTexture(directionIcon);
    SDL_DestroyTexture(levelPreview);
    SDL_DestroyTexture(character1);
    SDL_DestroyTexture(character2);
    SDL_DestroyTexture(character3);
    SDL_DestroyTexture(dizzy1);
    SDL_DestroyTexture(dizzy2);
    SDL_DestroyTexture(flowerGrowthStep);
    SDL_DestroyTexture(bee);
    SDL_DestroyTexture(pauseButton);
    SDL_DestroyTexture(soundOn);
    SDL_DestroyTexture(soundOff);
    SDL_DestroyTexture(star);
    SDL_DestroyTexture(win);
    SDL_DestroyTexture(exitEarly);
    SDL_DestroyTexture(beforeGame);
    SDL_DestroyTexture(direction1);
    SDL_DestroyTexture(direction2);
    SDL_DestroyTexture(nextButton);
    SDL_DestroyTexture(backButton);
    SDL_DestroyTexture(closeButton);
    SDL_DestroyTexture(passLevel);
    SDL_DestroyTexture(menuButton);
    SDL_DestroyTexture(playAgainButton);
    SDL_DestroyTexture(passExitButton);
    SDL_DestroyTexture(gameOver);
    SDL_DestroyTexture(pausing);
    SDL_DestroyTexture(continueButton);
    SDL_DestroyTexture(exitButton);

    TTF_CloseFont(font);
    TTF_Quit();

    Mix_FreeChunk(clickSound);
    Mix_FreeChunk(crySound);
    Mix_FreeChunk(happySound);
    Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
    quitSDL(window, renderer);
    return 0;
}
