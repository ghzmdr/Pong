#include "../inc/Button.h"

Button::Button(int width, int height, int posX, int posY, std::string message, TTF_Font *font,  SDL_Texture *background, SDL_Renderer *renderer):RenderableObject(background), selected(false), text(nullptr){
	bounds.x = posX; bounds.y = posY;
	bounds.w = width; bounds.h = height;

	SDL_Color textColor = { .r = 255, .g = 255, .b = 255};
	text = text2Texture(renderer, font, message, textColor);
	SDL_QueryTexture(text, NULL, NULL, &textBounds.w, &textBounds.h);
	textBounds.x = posX + bounds.w/2 - textBounds.w/2; 
	textBounds.y = posY + textBounds.h/2;
}

Button::~Button(){
	SDL_DestroyTexture(text);
}

void Button::select(){
	selected = true;
}

void Button::unselect(){
	selected = false;
}

bool Button::getSelected(){
	return selected;
}

bool Button::isMouseOver(int x, int y){
	return x >= bounds.x && x <= bounds.x + bounds.w && y >= bounds.y && y <= bounds.y + bounds.h;
}

SDL_Texture* Button::getText(){
	if(selected) SDL_SetTextureColorMod(text, 100, 100, 100);
	else SDL_SetTextureColorMod(text, 30, 30, 30);
	return text;
}

SDL_Rect& Button::getTextBounds(){
	return textBounds;
}


