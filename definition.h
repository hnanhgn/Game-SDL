#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

#include <string>
#include <SDL.h>
#include <vector>

#include "textureManager.h"

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "Loobee";

const int CHARACTER_WIDTH = 150;
const int CHARACTER_HEIGHT = 130;
const int CHARACTER_SPEED = 10;

const int GRID_SIZE = 30;

const int BEE_WIDTH = 60;
const int BEE_HEIGHT = 60;
const int BEE_SPEED = 4;

extern SDL_Rect playerRect ;
extern SDL_Renderer* renderer;

extern SDL_Rect playButton;
extern SDL_Rect directionButton;

const float MIN_DISTANCE_TO_FLOWER = 200.0f;
const float WAVE_AMPLITUDE = 1.0f;            // Độ lớn dao động lượn sóng
const float WAVE_FREQUENCY = 0.02f;            // Tần số dao động
const float COLLECTING_TIME = 3000;


extern int score;

enum PlantStage { SEED_STAGE, BUD_STAGE, SPROUT_STAGE, FLOWER_STAGE };

struct Plant {
    SDL_Rect rect;       // Vị trí (và kích thước) của ô đất đã gieo hạt
    PlantStage stage;    // Giai đoạn hiện tại: seed, bud hay flower
    Uint32 plantedTime;  // Thời điểm gieo (hoặc cập nhật giai đoạn) (ms)
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

extern int lives;
const int HEART_WIDTH = 40;
const int HEART_HEIGHT = 40;
extern vector<SDL_Rect> hearts;

SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer);

extern SDL_Texture* background;
extern SDL_Texture* beforeGame;

extern SDL_Texture* character1;
extern SDL_Texture* character2;
extern SDL_Texture* character3;

extern SDL_Texture* seed;
extern SDL_Texture* sprout;
extern SDL_Texture* bud;
extern SDL_Texture* flower;

extern SDL_Texture* bee;

extern SDL_Texture* welcome;
extern SDL_Texture* playIcon;
extern SDL_Texture* directionIcon;

extern SDL_Texture* dizzy1;
extern SDL_Texture* dizzy2;

extern SDL_Texture* heart;
void loadTextures(SDL_Renderer* renderer);

#endif // DEFINITION_H_INCLUDED
