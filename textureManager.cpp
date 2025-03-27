#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

#include "textureManager.h"
#include "definition.h"


using namespace std;

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}


void drawCharacter(SDL_Renderer* renderer, SDL_Texture* character1, SDL_Texture* character2, SDL_Texture* character3,
                    SDL_Texture* dizzy1, SDL_Texture* dizzy2, bool facingLeft,
                    bool inContactWithBee, Uint32 dizzyStartTime)
{
    SDL_Texture* currentCharacter = nullptr;

    // Hiển thị hiệu ứng dizzy nếu nhân vật đang bị choáng
    if (inContactWithBee && SDL_GetTicks() - dizzyStartTime <= 4000) {
        currentCharacter = ((SDL_GetTicks() / 300) % 2 == 0) ? dizzy1 : dizzy2;
    }
    else {
        // Duyệt animation bình thường khi không bị choáng
        static Uint32 lastFrameChange = 0;
        static int frame = 0;
        static int direction = 1;

        if (SDL_GetTicks() - lastFrameChange > 200) {
            frame += direction;

            if (frame == 3) direction = -1;
            if (frame == 1) direction = 1;

            lastFrameChange = SDL_GetTicks();
        }

        if (frame == 1) currentCharacter = character1;
        if (frame == 2) currentCharacter = character2;
        if (frame == 3) currentCharacter = character3;
    }

    SDL_RendererFlip flipType = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, currentCharacter, nullptr, &playerRect, 0, nullptr, flipType);
}

void drawBackground(SDL_Renderer* renderer, SDL_Texture* background)
{

    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_RenderPresent(renderer);

}



void drawPlants(SDL_Renderer* renderer, SDL_Texture* plantTexture) {

    for (auto& plant : plants) {
        SDL_Rect srcRect;
        srcRect.x = static_cast<int>(plant.stage) * 267;
        srcRect.y = 0;
        srcRect.w = 267;
        srcRect.h = 187;


        SDL_Rect drawRect = plant.rect;
        drawRect.w *= 3;
        drawRect.h *= 3;
        drawRect.x -= (drawRect.w - plant.rect.w) / 2;
        drawRect.y -= (drawRect.h - plant.rect.h) / 2;

        SDL_RenderCopy(renderer, plantTexture, &srcRect, &drawRect);
    }

}

void drawBees(SDL_Renderer* renderer, SDL_Texture* bee) {
    for (auto& aBee : bees) {
        SDL_RenderCopy(renderer, bee, nullptr, &aBee.rect);
    }
}

void drawWelcomeScreen(SDL_Renderer* renderer, SDL_Texture* welcome, SDL_Texture* playIcon, SDL_Texture* directionIcon) {
    SDL_RenderCopy(renderer, welcome, nullptr, nullptr);
    SDL_RenderCopy(renderer, playIcon, nullptr, &playButton);
    SDL_RenderCopy(renderer, directionIcon, nullptr, &directionButton);
}

void drawLoadingScreen(SDL_Renderer* renderer, SDL_Texture* beforeGame)
{
    int DELAY_TIME = 500;


    SDL_Rect srcRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_Rect destRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    for (int i = 0; i < 6; ++i) {
        srcRect.x = i * srcRect.w;

        //SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, beforeGame, &srcRect, &destRect);
        SDL_RenderPresent(renderer);

        SDL_Delay(DELAY_TIME);
    }

}


void drawDirection(SDL_Renderer* renderer, bool& showDirection, int& currentPage, SDL_Rect& nextRect, SDL_Rect& backRect, SDL_Rect& closeRect)
{
    // Vẽ nền direction (màu xám nhạt nếu không có texture nền riêng)
    /*SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_Rect directionBackground = {0, 0, 800, 600}; // Giả định màn hình 800x600
    SDL_RenderFillRect(renderer, &directionBackground);*/

    // Vẽ trang 1 hoặc trang 2
    SDL_Rect pageRect = {SCREEN_WIDTH / 2 - 700 / 2, SCREEN_HEIGHT / 2 - 500 / 2,  700, 500}; // Kích thước và vị trí của trang direction
    if (currentPage == 1) {
        SDL_RenderCopy(renderer, direction1, nullptr, &pageRect);
        SDL_RenderCopy(renderer, nextButton, nullptr, &nextRect); // Nút Next
    }
    if (currentPage == 2) {
        SDL_RenderCopy(renderer, direction2, nullptr, &pageRect);
        SDL_RenderCopy(renderer, backButton, nullptr, &backRect); // Nút Back
    }

    // Vẽ nút Close
    SDL_RenderCopy(renderer, closeButton, nullptr, &closeRect);
}

