#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>

#include "definition.h"

using namespace std;

extern bool isSoundOn;

void start()
{
    score = 0;
    playerRect = {SCREEN_WIDTH / 2 - CHARACTER_WIDTH / 2, SCREEN_HEIGHT / 2 - CHARACTER_HEIGHT / 2, CHARACTER_WIDTH, CHARACTER_HEIGHT};
    plants.clear();
    bees.clear();

}

void handleButtonClick(int mouseX, int mouseY) {
    SDL_Point mousePoint = {mouseX, mouseY};

    if (SDL_PointInRect(&mousePoint, &playButton)) {
        start();

    }
    /*else if (SDL_PointInRect(&mousePoint, &directionButton)) {
        showDirections();
    }
    else if (SDL_PointInRect(&mousePoint, &soundButton)) {

        isSoundOn = !isSoundOn;

        if (isSoundOn)
            Mix_Resume(-1);

        else

            Mix_Pause(-1);

    }*/
}
