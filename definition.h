#ifndef DEFINITION_H_INCLUDED
#define DEFINITION_H_INCLUDED

#include <string>
#include <SDL.h>
#include <vector>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "Loobee";
const int CHARACTER_WIDTH = 70;
const int CHARACTER_HEIGHT = 70;
const int CHARACTER_SPEED = 10;
const int GRID_SIZE = 30;


extern SDL_Rect playerRect ;
extern SDL_Renderer* renderer;
extern SDL_Texture* character ;
extern SDL_Texture* background ;

extern int score;

//extern vector<vector<bool>> seedGrid;
enum PlantStage { SEED_STAGE, BUD_STAGE, SPROUT_STAGE, FLOWER_STAGE };

struct Plant {
    SDL_Rect rect;       // Vị trí (và kích thước) của ô đất đã gieo hạt
    PlantStage stage;    // Giai đoạn hiện tại: seed, bud hay flower
    Uint32 plantedTime;  // Thời điểm gieo (hoặc cập nhật giai đoạn) (ms)
};

extern Uint32 currentTime ;
extern vector<Plant> plants;

#endif // DEFINITION_H_INCLUDED
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
