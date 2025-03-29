#include "button.h"
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
                 int& beeCount, std::vector<Bee>& bees, std::vector<Plant>& plants, TTF_Font* font, bool& isPaused, bool& wasPaused, bool& pausedTimeSet, Uint32& PausedTime) {
    SDL_RenderCopy(renderer, levelPreviewTexture, nullptr, nullptr);

    /*SDL_Rect starRect = {0, 0, 40, 40};
    if (completedLevel[0]) {
        starRect.x = level1Button.x + level1Button.w - 40;
        starRect.y = level1Button.y;
        SDL_RenderCopy(renderer, star, nullptr, &starRect);
    }
    if (completedLevel[1]) {
        starRect.x = level2Button.x + level2Button.w - 40;
        starRect.y = level2Button.y;
        SDL_RenderCopy(renderer, star, nullptr, &starRect);
    }
    if (completedLevel[2]) {
        starRect.x = level3Button.x + level3Button.w - 40;
        starRect.y = level3Button.y;
        SDL_RenderCopy(renderer, star, nullptr, &starRect);
    }
    if (completedLevel[3]) {
        starRect.x = level4Button.x + level4Button.w - 40;
        starRect.y = level4Button.y;
        SDL_RenderCopy(renderer, star, nullptr, &starRect);
    }*/



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
            isPaused = false;   // Reset trạng thái pause
            wasPaused = false;  // Reset biến theo dõi trạng thái pause trước đó
            pausedTimeSet = false; // Reset biến đánh dấu đã thiết lập thời gian pause
            PausedTime = 0;     // Reset thời gian tạm dừng
        }
        else if (SDL_PointInRect(&mousePoint, &level2Button)) {
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
            isPaused = false;   // Reset trạng thái pause
            wasPaused = false;  // Reset biến theo dõi trạng thái pause trước đó
            pausedTimeSet = false; // Reset biến đánh dấu đã thiết lập thời gian pause
            PausedTime = 0;     // Reset thời gian tạm dừng
        }
        else if (SDL_PointInRect(&mousePoint, &level3Button)) {
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
            isPaused = false;   // Reset trạng thái pause
            wasPaused = false;  // Reset biến theo dõi trạng thái pause trước đó
            pausedTimeSet = false; // Reset biến đánh dấu đã thiết lập thời gian pause
            PausedTime = 0;     // Reset thời gian tạm dừng
        }
        else if (SDL_PointInRect(&mousePoint, &level4Button)) {
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
            isPaused = false;   // Reset trạng thái pause
            wasPaused = false;  // Reset biến theo dõi trạng thái pause trước đó
            pausedTimeSet = false; // Reset biến đánh dấu đã thiết lập thời gian pause
            PausedTime = 0;     // Reset thời gian tạm dừng
        }
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
                // Chuyển sang màn hình chọn level
                showPassScreen = false;
                showLevelPreview = true;
                loaded = false;
                isPaused = false; // Đặt lại trạng thái pause
                completedLevel[level - 1] = true;
                //lastSeeds = seeds;
                if (level < 4) {
                    level++;
                }
            }
            else if (SDL_PointInRect(&mousePoint, &playAgainRect)) {
                // Chơi lại level hiện tại
                showPassScreen = false;
                loaded = true;
                isPaused = false; // Đặt lại trạng thái pause
                levelStartTime = 0; // Reset thời gian về giá trị hiện tại
                completedLevel[level - 1] = true;
                //lastSeeds = seeds;
                // Reset các giá trị của level
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
                //lastSeeds = seeds;
                running = false;
            }
        }
        else if (showGameOverScreen) {
            if (SDL_PointInRect(&mousePoint, &gameOverPlayAgainRect)) {
                // Chơi lại level hiện tại
                showGameOverScreen = false;
                loaded = true;
                isPaused = false;
                levelStartTime = 0;
                // Reset các giá trị của level
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
