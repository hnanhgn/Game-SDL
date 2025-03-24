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
    newPlant.rect.x = playerRect.x + (CHARACTER_WIDTH / 2) - (GRID_SIZE / 2);
    newPlant.rect.y = playerRect.y + CHARACTER_HEIGHT - (GRID_SIZE / 2);
    newPlant.rect.w = GRID_SIZE;
    newPlant.rect.h = GRID_SIZE;
    newPlant.stage = SEED_STAGE;
    newPlant.plantedTime = SDL_GetTicks();

    plants.push_back(newPlant);
}

void pickFlower(SDL_Rect& playerRect) {
    for (auto it = plants.begin(); it != plants.end(); ++it) {
        if (it->stage == FLOWER_STAGE) {
            SDL_Rect flowerRect = it->rect;
            flowerRect.w = 40;
            flowerRect.h = 40;
            flowerRect.x = it->rect.x - 10;
            flowerRect.y = it->rect.y - 10;


            if (SDL_HasIntersection(&playerRect, &flowerRect)) {
                plants.erase(it);
                score += 1;
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

void handleCollisionWithBee(SDL_Renderer* renderer, SDL_Texture* dizzy1, SDL_Texture* dizzy2,
                              SDL_Rect& playerRect, int& lives, Uint32& dizzyStartTime)
{
    // Kiểm tra va chạm giữa nhân vật và các ong
    bool contactNow = checkContactWithBee(playerRect, bees);

    // Sử dụng static để đảm bảo mỗi lần va chạm mới chỉ trừ 1 mạng
    static bool collisionHandled = false;

    if (contactNow) {
        if (!collisionHandled) {
            // Lần va chạm đầu tiên của sự kiện hiện tại: trừ 1 mạng và ghi lại thời gian bắt đầu hiệu ứng
            lives--;
            collisionHandled = true;
            dizzyStartTime = SDL_GetTicks();
        }

        // Hiển thị hiệu ứng dizzy trong 2 giây kể từ khi va chạm bắt đầu
        Uint32 elapsed = SDL_GetTicks() - dizzyStartTime;

            // Thay đổi frame mỗi 300ms để tạo hiệu ứng nhấp nháy
            SDL_Texture* dizzyTexture = (elapsed / 300) % 2 == 0 ? dizzy1 : dizzy2;
            SDL_RenderCopy(renderer, dizzyTexture, nullptr, &playerRect);

    }
    else {
        // Khi không còn va chạm, reset trạng thái để sẵn sàng cho lần va chạm mới
        collisionHandled = false;
    }
}
