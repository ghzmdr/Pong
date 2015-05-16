#ifndef PADDLE_H
#define PADDLE_H

#include "debug.h"
#include "SDL2/SDL.h"
#include "RenderableObject.h"

#define PADDLE_SPEED  50

const int POSITION_LEFT = 1, POSITION_RIGHT = -1;

class Paddle : public RenderableObject{
public:
	Paddle(SDL_Texture *tex, int w, int h, int position);
	virtual ~Paddle();
	void moveUp();
	void moveDown();
	void flick();
	int getScore();
	void addScore();
	void follow(int y, int difference, int speed);
	void reset();
	virtual SDL_Texture* getTexture();
private:
	int startY;
	int score;
	int flickCount;
};


#endif