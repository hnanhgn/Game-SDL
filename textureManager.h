#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <string>

SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
void drawCharacter(SDL_Renderer* renderer, SDL_Texture* character);
void drawBackground(SDL_Renderer* renderer, SDL_Texture* background);
void drawPlants(SDL_Renderer* renderer, SDL_Texture* seed, SDL_Texture* sprout, SDL_Texture* bud, SDL_Texture* flower);

#endif // TEXTUREMANAGER_H_INCLUDED
