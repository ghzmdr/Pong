#ifndef BALL_H
#define BALL_H

#include "debug.h"
#include "SDL2/SDL.h"
#include "RenderableObject.h"

#define DIR_LEFT 	-1
#define DIR_RIGHT 	1
#define DIR_UP		-1
#define DIR_DOWN	1


class Ball : public RenderableObject{
public:
	Ball(SDL_Texture*, int x, int speedY, int speedX);
	virtual ~Ball();
	void changeXDirection(int dir);
	void changeXDirection();
	void changeYDirection(int dir);
	void move();
	void reset();
	void setSpeed(int speedX = NULL, int speedY = NULL); //If the value passed is NULL the speed won't be altered
private:
	int directionY;
	int directionX;
	int startPosition;
	int xSpeed;
	int ySpeed;
};


#endif