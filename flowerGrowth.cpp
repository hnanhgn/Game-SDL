#include <SDL.h>

#include "definition.h"

void updateFlowerGrowth(std::vector<Plant>& plants) {
    Uint32 currentTime = SDL_GetTicks();
    for (auto &plant : plants) {
        Uint32 elapsed = currentTime - plant.plantedTime;
        if (elapsed < 3000)
            plant.stage = SEED;
        else if (elapsed < 6000)
            plant.stage = SPROUT;
        else if (elapsed < 9000)
            plant.stage = BUD;
        else if (elapsed < 12000)
            plant.stage = BLOOM;
        else
            plant.stage = WILT;
    }
}
