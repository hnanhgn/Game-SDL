#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

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


void drawCharacter(SDL_Renderer* renderer, SDL_Texture* character1, SDL_Texture* character2, SDL_Texture* character3, bool facingLeft)
{
    static Uint32 lastFrameChange = 0;
    static int frame = 0;
    static int direction = 1;

    if (SDL_GetTicks() - lastFrameChange > 200) {
        frame += direction;

        if (frame == 3) direction = -1;
        if (frame == 1) direction = 1;

        lastFrameChange = SDL_GetTicks();
    }

    SDL_Texture* currentCharacter = nullptr;
    if (frame == 1) currentCharacter = character1;
    if (frame == 2) currentCharacter = character2;
    if (frame == 3) currentCharacter = character3;

    SDL_RendererFlip flipType = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    SDL_RenderCopyEx(renderer, currentCharacter, nullptr, &playerRect, 0, nullptr, flipType);

}

void drawBackground(SDL_Renderer* renderer, SDL_Texture* background)
{

    SDL_RenderCopy(renderer, background, nullptr, nullptr);
    SDL_RenderPresent(renderer);

}

void drawPlants(SDL_Renderer* renderer, SDL_Texture* seed, SDL_Texture* sprout,SDL_Texture* bud, SDL_Texture* flower) {
    for (auto& plant : plants) {
        SDL_Texture* texture = nullptr;
        SDL_Rect drawRect = plant.rect;

        Uint32 elapsedTime = currentTime - plant.plantedTime;

        if (elapsedTime >= 6000) {
            plant.stage = FLOWER_STAGE;
            texture = flower;
            drawRect.w = 80;
            drawRect.h = 80;
            drawRect.x = plant.rect.x ;
            drawRect.y = plant.rect.y - 30;
        }
        else if (elapsedTime >= 4000) {
            plant.stage = BUD_STAGE;
            texture = bud;
            drawRect.w = 80;
            drawRect.h = 70;
            drawRect.x = plant.rect.x ;
            drawRect.y = plant.rect.y - 30;
        }
        else if (elapsedTime >= 2000) {
            plant.stage = SPROUT_STAGE;
            texture = sprout;
            drawRect.w = 80;
            drawRect.h = 40;
            drawRect.x = plant.rect.x - 2;
            drawRect.y = plant.rect.y - 10;
        }
        else {
            plant.stage = SEED_STAGE;
            texture = seed;
            drawRect.w = 20;
            drawRect.h = 20;
        }

        if (texture != nullptr)
            SDL_RenderCopy(renderer, texture, nullptr, &drawRect);

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
    int DELAY_TIME = 600;


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


void drawHearts(SDL_Renderer* renderer, SDL_Texture* heart) {
    // Nếu vector hearts trống, khởi tạo vị trí 5 trái tim
    if (hearts.empty()) {
        for (int i = 0; i < 5; i++) {
            SDL_Rect heartRect = { 10 + i * (HEART_WIDTH + 5), 10, HEART_WIDTH, HEART_HEIGHT };
            hearts.push_back(heartRect);
        }
    }
    // Vẽ số trái tim tương ứng với số mạng còn lại (lives)
    for (int i = 0; i < lives; i++) {
        SDL_RenderCopy(renderer, heart, nullptr, &hearts[i]);
    }
}

