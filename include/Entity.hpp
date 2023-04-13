#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
public:
	Entity(int p_x, int p_y, SDL_Texture* p_tex, int rotation);
    SDL_Texture *getTex();
    int getPosX();
    int getPosY();
    int getTexW();
    int getTexH();
    int getAngle();
    void handleKeyDown(SDL_Keycode key);
    void handleKeyUp(SDL_Keycode key);
    void updateDeltas();
	void updatePos();

private:
    bool k_up = false, k_down = false; 
    bool k_left = false, k_right = false;
    double velocityDelta;
	double angle, angleDelta;
	double speed, rotSpeed;
	double x, y, vel;
	int tex_w, tex_h;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
