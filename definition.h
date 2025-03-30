#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "Loobee";

const int CHARACTER_WIDTH = 65;
const int CHARACTER_HEIGHT = 73;
const int CHARACTER_SPEED = 10;

const int BEE_WIDTH = 40;
const int BEE_HEIGHT = 40;
const int BEE_SPEED = 3;

extern SDL_Rect playerRect ;
extern SDL_Renderer* renderer;

extern SDL_Rect playButton;
extern SDL_Rect directionButton;

extern SDL_Rect nextRect;
extern SDL_Rect backRect;
extern SDL_Rect closeRect;

extern SDL_Rect level1Button ;
extern SDL_Rect level2Button ;
extern SDL_Rect level3Button ;
extern SDL_Rect level4Button ;

extern SDL_Rect pauseRect ;
extern SDL_Rect pausingRect;
extern SDL_Rect continueRect ;
extern SDL_Rect exitRect ;

extern SDL_Rect passLevelRect;
extern SDL_Rect menuRect;
extern SDL_Rect playAgainRect;
extern SDL_Rect passExitRect;

extern SDL_Rect gameOverRect;
extern SDL_Rect gameOverPlayAgainRect;
extern SDL_Rect gameOverExitRect;

extern SDL_Rect winRect;

extern SDL_Rect soundButton;

const float MIN_DISTANCE_TO_FLOWER = 200.0f;
const float WAVE_AMPLITUDE = 1.0f;
const float WAVE_FREQUENCY = 0.02f;
const float COLLECTING_TIME = 3000;
const float APPROACH_FACTOR = 0.1f;

extern int plantedFlower;
extern int seeds;
extern int level;
extern int beeCount;
extern int lives;
extern int currentPage;
extern int levelStartTime;

extern bool completedLevel[4];

enum PlantStage { SEED, SPROUT, BUD, BLOOM, WILT };

struct Plant {
    SDL_Rect rect;
    PlantStage stage;
    Uint32 plantedTime;
    int id;
};

extern Uint32 currentTime ;
extern vector<Plant> plants;

struct Bee {
    SDL_Rect rect;
    Uint32 moveTime;
    float collectTime;
    float velocityX;
    float velocityY;
};
extern vector<Bee> bees;




SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer);

extern SDL_Texture* background;
extern SDL_Texture* beforeGame;

extern SDL_Texture* character1;
extern SDL_Texture* character2;
extern SDL_Texture* character3;

extern SDL_Texture* flowerGrowthStep;

extern SDL_Texture* bee;

extern SDL_Texture* welcome;
extern SDL_Texture* playIcon;
extern SDL_Texture* directionIcon;

extern SDL_Texture* direction1;
extern SDL_Texture* direction2;
extern SDL_Texture* nextButton;
extern SDL_Texture* backButton;
extern SDL_Texture* closeButton;

extern SDL_Texture* pauseButton;
extern SDL_Texture* pausing;
extern SDL_Texture* continueButton;
extern SDL_Texture* exitButton;

extern SDL_Texture* passLevel;
extern SDL_Texture* menuButton;
extern SDL_Texture* playAgainButton;
extern SDL_Texture* passExitButton;

extern SDL_Texture* levelPreview;

extern SDL_Texture* star;

extern SDL_Texture* dizzy1;
extern SDL_Texture* dizzy2;

extern SDL_Texture* gameOver;

extern SDL_Texture* win;

extern SDL_Texture* soundOn;
extern SDL_Texture* soundOff;

void loadTextures(SDL_Renderer* renderer);


#endif // DEFINITION_H_INCLUDED
