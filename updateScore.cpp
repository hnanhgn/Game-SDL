#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "definition.h"

void updateScore(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color textColor = {255, 255, 255, 255};  // Màu trắng

    string scoreText = to_string(score);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect = {20, 20, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    //SDL_FreeSurface(textSurface);
    //SDL_DestroyTexture(textTexture);
}
