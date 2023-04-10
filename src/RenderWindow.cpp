#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <Entity.hpp>

#include "RenderWindow.hpp"
#define RAD(x) (x * M_PI / 180)
#define TEXTURE_SIZE_MOD 0.4
#define BG_FADE_SPEED 1000.0

/* Creates a window of p_w width and p_h height with p_title name, and a renderer linked to the window */
RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
    : window(NULL), renderer(NULL)
{
    bg_r = 235 + 20 * sin(SDL_GetTicks()           );
    bg_g = 235 + 20 * sin(SDL_GetTicks() +   M_PI/3);
    bg_b = 235 + 20 * sin(SDL_GetTicks() + 2*M_PI/3);
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL)
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
}

/* Load a texture from filePath and return it in SDL_Texture */
SDL_Texture *RenderWindow::loadTexture(const char *p_filePath)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);
    if (texture == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    return texture;
}

void RenderWindow::renderEntity(Entity entity)
{

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = entity.getTexW();
    src.h = entity.getTexH();

    SDL_Rect dst;
    dst.x = entity.getPosX();
    dst.y = entity.getPosY();
    dst.w = entity.getTexW() * TEXTURE_SIZE_MOD;
    dst.h = entity.getTexH() * TEXTURE_SIZE_MOD;

    const SDL_Point center = {
        dst.w / 2 + 50 * TEXTURE_SIZE_MOD,
        dst.h / 2};

    SDL_RenderCopyEx(
        renderer, entity.getTex(), &src, &dst,
        entity.getAngle(), &center, SDL_FLIP_NONE);
}

/* Render a SDL_Texture to current renderer. */
void RenderWindow::render(SDL_Texture *p_tex, int x, int y)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 32;
    src.h = 32;

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = 32;
    dst.h = 32;

    SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

/* Render all content to window */
void RenderWindow::display()
{
    bg_r = 235 + 20 * sin((double)SDL_GetTicks()/BG_FADE_SPEED           );
    bg_g = 235 + 20 * sin((double)SDL_GetTicks()/BG_FADE_SPEED +   M_PI/3);
    bg_b = 235 + 20 * sin((double)SDL_GetTicks()/BG_FADE_SPEED + 2*M_PI/3);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, bg_r, bg_g, bg_b, 200);
}

/* Destroy the window */
void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

/* Clear the renderer */
void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}
