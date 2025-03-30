#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>

#include "definition.h"
#include "textureManager.h"

using namespace std;

SDL_Renderer* renderer = nullptr;
SDL_Rect playerRect = {SCREEN_WIDTH / 2 - CHARACTER_WIDTH / 2, SCREEN_HEIGHT / 2 - CHARACTER_HEIGHT / 2, CHARACTER_WIDTH, CHARACTER_HEIGHT};

SDL_Rect playButton = { 70, 450, 150, 120 };
SDL_Rect directionButton = { 180, 450, 150, 120 };
SDL_Rect exitNow = {290, 450, 150, 120};

SDL_Rect nextRect = {350, 520, 50, 20};
SDL_Rect backRect = {300, 520, 50, 20};
SDL_Rect closeRect = {720, 150, 60, 50};

SDL_Rect level1Button = {100, 400, 200, 200};
SDL_Rect level2Button = {250, 500, 200, 200};
SDL_Rect level3Button = {450, 400, 200, 200};
SDL_Rect level4Button = {700, 500, 200, 200};
SDL_Rect exitLevel = {50, 600, 120, 90};

SDL_Rect pauseRect = {750, 430, 300, 240};
SDL_Rect pausingRect = {SCREEN_WIDTH / 2 - 550 / 2, SCREEN_HEIGHT / 2 - 450 / 2, 550, 450};
SDL_Rect continueRect = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 10, 180, 100};
SDL_Rect exitRect = {SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 10, 180, 100};

SDL_Rect passLevelRect = {SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 330 / 2, 500, 330};
SDL_Rect menuRect = {SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 + 10 , 100, 50};
SDL_Rect playAgainRect = {SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 + 10 , 100, 50};
SDL_Rect passExitRect = {SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT / 2 + 10 , 100, 50};

SDL_Rect gameOverRect = {SCREEN_WIDTH / 2 - 375, SCREEN_HEIGHT / 2 - 275, 750, 550};
SDL_Rect gameOverPlayAgainRect = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 60, 130, 100};
SDL_Rect gameOverExitRect = {SCREEN_WIDTH / 2 + 130, SCREEN_HEIGHT / 2 + 60, 130, 100};

SDL_Rect soundButton = {900, 40, 50, 50};

SDL_Rect winRect = {SCREEN_WIDTH / 2 - 450, SCREEN_HEIGHT / 2 - 300, 900, 600};

Uint32 currentTime = SDL_GetTicks();

vector<Plant> plants;
vector<Bee> bees;

int seeds = 10;
int plantedFlower = 0;
int lives = 5;
int level = 1;
int beeCount = 0;
int currentPage = 1;
int levelStartTime = 0;

bool completedLevel[4] = {false, false, false, false};

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
SDL_Texture* exitEarly;

SDL_Texture* pauseButton;
SDL_Texture* pausing;
SDL_Texture* continueButton;
SDL_Texture* exitButton;

SDL_Texture* passLevel;
SDL_Texture* menuButton;
SDL_Texture* playAgainButton;
SDL_Texture* passExitButton;

SDL_Texture* levelPreview = nullptr;
SDL_Texture* star;
SDL_Texture* lock;

SDL_Texture* dizzy1 = nullptr;
SDL_Texture* dizzy2 = nullptr;

SDL_Texture* gameOver = nullptr;

SDL_Texture* win = nullptr;

SDL_Texture* soundOn;
SDL_Texture* soundOff;


void loadTextures(SDL_Renderer* renderer) {
    background = loadTexture("pics/background.png", renderer);
    beforeGame = loadTexture("pics/beforeGame.png", renderer);

    character1 = loadTexture("pics/flyStep1.png", renderer);
    character2 = loadTexture("pics/flyStep2.png", renderer);
    character3 = loadTexture("pics/flyStep3.png", renderer);


    flowerGrowthStep = loadTexture("pics/flowerGrowth.png", renderer);

    bee = loadTexture("pics/bee.png", renderer);

    welcome = loadTexture("pics/welcomeBg.png", renderer);
    playIcon = loadTexture("pics/playButton.png", renderer);
    directionIcon = loadTexture("pics/directionButton.png", renderer);

    direction1 = loadTexture("pics/direction1.png", renderer);
    direction2 = loadTexture("pics/direction2.png", renderer);
    nextButton = loadTexture("pics/next.png", renderer);
    backButton = loadTexture("pics/back.png", renderer);
    closeButton = loadTexture("pics/close.png", renderer);
    exitEarly = loadTexture("pics/exitEarly.png", renderer);

    pauseButton = loadTexture("pics/pause.png", renderer);
    pausing = loadTexture("pics/pausing.png", renderer);
    continueButton = loadTexture("pics/continue.png", renderer);
    exitButton = loadTexture("pics/exit.png", renderer);

    passLevel = loadTexture("pics/passLevel.png", renderer);
    menuButton = loadTexture("pics/backMenu.png", renderer);
    playAgainButton = loadTexture("pics/playAgain.png", renderer);
    passExitButton = loadTexture("pics/exit.png", renderer);

    levelPreview = loadTexture("pics/levelPreview.png", renderer);
    star = loadTexture("pics/star.png", renderer);
    lock = loadTexture("pics/lock.png", renderer);

    dizzy1 = loadTexture("pics/dizzy1.png", renderer);
    dizzy2 = loadTexture("pics/dizzy2.png", renderer);

    gameOver = loadTexture("pics/gameOver.png", renderer);

    win = loadTexture("pics/win.png", renderer);

    soundOn = loadTexture("pics/soundOn.png", renderer);
    soundOff = loadTexture("pics/soundOff.png", renderer);
}

