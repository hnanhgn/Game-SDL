#include <SDL.h>
#include <vector>

#include "definition.h"

void updateMovement (SDL_Rect& playerRect)
{

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_UP])
        playerRect.y -= CHARACTER_SPEED;

    if (keystates[SDL_SCANCODE_DOWN])
        playerRect.y += CHARACTER_SPEED;

    if (keystates[SDL_SCANCODE_LEFT])
        playerRect.x -= CHARACTER_SPEED;

    if (keystates[SDL_SCANCODE_RIGHT])
        playerRect.x += CHARACTER_SPEED;

    if (playerRect.x < 80)
        playerRect.x = 80;

    if (playerRect.x > 800)
        playerRect.x = 800;

    if (playerRect.y < 150)
        playerRect.y = 150;

    if (playerRect.y > 550)
        playerRect.y = 550;

}

void dropSeed( SDL_Rect& playerRect)
{

    int row = playerRect.y / (GRID_SIZE * 2);
    int col = playerRect.x / (GRID_SIZE * 2);

    SDL_Rect cellRect = { col * GRID_SIZE * 2, row * GRID_SIZE * 2, 20, 20 };

    for (const auto& plant : plants) {
        if (plant.rect.x == cellRect.x && plant.rect.y == cellRect.y) {

            return;
        }
    }

    Plant newPlant;
    newPlant.rect = cellRect;
    newPlant.stage = SEED_STAGE;
    newPlant.plantedTime = SDL_GetTicks();

    plants.push_back(newPlant);
}

void pickFlower(SDL_Rect& playerRect) {
    for (auto it = plants.begin(); it != plants.end(); ++it) {
        if (it->stage == FLOWER_STAGE) {
            SDL_Rect flowerRect = it->rect;
            flowerRect.w = 40; // Kích thước lớn nhất của hoa
            flowerRect.h = 40;
            flowerRect.x = it->rect.x - 10;
            flowerRect.y = it->rect.y - 10;

            // Kiểm tra va chạm với nhân vật (gần hoa)
            if (SDL_HasIntersection(&playerRect, &flowerRect)) {
                plants.erase(it);
                score += 1;
                break;
            }
        }
    }
}
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
