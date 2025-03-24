#ifndef CHARACTERMOVEMENT_H_INCLUDED
#define CHARACTERMOVEMENT_H_INCLUDED

#include <SDL.h>

#include "definition.h"
#include "textureManager.h"

using namespace std;

void updateMovement (SDL_Rect& playerRect);
void dropSeed( SDL_Rect& playerRect);
void pickFlower(SDL_Rect& playerRect);
bool checkContactWithBee (SDL_Rect& characterRect, vector<Bee>& bees);
void handleCollisionWithBee(SDL_Renderer* renderer, SDL_Texture* dizzy1, SDL_Texture* dizzy2,
                            SDL_Rect& playerRect, int& lives, Uint32& dizzyStartTime);

#endif // CHARACTERMOVEMENT_H_INCLUDED
