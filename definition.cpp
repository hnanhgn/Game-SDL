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


SDL_Rect nextRect = {350, 520, 50, 20};
SDL_Rect backRect = {300, 520, 50, 20};
SDL_Rect closeRect = {720, 150, 60, 50};

SDL_Rect level1Button = {100, 400, 200, 200};
SDL_Rect level2Button = {250, 500, 200, 200};
SDL_Rect level3Button = {450, 400, 200, 200};
SDL_Rect level4Button = {700, 500, 200, 200};

SDL_Rect pauseRect = {750, 430, 300, 250}; // Nút pause ở góc phải dưới
SDL_Rect pausingRect = {SCREEN_WIDTH / 2 - 550 / 2, SCREEN_HEIGHT / 2 - 450 / 2, 550, 450};
SDL_Rect continueRect = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 10, 180, 100}; // Nút tiếp tục
SDL_Rect exitRect = {SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 10, 180, 100}; // Nút thoát

Uint32 currentTime = SDL_GetTicks();

vector<Plant> plants;
vector<Bee> bees;

int seeds = 10;
int plantedFlower = 0;
int lives = 5;
int level = 1;
int beeCount = 0;
int currentPage = 1;

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

SDL_Texture* direction1;
SDL_Texture* direction2;
SDL_Texture* nextButton;
SDL_Texture* backButton;
SDL_Texture* closeButton;

SDL_Texture* pauseButton;
SDL_Texture* pausing;
SDL_Texture* continueButton;
SDL_Texture* exitButton;

SDL_Texture* levelPreview = nullptr;


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

    direction1 = loadTexture("direction1.png", renderer);
    direction2 = loadTexture("direction2.png", renderer);
    nextButton = loadTexture("next.png", renderer);
    backButton = loadTexture("back.png", renderer);
    closeButton = loadTexture("close.png", renderer);

    pauseButton = loadTexture("pause.png", renderer);
    pausing = loadTexture("pausing.png", renderer);
    continueButton = loadTexture("continue.png", renderer);
    exitButton = loadTexture("exit.png", renderer);

    levelPreview = loadTexture("levelPreview.png", renderer);

    dizzy1 = loadTexture("dizzy1.png", renderer);
    dizzy2 = loadTexture("dizzy2.png", renderer);

    gameOver = loadTexture("gameOver.png", renderer);
}
