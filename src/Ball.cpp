#include "../inc/Ball.h"

Ball::Ball(SDL_Texture *tex, int w, int speedX, int speedY):RenderableObject(tex),  directionY(DIR_DOWN), directionX(DIR_RIGHT), xSpeed(speedX), ySpeed(speedY){
	bounds.y = 70;
	bounds.x = w/2 + bounds.w/2;
	startPosition = bounds.x;
}

Ball::~Ball(){
}

void Ball::move(){
	bounds.x += xSpeed*directionX;
	bounds.y += ySpeed*directionY;
}

void Ball::changeYDirection(int dir){
	directionY = dir;
}

void Ball::changeXDirection(int dir){
	directionX = dir; 
}

void Ball::changeXDirection(){
	directionX *= -1;
}

void Ball::setSpeed(int speedX, int speedY){
	if(speedX != NULL) xSpeed = speedX;
	if(speedY != NULL) ySpeed = speedY;
}

void Ball::reset(){
	changeYDirection(DIR_DOWN);
	bounds.x = startPosition;
	bounds.y = 70;
}