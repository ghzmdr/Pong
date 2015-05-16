#include "../inc/RenderableObject.h"

RenderableObject::RenderableObject(SDL_Texture *tex):texture(nullptr){
	texture = tex;
	SDL_QueryTexture(texture, NULL, NULL, &bounds.w, &bounds.h);
}
RenderableObject::RenderableObject(SDL_Texture *tex, SDL_Rect rect):texture(nullptr), bounds(rect){
	texture = tex;
}

RenderableObject::~RenderableObject(){
	if(texture != nullptr){ SDL_DestroyTexture(texture); texture = nullptr;}
}
SDL_Rect& RenderableObject::getBounds(){
	return bounds;
}

SDL_Texture* RenderableObject::getTexture(){
	return texture;
}
