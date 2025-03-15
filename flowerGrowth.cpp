#include <SDL.h>

#include "definition.h"

void updateFlower() {
    currentTime = SDL_GetTicks();
    for (auto& plant : plants) {
        Uint32 elapsedTime = currentTime - plant.plantedTime;

        if( elapsedTime >= 6000 )
            plant.stage = FLOWER_STAGE;
        else if (elapsedTime >= 4000)
            plant.stage = BUD_STAGE;
        else if (elapsedTime >= 2000)
            plant.stage = SPROUT_STAGE;
        else
            plant.stage = SEED_STAGE;

    }
}
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
