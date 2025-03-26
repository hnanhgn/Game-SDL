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

    if (playerRect.x < 80)
        playerRect.x = 80;

    if (playerRect.x > 800)
        playerRect.x = 800;

    if (playerRect.y < 150)
        playerRect.y = 150;

    if (playerRect.y > 550)
        playerRect.y = 550;

}



void dropSeed(SDL_Rect& playerRect, int& seeds, int& plantedFlowers) {
    if (seeds >= 2) {

        Plant newPlant;
        newPlant.rect = {playerRect.x, playerRect.y, 20, 20};
        newPlant.stage = SEED;
        newPlant.plantedTime = SDL_GetTicks();
        plants.push_back(newPlant);

        seeds -= 2;          // Trừ 2 hạt giống
        //plantedFlowers += 1; // Tăng số hoa đã gieo
    }
}

void pickFlower(SDL_Rect& playerRect, int& seeds, int& plantedFlower) {
    for (auto it = plants.begin(); it != plants.end(); ++it) {
        if (it->stage == WILT) {
            SDL_Rect flowerRect = it->rect;
            flowerRect.w = 40;
            flowerRect.h = 40;
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

void handleCollisionWithBee(int& lives, bool& inContactWithBee, Uint32& dizzyStartTime)
{
    bool contactNow = checkContactWithBee(playerRect, bees); // Kiểm tra va chạm

    if (contactNow && !inContactWithBee) { // Chỉ trừ mạng khi vừa mới chạm ong
        lives--; // Giảm mạng
        inContactWithBee = true; // Đánh dấu đang chạm ong
        dizzyStartTime = SDL_GetTicks(); // Bắt đầu thời gian "choáng"
    }
    else if (!contactNow && inContactWithBee) { // Khi không còn chạm ong nữa
        inContactWithBee = false; // Đặt lại trạng thái
    }
}
