#include "button.h"
#include <iostream>

void handleWelcomeScreenEvents(SDL_Event& event, bool& showWelcomeScreen, bool& showLoadingScreen,
                               bool& showDirection, int& currentPage, bool& running) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        SDL_Point mousePoint = {mouseX, mouseY};

        if (SDL_PointInRect(&mousePoint, &playButton)) {
            showWelcomeScreen = false;
            showLoadingScreen = true;
        }
        if (!showDirection && SDL_PointInRect(&mousePoint, &directionButton)) {
            showDirection = true;
            currentPage = 1;
        }
        if (showDirection) {
            if (SDL_PointInRect(&mousePoint, &nextRect) && currentPage == 1) currentPage = 2;
            if (SDL_PointInRect(&mousePoint, &backRect) && currentPage == 2) currentPage = 1;
            if (SDL_PointInRect(&mousePoint, &closeRect)){
                showDirection = false;
                currentPage = 1;
            }
        }
        if (SDL_PointInRect(&mousePoint, &exitNow) && !showDirection)
            running = false;

    }
}

void chooseLevel(SDL_Renderer* renderer, SDL_Texture* levelPreviewTexture, bool& showLevelPreview, int& level,
                 SDL_Event& event, bool& loaded, Uint32& levelStartTime, int& lives, int& seeds, int& plantedFlower,
                 int& beeCount, std::vector<Bee>& bees, std::vector<Plant>& plants, TTF_Font* font, bool& isPaused,
                 bool& wasPaused, bool& pausedTimeSet, Uint32& PausedTime, bool& running ) {


    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        SDL_Point mousePoint = {mouseX, mouseY};

        if (SDL_PointInRect(&mousePoint, &level1Button)) {
            level = 1;
            lives = 4;
            seeds = 10;
            plantedFlower = 0;
            beeCount = 0;
            bees.clear();
            plants.clear();
            showLevelPreview = false;
            loaded = true;
            levelStartTime = 0;
            isPaused = false;
            wasPaused = false;
            pausedTimeSet = false;
            PausedTime = 0;
        }
        else if (SDL_PointInRect(&mousePoint, &level2Button) && completedLevel[0]) {
            level = 2;
            lives = 4;
            seeds = 10;
            plantedFlower = 0;
            beeCount = 1;
            bees.clear();
            plants.clear();
            for (int i = 0; i < 1; i++) {
                Bee newBee;
                newBee.rect = {rand() % 800, rand() % 600, BEE_WIDTH, BEE_HEIGHT};
                newBee.moveTime = SDL_GetTicks();
                newBee.velocityX = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;
                newBee.velocityY = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;
                bees.push_back(newBee);
            }
            showLevelPreview = false;
            loaded = true;
            levelStartTime = 0;
            isPaused = false;
            wasPaused = false;
            pausedTimeSet = false;
            PausedTime = 0;
        }
        else if (SDL_PointInRect(&mousePoint, &level3Button) && completedLevel[0] && completedLevel[1]) {
            level = 3;
            lives = 5;
            seeds = 10;
            plantedFlower = 0;
            beeCount = 2;
            bees.clear();
            plants.clear();
            for (int i = 0; i < 2; i++) {
                Bee newBee;
                newBee.rect = {rand() % 800, rand() % 600, BEE_WIDTH, BEE_HEIGHT};
                newBee.moveTime = SDL_GetTicks();
                newBee.velocityX = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;
                newBee.velocityY = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;
                bees.push_back(newBee);
            }
            showLevelPreview = false;
            loaded = true;
            levelStartTime = 0;
            isPaused = false;
            wasPaused = false;
            pausedTimeSet = false;
            PausedTime = 0;
        }
        else if (SDL_PointInRect(&mousePoint, &level4Button) && completedLevel[0] && completedLevel[1] && completedLevel[2]) {
            level = 4;
            lives = 5;
            seeds = 10;
            plantedFlower = 0;
            beeCount = 3;
            bees.clear();
            plants.clear();
            for (int i = 0; i < 3; i++) {
                Bee newBee;
                newBee.rect = {rand() % 800, rand() % 600, BEE_WIDTH, BEE_HEIGHT};
                newBee.moveTime = SDL_GetTicks();
                newBee.velocityX = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;
                newBee.velocityY = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;
                bees.push_back(newBee);
            }
            showLevelPreview = false;
            loaded = true;
            levelStartTime = 0;
            isPaused = false;
            wasPaused = false;
            pausedTimeSet = false;
            PausedTime = 0;
        }

        else if (SDL_PointInRect(&mousePoint, &exitLevel))
            running = false;

    }
}

