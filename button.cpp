#include "Button.h"
#include <iostream>

void handleWelcomeScreenEvents(SDL_Event& event, bool& showWelcomeScreen, bool& showLoadingScreen,
                               bool& showDirection, int& currentPage) {
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
    }
}

void chooseLevel(SDL_Renderer* renderer, SDL_Texture* levelPreviewTexture, bool& showLevelPreview, int& level,
                 SDL_Rect& level1Button, SDL_Rect& level2Button, SDL_Rect& level3Button, SDL_Rect& level4Button,
                 SDL_Event& event, bool& loaded, Uint32& levelStartTime, int& lives, int& seeds, int& plantedFlower,
                 int& beeCount, std::vector<Bee>& bees, std::vector<Plant>& plants) {
    // Vẽ ảnh levelPreview
    SDL_RenderCopy(renderer, levelPreviewTexture, nullptr, nullptr);

    // Xử lý sự kiện nhấp chuột
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        SDL_Point mousePoint = {mouseX, mouseY};

        if (SDL_PointInRect(&mousePoint, &level1Button)) {
            level = 1;
            lives = 5;
            seeds = 10;
            plantedFlower = 0;
            beeCount = 0;
            bees.clear();
            plants.clear();
            showLevelPreview = false;
            loaded = true;
            // Không đặt levelStartTime ở đây, sẽ đặt trong main
        }
        else if (SDL_PointInRect(&mousePoint, &level2Button)) {
            level = 2;
            lives = 5;
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
        }
        else if (SDL_PointInRect(&mousePoint, &level3Button)) {
            level = 3;
            lives = 4;
            seeds = 8;
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
        }
        else if (SDL_PointInRect(&mousePoint, &level4Button)) {
            level = 4;
            lives = 3;
            seeds = 6;
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
        }
    }


}

void handleGameEvents(SDL_Event& event, bool& showDirection, int& currentPage, bool& facingLeft,
                      SDL_Rect& playerRect, int& seeds, int& plantedFlower, bool& isPaused, bool& running) {
    if (event.type == SDL_KEYDOWN && !showDirection && !isPaused) {
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

        if (!showDirection && !isPaused && SDL_PointInRect(&mousePoint, &pauseRect)) {
            isPaused = true;
        }
        else if (isPaused && SDL_PointInRect(&mousePoint, &continueRect)) {
            isPaused = false;
        }
        else if (isPaused && SDL_PointInRect(&mousePoint, &exitRect)) {
            running = false;
        }
        /*else if (!showDirection && !isPaused && SDL_PointInRect(&mousePoint, &directionButton)) {
            showDirection = true;
            currentPage = 1;
        }
        else if (showDirection) {
            if (SDL_PointInRect(&mousePoint, &nextRect) && currentPage == 1) currentPage = 2;
            if (SDL_PointInRect(&mousePoint, &backRect) && currentPage == 2) currentPage = 1;
            if (SDL_PointInRect(&mousePoint, &closeRect)) showDirection = false;
        }*/
    }
}
