#include <SDL.h>
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <vector>


#include "definition.h"

void moveBee( vector<Bee>& bees, vector<Plant>& plants)
{
    Uint32 currentTime = SDL_GetTicks();
    for (auto& bee : bees) {

        SDL_Rect nearestFlower ;
        float minDistance = FLT_MAX;

        for(auto& flower : plants ){
            float distance = sqrt( (flower.rect.x - bee.rect.x) * (flower.rect.x - bee.rect.x) + (flower.rect.y - bee.rect.y) * (flower.rect.y - bee.rect.y) );
            if (distance < minDistance) {
                minDistance = distance;
                nearestFlower = flower.rect;
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
            if (minDistance < 10.0f) {
                if (bee.collectTime == 0)
                        bee.collectTime = currentTime;

                if (currentTime - bee.collectTime >= 4000) {
                    plants.erase(plants.begin(), plants.end());
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

void addBees(int score) {
    if ((score == 10 && bees.size() == 0) ||
        (score == 30 && bees.size() == 1) ||
        (score == 50 && bees.size() == 3) ||
        (score == 80 && bees.size() == 4)) {
        Bee newBee;
        newBee.rect = {rand() % 800, rand() % 600, 40, 40};
        newBee.moveTime = SDL_GetTicks();

        newBee.velocityX = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;
        newBee.velocityY = (rand() % (2 * BEE_SPEED)) - BEE_SPEED;

        bees.push_back(newBee);
    }
}
