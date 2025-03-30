#ifndef CHARACTERMOVEMENT_H_INCLUDED
#define CHARACTERMOVEMENT_H_INCLUDED

#include <SDL.h>

#include "definition.h"
#include "textureManager.h"

using namespace std;

void updateMovement (SDL_Rect& playerRect);

void dropSeed(SDL_Rect& playerRect, int& seeds, int& plantedFlowers);
void pickFlower(SDL_Rect& playerRect, int& seeds, int& score);
bool checkContactWithBee (SDL_Rect& characterRect, vector<Bee>& bees);
void handleCollisionWithBee(int& lives, bool& inContactWithBee, Uint32& dizzyStartTime);

#endif // CHARACTERMOVEMENT_H_INCLUDED
