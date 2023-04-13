#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderWindow
{
public:
	RenderWindow(const char *p_title, int p_w, int p_h);
	SDL_Texture *loadTexture(const char *p_filePath);
	SDL_Renderer *getRenderer();
	void render(SDL_Texture *p_tex, int x, int y);
	void renderEntity(Entity entity);
	void display();
	void cleanUp();
	void clear();

private:
	int bg_r, bg_g, bg_b;
	SDL_Window *window;
	SDL_Renderer *renderer;
};
