#ifndef GAME_H
#define GAME_H

#include <string>
#include <sstream>
#include "debug.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include "Window.h"
#include "ImageUtils.h"

#include "Button.h"

#include "Paddle.h"
#include "Ball.h"

enum class Mode{ SINGLEPLAYER, MULTIPLAYER };
enum class Difficulty{ NO, EASY, NORMAL, HARD, UNBEATABLE };

class Game{
public:
	Game(Window *win, Mode mod, Difficulty diff);
	~Game();
private:	
	void init();
	void waitForPlayers();
	void displayInstructions();
	void handleInput();
	void updateLogic();
	void drawGame();
	void reset();

	void displayGameOver();
	void elaborateScore();
	int  ballIsOut();
	int  calcBallAngle(Paddle *pad);
	bool ballCollidesLeft();
	bool ballCollidesRight();

	bool done;
	Window *window;
	TTF_Font *font;
	SDL_Texture *scoreTexture;
	SDL_Texture *background;
	SDL_Rect scorePosition;

	Paddle *lPad;
	Paddle *rPad;
	Ball *ball;
	Mix_Chunk *hitEffect;
	Mix_Chunk *bounceEffect;
	Mix_Chunk *pointEffect;
	RenderableObject *field;
	bool scored;
	Mode mode;
	Difficulty difficulty;
};

#endif