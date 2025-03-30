#include <SDL.h>
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "include/definition.h"
#include "include/flowerGrowth.h"

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
            //float targetX = nearestFlower.x + (nearestFlower.w - bee.rect.w) / 2.0f;
            //float targetY = nearestFlower.y - bee.rect.h + 15.0f;

            float deltaX = nearestFlower.x - bee.rect.x;
            float deltaY = nearestFlower.y - bee.rect.y;

            float angle = atan2(deltaY, deltaX);

            if (minDistance > 10.0f) {
                float waveX = (minDistance > 50.0f) ? sin(currentTime * WAVE_FREQUENCY) * WAVE_AMPLITUDE : 0.0f;
                float waveY = (minDistance > 50.0f) ? cos(currentTime * WAVE_FREQUENCY) * WAVE_AMPLITUDE : 0.0f;
                bee.rect.x += cos(angle) * BEE_SPEED + waveX;
                bee.rect.y += sin(angle) * BEE_SPEED + waveY;
            }
            else {
                //bee.rect.x = targetX;
                //bee.rect.y = targetY;

                bee.velocityX = 0;
                bee.velocityY = 0;
            }

            if (targetFlower && targetFlower->stage == WILT) {
                if (bee.collectTime == 0)
                    bee.collectTime = currentTime;

                if (bee.collectTime != 0 && currentTime - bee.collectTime >= 3000) {

                    plants.erase( std::remove_if(plants.begin(), plants.end(),[&](const Plant& p) { return SDL_RectEquals(&p.rect, &nearestFlower); }),plants.end() );
                    bee.collectTime = 0;
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

        if (bee.rect.x < 100 ){
            bee.rect.x = 100;
            bee.velocityX *= -1;
        }
        if (bee.rect.x > 900 - bee.rect.w) {
            bee.rect.x = 900 - bee.rect.w;
            bee.velocityX *= -1;
        }
        if (bee.rect.y < 50) {
            bee.rect.y = 50;
            bee.velocityY *= -1;
        }
        if (bee.rect.y > 650 - bee.rect.h) {
            bee.rect.y = 650 - bee.rect.h;
            bee.velocityY *= -1;
        }

        bee.moveTime = currentTime;

    }

}


void addBees(int level) {
    int minBeeCount = 0;
    switch (level) {
        case 1: minBeeCount = 0; break;
        case 2: minBeeCount = 1; break;
        case 3: minBeeCount = 2; break;
        case 4: minBeeCount = 3; break;
    }

    if (bees.size() < minBeeCount) {
        Bee newBee;
        newBee.rect = {rand() % 800, rand() % 600, BEE_WIDTH, BEE_HEIGHT};
        newBee.moveTime = SDL_GetTicks();
        newBee.velocityX = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;
        newBee.velocityY = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;
        bees.push_back(newBee);
    }
}
