#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <string>

SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
void drawCharacter(SDL_Renderer* renderer, SDL_Texture* character1, SDL_Texture* character2, SDL_Texture* character3, bool facingLeft);
void drawBackground(SDL_Renderer* renderer, SDL_Texture* background);
void drawPlants(SDL_Renderer* renderer, SDL_Texture* seed, SDL_Texture* sprout, SDL_Texture* bud, SDL_Texture* flower);
void drawBees(SDL_Renderer* renderer, SDL_Texture* bee);
void drawWelcomeScreen(SDL_Renderer* renderer, SDL_Texture* welcome, SDL_Texture* playIcon, SDL_Texture* directionIcon);

#endif // TEXTUREMANAGER_H_INCLUDED
