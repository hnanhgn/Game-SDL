#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SDL.h>
#include <vector>
#include "definition.h"
#include "characterMovement.h"
#include "textureManager.h"
#include "updateScore.h"

// Xử lý sự kiện cho màn hình welcome
void handleWelcomeScreenEvents(SDL_Event& event, bool& showWelcomeScreen, bool& showLoadingScreen,
                               bool& showDirection, int& currentPage);

// Xử lý sự kiện cho màn hình chọn level
void chooseLevel(SDL_Renderer* renderer, SDL_Texture* levelPreviewTexture, bool& showLevelPreview, int& level,
                 SDL_Rect& level1Button, SDL_Rect& level2Button, SDL_Rect& level3Button, SDL_Rect& level4Button,
                 SDL_Event& event, bool& loaded, Uint32& levelStartTime, int& lives, int& seeds, int& plantedFlower,
                 int& beeCount, std::vector<Bee>& bees, std::vector<Plant>& plants);

// Xử lý sự kiện trong game
void handleGameEvents(SDL_Event& event, bool& showDirection, int& currentPage, bool& facingLeft,
                      SDL_Rect& playerRect, int& seeds, int& plantedFlower, bool& isPaused, bool& running);

#endif // BUTTON_H_INCLUDED
