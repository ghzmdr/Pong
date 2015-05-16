#ifndef MAINMENU_H
#define MAINMENU_H

#include "SDL2/SDL_mixer.h"
#include "Window.h"
#include "ImageUtils.h"
#include "Button.h"
#include "Game.h"

class MainMenu {

public:
	MainMenu(Window *win);
	~MainMenu();
private:
	void initResources();
	void handleInput();
	void draw();

	Difficulty chooseDifficulty();

	void handleClick(SDL_MouseButtonEvent event);
	void handleMouse();

	Window *window;
	TTF_Font *font;
	Mix_Chunk *buttonPress;
	SDL_Texture *background;
	SDL_Texture *title;
	SDL_Rect titleBounds;
	Button *buttons[3];
	bool done;
};



#endif