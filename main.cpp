#include "inc/debug.h"
#include "inc/MainMenu.h"
#include "SDL2/SDL_mixer.h"

#define SCR_W 800
#define SCR_H 600


int main(int argc, char const *argv[])
{
	SDL_Init(SDL_INIT_EVENTS|SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	Window *window = new Window("Pong", SCR_W, SCR_H);
	MainMenu *menu = new MainMenu(window);
	checkMem(window);
	checkMem(menu);
error:
	delete window;
	delete menu;

	Mix_CloseAudio();
	Mix_Quit();
	SDL_VideoQuit();
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	
	return 0;
}