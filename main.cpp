#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string.h>
#include <vector>

#include "definition.h"
#include "textureManager.h"
#include "characterMovement.h"
#include "flowerGrowth.h"
#include "updateScore.h"
#include "beeOperation.h"

using namespace std;

void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(cout, "SDL_Init", true);
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    // SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(cout, "CreateWindow", true);
    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if ( SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    TTF_Init();
    TTF_Font* font = TTF_OpenFont("LoveDays-2v7Oe.ttf", 24);

    SDL_Texture* background = loadTexture("background.png", renderer);

    SDL_Texture* character1 = loadTexture("flyStep1.png", renderer);
    SDL_Texture* character2 = loadTexture("flyStep2.png", renderer);
    SDL_Texture* character3 = loadTexture("flyStep3.png", renderer);

    SDL_Texture* seed = loadTexture("seed.png", renderer);
    SDL_Texture* sprout = loadTexture("sprout.png", renderer);
    SDL_Texture* bud = loadTexture("bud.png", renderer);
    SDL_Texture* flower = loadTexture("flower.png", renderer);

    SDL_Texture* bee = loadTexture("bee.png", renderer);

    SDL_Texture* welcome = loadTexture("welcomeBg.png", renderer);
    SDL_Texture* playIcon = loadTexture("playButton.png", renderer);
    SDL_Texture* directionIcon = loadTexture("directionButton.png", renderer);

    bool running = true;
    bool facingLeft = false;
    bool showWelcomeScreen = true;
    SDL_Event event;

    while (running)
{
    currentTime = SDL_GetTicks();

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            running = false;

        if (!showWelcomeScreen)
        {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
                dropSeed(playerRect);
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
                pickFlower(playerRect);
            if (event.key.keysym.sym == SDLK_LEFT)
                facingLeft = true;
            if (event.key.keysym.sym == SDLK_RIGHT)
                facingLeft = false;
        }

        if (showWelcomeScreen)
        {
            drawWelcomeScreen(renderer, welcome, playIcon, directionIcon);

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                SDL_Point mousePoint = {mouseX, mouseY};

                if (SDL_PointInRect(&mousePoint, &playButton))
                    showWelcomeScreen = false;
            }

            SDL_RenderPresent(renderer);

        }
    }

    if (!showWelcomeScreen)
    {
        updateMovement(playerRect);
        updateFlower();
        moveBee(bees, plants);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, nullptr, nullptr);

        addBees(score);
        drawBees(renderer, bee);

        drawPlants(renderer, seed, sprout, bud, flower);
        drawCharacter(renderer, character1, character2, character3, facingLeft);

        updateScore(renderer, font);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }
}


    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyTexture(background);
    quitSDL(window, renderer);
    return 0;
}
