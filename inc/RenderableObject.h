#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "SDL2/SDL.h"

//FIXME: Members should be public only for subclasses

class RenderableObject{
public:
	RenderableObject(SDL_Texture*, SDL_Rect rect);
	RenderableObject(SDL_Texture*);
	~RenderableObject();
	SDL_Rect& getBounds();
	virtual SDL_Texture* getTexture();  //To override for animations
	SDL_Texture *texture;
	SDL_Rect bounds;
};

#endif