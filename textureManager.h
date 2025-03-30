#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

#include "definition.h"


using namespace std;


SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
void drawCharacter(SDL_Renderer* renderer, SDL_Texture* character1, SDL_Texture* character2,
                    SDL_Texture* character3, SDL_Texture* dizzy1, SDL_Texture* dizzy2,
                    bool facingLeft, bool inContactWithBee, Uint32 dizzyStartTime);
void drawBackground(SDL_Renderer* renderer, SDL_Texture* background);
void drawPlants(SDL_Renderer* renderer, SDL_Texture* plantTexture);
void drawBees(SDL_Renderer* renderer, SDL_Texture* bee);
void drawWelcomeScreen(SDL_Renderer* renderer, SDL_Texture* welcome, SDL_Texture* playIcon, SDL_Texture* directionIcon);
void drawLoadingScreen(SDL_Renderer* renderer, SDL_Texture* beforeGame);
void drawDirection(SDL_Renderer* renderer, bool& showDirection, int& currentPage, SDL_Rect& nextRect, SDL_Rect& backRect, SDL_Rect& closeRect);
void drawPassedNoti (SDL_Renderer* renderer);
void drawGameOverNoti (SDL_Renderer* renderer);
void drawPauseNoti (SDL_Renderer* renderer);
void drawStar (SDL_Renderer* renderer, bool completedLevel[4]);
void drawSoundButton(SDL_Renderer* renderer, bool& isSoundOn) ;

#endif // TEXTUREMANAGER_H_INCLUDED
