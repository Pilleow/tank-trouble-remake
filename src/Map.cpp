#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Map.hpp"

#define BG_FADE_SPEED 1000.0

using namespace std;

Map::Map(int h, int w) : height(0), width(0)
{
	height = h;
	width = w;
	
	// int i;
	// int **wl = new int *[height - 2];
	// for (i = 0; i < height - 2; ++i)
	// 	wl[i] = new int[width - 2];

	walls[height - 2][width - 2];

	// int ***wlOp = new int **[height - 2];
	// for (i = 0; i < height - 2; ++i)
	// 	*wlOp[i] = new int[width - 2];

	wallsOpt[height - 2][width - 2][4];
}

void Map::render(SDL_Renderer *renderer)
{
	int bg_r = 20 + 20 * sin((double)SDL_GetTicks() / BG_FADE_SPEED);
	int bg_g = 20 + 20 * sin((double)SDL_GetTicks() / BG_FADE_SPEED + M_PI / 3);
	int bg_b = 20 + 20 * sin((double)SDL_GetTicks() / BG_FADE_SPEED + 2 * M_PI / 3);
	SDL_SetRenderDrawColor(renderer, bg_r, bg_g, bg_b, 200);

	double x_delta, y_delta;
	int i, j, x_move, y_move;

	for (i = 0; i < height - 2; ++i)
	{
		for (j = 0; j < width - 2; ++j)
		{
			SDL_RenderDrawLine(
				renderer,
				wallsOpt[i][j][0], wallsOpt[i][j][1], 
				wallsOpt[i][j][2], wallsOpt[i][j][3]
			);
		}
	}
}

void Map::generateNew(int width_px, int height_px, int init_x, int init_y)
{
	Map::walls[height - 2][width - 2];
	int i, j, w, tries;

	for (i = 0; i < height - 2; ++i)
	{
		for (j = 0; j < width - 2; ++j)
		{
			tries = 100;
			while (tries > 0)
			{
				// generate wall at 1 of 4 directions
				// and ensure no walls are overlapping
				// 1 - up, 2 - right, 3 - down, 4 - left
				w = rand() % 4 + 1;
				if (w == 1 && i > 0 && walls[i - 1][j] != 3)
					break;
				if (w == 4 && j > 0 && walls[i][j - 1] != 2)
					break;
				if (w == 3 && i < height - 3 && walls[i + 1][j] != 1)
					break;
				if (w == 2 && j < width - 3 && walls[i][j + 1] != 4)
					break;
				tries--;
			}
			walls[i][j] = w;
		}
	}
	Map::optimizeWalls(width_px, height_px, init_x, init_y);
}

void Map::optimizeWalls(int width_px, int height_px, int init_x, int init_y)
{
	int i, j, x_delta, y_delta, x_move, y_move;
	x_delta = width_px / (width - 2);
	y_delta = height_px / (height - 2);
	wallsOpt[height - 2][width - 2][4];

	for (i = 0; i < height - 2; ++i)
	{
		for (j = 0; j < width - 2; ++j)
		{
			x_move = 0;
			y_move = 0;
			if (walls[i][j] == 1)
				y_move = -1;
			if (walls[i][j] == 2)
				x_move = 1;
			if (walls[i][j] == 3)
				y_move = 1;
			if (walls[i][j] == 4)
				x_move = -1;
			wallsOpt[i][j][0] = init_x + j * x_delta;
			wallsOpt[i][j][1] = init_y + i * y_delta;
			wallsOpt[i][j][2] = init_x + (j + x_move) * x_delta;
			wallsOpt[i][j][3] = init_y + (i + y_move) * y_delta;
		}
	}
}

void Map::clear()
{
}
