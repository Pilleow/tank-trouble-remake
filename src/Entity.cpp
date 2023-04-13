#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Entity.hpp"

#define RAD(x) (x * M_PI/180)

using namespace std;

Entity::Entity(int p_x, int p_y, SDL_Texture* p_tex, int rotation)
{
    SDL_QueryTexture(p_tex, NULL, NULL, &tex_w, &tex_h);
    angle = rotation;
    angleDelta = 0;
    velocityDelta = 0.07;
    tex = p_tex;
    x = p_x;
    y = p_y;
	speed = 3;
    rotSpeed = 2;
    vel = 0;
}

int Entity::getAngle() {
    return angle;
}
int Entity::getTexW() {
    return tex_w;
}
int Entity::getTexH() {
    return tex_h;
}
int Entity::getPosX() {
    return x;
}
int Entity::getPosY() {
    return y;
}
SDL_Texture *Entity::getTex() {
    return tex;
}

void Entity::updateDeltas() {
    
    /* movement deltas ------------------------------------------- */
    if (k_left && angleDelta > -1) angleDelta -= velocityDelta;
    else if ( !k_left && angleDelta < 0 ) angleDelta += velocityDelta;
    
    if (k_right && angleDelta < 1) angleDelta += velocityDelta;
    else if ( !k_right && angleDelta > 0 ) angleDelta -= velocityDelta;

    if (k_up && vel > -1) vel -= velocityDelta;
    else if ( !k_up && vel < 0 ) vel += velocityDelta;

    if (k_down && vel < 1) vel += velocityDelta;
    else if ( !k_down && vel > 0 ) vel -= velocityDelta;

    // eliminate rounding error :skull_emoji:
    vel = round(vel * 100) / 100;
    angleDelta = round(angleDelta * 100) / 100;
}

void Entity::handleKeyDown(SDL_Keycode key) {
    switch (key) {
        case SDLK_LEFT:
            k_left = true;
            break;
        case SDLK_RIGHT:
            k_right = true;
            break;
        case SDLK_UP:
            k_up = true;
            break;
        case SDLK_DOWN:
            k_down = true;
            break;
    }
}

void Entity::handleKeyUp(SDL_Keycode key) {
    switch(key){
        case SDLK_LEFT:
            k_left = false;
            break;
        case SDLK_RIGHT:
            k_right = false;
            break;
        case SDLK_UP:
            k_up = false;
            break;
        case SDLK_DOWN:
            k_down = false;
            break;
    }
}

void Entity::updatePos() {
    angle += angleDelta * rotSpeed;
    x += vel * speed * cos(RAD(angle));
    y += vel * speed * sin(RAD(angle));
}