void handleGameEvents(SDL_Event& event, bool& showDirection, int& currentPage, bool& facingLeft,
                      SDL_Rect& playerRect, int& seeds, int& plantedFlower, bool& isPaused, bool& running,
                      bool& showPassScreen, bool& showLevelPreview, bool& loaded, int& level, int& lives,
                      bool& showGameOverScreen, bool state, Uint32& levelStartTime) {
    static bool inContactWithBee = false;
    static Uint32 dizzyStartTime = 0;

    if (event.type == SDL_KEYDOWN && !showDirection && !isPaused && !showPassScreen && !showGameOverScreen) {
        if (event.key.keysym.sym == SDLK_SPACE)
            dropSeed(playerRect, seeds, plantedFlower);
        if (event.key.keysym.sym == SDLK_RETURN)
            pickFlower(playerRect, seeds, plantedFlower);
        if (event.key.keysym.sym == SDLK_LEFT)
            facingLeft = true;
        if (event.key.keysym.sym == SDLK_RIGHT)
            facingLeft = false;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        SDL_Point mousePoint = {mouseX, mouseY};

        if (!showDirection && !isPaused && !showPassScreen && !showGameOverScreen && SDL_PointInRect(&mousePoint, &pauseRect)) {
            isPaused = true;
        }
        else if (!state && isPaused && SDL_PointInRect(&mousePoint, &continueRect)) {
            isPaused = false;
        }
        else if (isPaused && SDL_PointInRect(&mousePoint, &exitRect)) {
            running = false;
        }
        else if (!showDirection && !isPaused && !showPassScreen && !showGameOverScreen && SDL_PointInRect(&mousePoint, &directionButton)) {
            showDirection = true;
            currentPage = 1;
        }
        else if (showDirection) {
            if (SDL_PointInRect(&mousePoint, &nextRect) && currentPage == 1) currentPage = 2;
            if (SDL_PointInRect(&mousePoint, &backRect) && currentPage == 2) currentPage = 1;
            if (SDL_PointInRect(&mousePoint, &closeRect)){
                showDirection = false;
                currentPage = 1;
            }
        }
        else if (showPassScreen) {
            if (SDL_PointInRect(&mousePoint, &menuRect)) {

                showPassScreen = false;
                showLevelPreview = true;
                loaded = false;
                isPaused = false;
                completedLevel[level - 1] = true;

                if (level < 4) {
                    level++;
                }
            }
            else if (SDL_PointInRect(&mousePoint, &playAgainRect)) {

                showPassScreen = false;
                loaded = true;
                isPaused = false;
                levelStartTime = 0;
                completedLevel[level - 1] = true;

                switch (level) {
                    case 1: lives = 4; seeds = 10; break;
                    case 2: lives = 4; seeds = 10; break;
                    case 3: lives = 5; seeds = 10; break;
                    case 4: lives = 5; seeds = 10; break;
                }
                plantedFlower = 0;
                bees.clear();
                plants.clear();
            }
            else if (SDL_PointInRect(&mousePoint, &passExitRect)) {
                completedLevel[level - 1] = true;
                running = false;
            }
        }
        else if (showGameOverScreen) {
            if (SDL_PointInRect(&mousePoint, &gameOverPlayAgainRect)) {

                showGameOverScreen = false;
                loaded = true;
                isPaused = false;
                levelStartTime = 0;

                switch (level) {
                    case 1: lives = 4; seeds = 10; break;
                    case 2: lives = 4; seeds = 10; break;
                    case 3: lives = 5; seeds = 10; break;
                    case 4: lives = 5; seeds = 10; break;
                }
                plantedFlower = 0;
                bees.clear();
                plants.clear();
                inContactWithBee = false;
            }
            else if (SDL_PointInRect(&mousePoint, &gameOverExitRect)) {
                running = false;
            }
        }
    }
}

void handleSoundButtonClick(SDL_Event& event, bool& isSoundOn) {
    int mouseX = event.button.x;
    int mouseY = event.button.y;
    SDL_Point mousePoint = {mouseX, mouseY};

    if (SDL_PointInRect(&mousePoint, &soundButton)) {

        isSoundOn = !isSoundOn;


        if(isSoundOn) {
            Mix_ResumeMusic();
            Mix_Volume(-1, MIX_MAX_VOLUME);
        }
        else {
            Mix_PauseMusic();
            Mix_Volume(-1, 0);
        }
    }
}
