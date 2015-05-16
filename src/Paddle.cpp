#include "../inc/Paddle.h"

/*PLEASE NOTE:
*	The flickering of the paddle is done by altering the alpha of it's texture
*	In order to get an acceptable animation it is capped to run only once every two frames
*	To achieve this flickCount is made == 30 and the alpha altering is done only if flickCount%6 is == to 0, 2, 4.
*	So if flickCount starts higher it lasts more, if you want to change the delay between alpha changing you'll need
*	to alter the values of the modules in order to manatain a proper ratio. 
*/

Paddle::Paddle(SDL_Texture *tex, int w, int h, int position):RenderableObject(tex), score(0), flickCount(0){
	startY = bounds.y = h/2 - bounds.h/2;
	if(position == POSITION_LEFT)	bounds.x = 10;
	if(position == POSITION_RIGHT)	bounds.x = w-(bounds.w+10);
}

Paddle::~Paddle(){
	
}

void Paddle::moveUp(){
	bounds.y -= PADDLE_SPEED;
}

void Paddle::moveDown(){
	bounds.y += PADDLE_SPEED;
}

void Paddle::flick(){
	flickCount = 30;
}

void Paddle::addScore(){
	score++;
}

int Paddle::getScore(){
	return score;
}

void Paddle::follow(int y, int difference, int speed){
	if(bounds.y < y -difference) bounds.y += speed;
	else if(bounds.y > y +difference) bounds.y -= speed;
}

void Paddle::reset(){
	score = 0;
	bounds.y = startY;
}


SDL_Texture *Paddle::getTexture(){

	//Managing the flicking of the paddle from here!
	if(flickCount){
		if (flickCount%6 == 0)	SDL_SetTextureAlphaMod(texture, 130);
		if (flickCount%6 == 2) 	SDL_SetTextureAlphaMod(texture, 0);
		if (flickCount%6 == 4)	SDL_SetTextureAlphaMod(texture, 200);
		if (flickCount == 30)	SDL_SetTextureAlphaMod(texture, 255);	//This is done in order to present the full-alpha frame after a score
		flickCount--;
	} else SDL_SetTextureAlphaMod(texture, 255);

	return texture;
}
