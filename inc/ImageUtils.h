#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <string>
#include "debug.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"


SDL_Texture* image2Texture(SDL_Renderer* renderer, std::string path);											//File to texture
SDL_Surface* image2Surface(std::string path);																	//File to surface
SDL_Texture* surface2Texture(SDL_Renderer* renderer, SDL_Surface* surface);										//Surface to Texture
SDL_Texture* text2Texture(SDL_Renderer *renderer, TTF_Font *font, std::string message, SDL_Color &textColor);	//String to Texture
void extractClipRect(int framesNum, SDL_Texture* image, SDL_Rect destination[]);								//Extracts a clip from a sprite

#endif