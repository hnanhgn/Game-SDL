#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

#include <string>
#include <SDL.h>
#include <vector>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "Loobee";

const int CHARACTER_WIDTH = 150;
const int CHARACTER_HEIGHT = 130;
const int CHARACTER_SPEED = 10;

const int GRID_SIZE = 30;

const int BEE_WIDTH = 60;
const int BEE_HEIGHT = 50;
const int BEE_SPEED = 4;

extern SDL_Rect playerRect ;
extern SDL_Renderer* renderer;

extern SDL_Rect playButton;
extern SDL_Rect directionButton;

//extern SDL_Rect directionRect; // Nút Direction
extern SDL_Rect nextRect;      // Nút Next
extern SDL_Rect backRect;      // Nút Back
extern SDL_Rect closeRect;      // Nút Close

const float MIN_DISTANCE_TO_FLOWER = 200.0f;
const float WAVE_AMPLITUDE = 1.0f;
const float WAVE_FREQUENCY = 0.02f;
const float COLLECTING_TIME = 3000;


extern int plantedFlower;
extern int seeds;
extern int level;
extern int beeCount;
extern int lives;
extern int currentPage;

enum PlantStage { SEED, SPROUT, BUD, BLOOM, WILT };

struct Plant {
    SDL_Rect rect;
    PlantStage stage;
    Uint32 plantedTime;
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

extern SDL_Texture* dizzy1;
extern SDL_Texture* dizzy2;

extern SDL_Texture* gameOver;
void loadTextures(SDL_Renderer* renderer);

#endif // DEFINITION_H_INCLUDED
