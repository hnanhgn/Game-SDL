#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "definition.h"

using namespace std;

SDL_Texture* loadTexture( std::string path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void drawCharacter(SDL_Renderer* renderer, SDL_Texture* character)
{
    SDL_RenderCopy(renderer, character, nullptr, &playerRect);
    SDL_RenderPresent(renderer);

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
