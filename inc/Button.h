#ifndef BUTTON_H
#define BUTTON_H

#include "SDL2/SDL.h"
#include "ImageUtils.h"
#include "RenderableObject.h"

class Button : public RenderableObject{
public:
	Button(int width, int height, int posX, int posY, std::string message, TTF_Font *font, SDL_Texture *background, SDL_Renderer *renderer);
	virtual ~Button();

	void select();
	void unselect();
	bool getSelected();

	SDL_Texture *getText();
	SDL_Rect& getTextBounds();

	bool isMouseOver(int x, int y);
private:
	bool selected;
	SDL_Texture* text;
	SDL_Rect textBounds;
};

#endif