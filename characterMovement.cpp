#include <SDL.h>
#include <vector>

#include "characterMovement.h"
#include "definition.h"
#include "textureManager.h"


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

    if (playerRect.x < 70)
        playerRect.x = 70;

    if (playerRect.x > 750)
        playerRect.x = 750;

    if (playerRect.y < 170)
        playerRect.y = 170;

    if (playerRect.y > 550)
        playerRect.y = 550;

}



void dropSeed(SDL_Rect& playerRect, int& seeds, int& plantedFlowers) {
    if (seeds >= 2) {

        Plant newPlant;
        newPlant.rect = {playerRect.x + 30, playerRect.y + 30, 20, 20};
        newPlant.stage = SEED;
        newPlant.plantedTime = SDL_GetTicks();
        plants.push_back(newPlant);

        seeds -= 2;
    }
}

void pickFlower(SDL_Rect& playerRect, int& seeds, int& plantedFlower) {
    for (auto it = plants.begin(); it != plants.end(); ++it) {
        if (it->stage == WILT) {
            SDL_Rect flowerRect = it->rect;
            flowerRect.w = 30;
            flowerRect.h = 30;
            flowerRect.x = it->rect.x - 10;
            flowerRect.y = it->rect.y - 10;

            if (SDL_HasIntersection(&playerRect, &flowerRect)) {
                plants.erase(it);
                plantedFlower += 1;
                seeds += 3;
                break;
            }
        }
    }
}

bool checkCollision (const SDL_Rect& a, const SDL_Rect& b) {
    return (a.x < b.x + b.w &&
            a.x + a.w > b.x &&
            a.y < b.y + b.h &&
            a.y + a.h > b.y);
}

bool checkContactWithBee (SDL_Rect& characterRect, vector<Bee>& bees) {
    for (auto& bee : bees) {
        if (checkCollision(characterRect, bee.rect)) {
            return true;
        }
    }
    return false;
}

void handleCollisionWithBee(int& lives, bool& inContactWithBee, Uint32& dizzyStartTime) {
    Uint32 currentTime = SDL_GetTicks();
    const Uint32 COOLDOWN_TIME = 1000;


    if (!inContactWithBee || (currentTime - dizzyStartTime >= COOLDOWN_TIME)) {
        lives--;
        inContactWithBee = true;
        dizzyStartTime = currentTime;
    }
}

