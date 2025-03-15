#ifndef CHARACTERMOVEMENT_H_INCLUDED
#define CHARACTERMOVEMENT_H_INCLUDED

#include <SDL.h>
#include <vector>

using namespace std;

void updateMovement(SDL_Rect& playerRect);
void dropSeed( SDL_Rect& playerRect);
void pickFlower(SDL_Rect& playerRect);

#endif // CHARACTERMOVEMENT_H_INCLUDED
