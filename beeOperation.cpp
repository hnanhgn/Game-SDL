#include <SDL.h>
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "definition.h"
#include "flowerGrowth.h"

void moveBee( vector<Bee>& bees, vector<Plant>& plants)
{
    Uint32 currentTime = SDL_GetTicks();
    for (auto& bee : bees) {

        SDL_Rect nearestFlower ;
        float minDistance = FLT_MAX;
        Plant* targetFlower = nullptr;

        for(auto& flower : plants ){
            float distance = sqrt( (flower.rect.x - bee.rect.x) * (flower.rect.x - bee.rect.x) + (flower.rect.y - bee.rect.y) * (flower.rect.y - bee.rect.y) );
            if (distance < minDistance) {
                minDistance = distance;
                nearestFlower = flower.rect;
                targetFlower = &flower;
            }

        }
        if (minDistance < MIN_DISTANCE_TO_FLOWER) {
            float deltaX = nearestFlower.x - bee.rect.x;
            float deltaY = nearestFlower.y - bee.rect.y;

            float angle = atan2(deltaY, deltaX);

            if (minDistance > 10.0f) {
                bee.rect.x += cos(angle) * BEE_SPEED + sin(currentTime * WAVE_FREQUENCY) * WAVE_AMPLITUDE;
                bee.rect.y += sin(angle) * BEE_SPEED + cos(currentTime * WAVE_FREQUENCY) * WAVE_AMPLITUDE;
            }
            else {
                bee.rect.x += cos(angle) * 0.5f;
                bee.rect.y += sin(angle) * 0.5f;
            }

            if (targetFlower && targetFlower->stage == WILT) { // Chỉ hút khi hoa ở trạng thái WILT
                if (bee.collectTime == 0)
                    bee.collectTime = currentTime; // Bắt đầu đếm thời gian hút mật

                if (bee.collectTime != 0 && currentTime - bee.collectTime >= 4000) {
                    // Xóa hoa khi đã hút mật đủ 4 giây
                    plants.erase( std::remove_if(plants.begin(), plants.end(),[&](const Plant& p) { return SDL_RectEquals(&p.rect, &nearestFlower); }),plants.end() );
                    bee.collectTime = 0; // Reset thời gian hút mật
                }
            }
        }

        else {
            if (rand() % 100 < 5) {
            bee.velocityX = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;
            bee.velocityY = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;
            }

            bee.rect.x += bee.velocityX;
            bee.rect.y += bee.velocityY;
        }

        if (bee.rect.x < 0){
            bee.rect.x = 0;
            bee.velocityX *= -1;
        }
        if (bee.rect.x > 800 - bee.rect.w) {
            bee.rect.x = 800 - bee.rect.w;
            bee.velocityX *= -1;
        }
        if (bee.rect.y < 0) {
            bee.rect.y = 0;
            bee.velocityY *= -1;
        }
        if (bee.rect.y > 600 - bee.rect.h) {
            bee.rect.y = 600 - bee.rect.h;
            bee.velocityY *= -1;
        }

        bee.moveTime = currentTime;

    }

}

void addBees(int level) {
    if ((level == 2 && bees.size() == 0) ||
        (level == 3 && bees.size() == 1) ||
        (level == 4 && bees.size() == 2) ||
        (level == 5 && bees.size() == 3)) {
        Bee newBee;
        newBee.rect = {rand() % 800, rand() % 600, BEE_WIDTH, BEE_HEIGHT};
        newBee.moveTime = SDL_GetTicks();

        newBee.velocityX = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;
        newBee.velocityY = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;

        bees.push_back(newBee);
    }
}
