#include <SDL.h>

#include "definition.h"

void updateFlowerGrowth(std::vector<Plant>& plants) {
    Uint32 currentTime = SDL_GetTicks();
    for (auto &plant : plants) {
        Uint32 elapsed = currentTime - plant.plantedTime;
        if (elapsed < 3000)         // 0-5 giây
            plant.stage = SEED;
        else if (elapsed < 6000)   // 5-10 giây
            plant.stage = SPROUT;
        else if (elapsed < 9000)   // 10-15 giây
            plant.stage = BUD;
        else if (elapsed < 12000)   // 15-20 giây
            plant.stage = BLOOM;
        else                        // ≥20 giây
            plant.stage = WILT;
    }
}
