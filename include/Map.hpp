#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Map
{
public:
	Map(int h, int w);
	void render(SDL_Renderer *renderer);
    void generateNew(int width_px, int height_px, int init_x, int init_y);
	void optimizeWalls(int width_px, int height_px, int init_x, int init_y);
	void clear();

private:
	int width, height;
    int walls[64][64];
	int wallsOpt[64][64][4];
};
