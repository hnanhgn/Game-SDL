#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "definition.h"
#include "textureManager.h"

using namespace std;

SDL_Renderer* renderer = nullptr;
SDL_Rect playerRect = {SCREEN_WIDTH / 2 - CHARACTER_WIDTH / 2, SCREEN_HEIGHT / 2 - CHARACTER_HEIGHT / 2, CHARACTER_WIDTH, CHARACTER_HEIGHT};

SDL_Rect playButton = { 100, 450, 150, 120 };
SDL_Rect directionButton = { 250, 450, 150, 120 };
Uint32 currentTime = SDL_GetTicks();

vector<Plant> plants;
vector<Bee> bees;

int seeds = 10;
int plantedFlower = 0;
int lives = 5;
int level = 1;
int beeCount = 0;

vector<SDL_Rect> hearts;


SDL_Texture* background = nullptr;
SDL_Texture* beforeGame = nullptr;

SDL_Texture* character1 = nullptr;
SDL_Texture* character2 = nullptr;
SDL_Texture* character3 = nullptr;

SDL_Texture* flowerGrowthStep = nullptr;

SDL_Texture* bee = nullptr;

SDL_Texture* welcome = nullptr;
SDL_Texture* playIcon = nullptr;
SDL_Texture* directionIcon = nullptr;

SDL_Texture* dizzy1 = nullptr;
SDL_Texture* dizzy2 = nullptr;

SDL_Texture* gameOver = nullptr;


void loadTextures(SDL_Renderer* renderer) {
    background = loadTexture("background.png", renderer);
    beforeGame = loadTexture("beforeGame.png", renderer);

    character1 = loadTexture("flyStep1.png", renderer);
    character2 = loadTexture("flyStep2.png", renderer);
    character3 = loadTexture("flyStep3.png", renderer);


    flowerGrowthStep = loadTexture("flowerGrowth.png", renderer);

    bee = loadTexture("bee.png", renderer);

    welcome = loadTexture("welcomeBg.png", renderer);
    playIcon = loadTexture("playButton.png", renderer);
    directionIcon = loadTexture("directionButton.png", renderer);

    dizzy1 = loadTexture("dizzy1.png", renderer);
    dizzy2 = loadTexture("dizzy2.png", renderer);

    gameOver = loadTexture("gameOver.png", renderer);
}
