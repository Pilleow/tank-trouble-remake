#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <thread>

#include "Map.hpp"
#include "Entity.hpp"
#include "RenderWindow.hpp"

/* DEFINING RESOLUTION (PREPROCESSOR) */

#define RES_X 1280
#define RES_Y (RES_X * 9 / 16)

int main(int argc, char *args[])
{
    /* LOADING SDL2 */

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL_Init has failed. Error: " << SDL_GetError() << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
    SDL_Event event;

    /* CREATING WINDOW */

    RenderWindow window("Tank Trouble", RES_X, RES_Y);

    /* LOADING TEXTURES */

    SDL_Texture *tank1 = window.loadTexture("res/gfx/player1.png");
    SDL_Texture *tank2 = window.loadTexture("res/gfx/player2.png");
    SDL_Texture *tank3 = window.loadTexture("res/gfx/player3.png");
    SDL_Texture *tank4 = window.loadTexture("res/gfx/player4.png");

    /* LOADING ENTITIES */

    Entity player1((int)(RES_X/3), (int)(RES_Y/3), tank1, 0);
    Entity player2((int)(RES_X*2/3), (int)(RES_Y/3), tank2, 0);
    Entity player3((int)(RES_X*2/3), (int)(RES_Y*2/3), tank3, 0);
    Entity player4((int)(RES_X/3), (int)(RES_Y*2/3), tank4, 0);
    
    Map map(8, 12);
    map.generateNew(0.9 * RES_X, 0.9 * RES_Y, 0.1 * RES_X, 0.1 * RES_Y);

    /* FPS CAP SETUP */

    unsigned int fps = 60;
    unsigned int a, b = SDL_GetTicks();
    double delta;

    /* MAIN GAME LOOP -------------------------------------------- */

    bool gameRunning = true;
    while (gameRunning)
    {
        /* FPS CAP */

        a = SDL_GetTicks();
        delta = a - b;
        if (delta < 1000/fps) std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000.0/fps - delta)));
        b = a;

        /* EVENT HANDLING */

        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_QUIT:
                    gameRunning = false;
                    break;
                case SDL_KEYDOWN:
                    player1.handleKeyDown(event.key.keysym.sym);
                    if (event.key.keysym.sym == SDLK_F1)
                        map.generateNew(0.9 * RES_X, 0.9 * RES_Y, 0.1 * RES_X, 0.1 * RES_Y);
                    break;
                case SDL_KEYUP:
                    player1.handleKeyUp(event.key.keysym.sym);
                    break;
            }
        }

        /* MOVE PLAYERS */

        player1.updatePos();
        player1.updateDeltas();

        /* RENDERING ELEMENTS TO WINDOW */

        window.clear();

        map.render(window.getRenderer());

        window.renderEntity(player1);
        window.renderEntity(player2);
        window.renderEntity(player3);
        window.renderEntity(player4);

        window.display();
    }

    /* ON QUIT */

    window.cleanUp();
    SDL_Quit();
    return 0;
}