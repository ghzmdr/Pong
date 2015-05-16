#include "../inc/ImageUtils.h"

SDL_Texture* image2Texture(SDL_Renderer* renderer, std::string path){
    SDL_Texture *image = nullptr;
    image = IMG_LoadTexture(renderer, path.c_str());
    if (image == nullptr) logErr("Cannot load Texure from file");
    return image;
}

SDL_Surface* image2Surface(std::string path){
    SDL_Surface *image = nullptr;
    image = IMG_Load(path.c_str());
    if (image == nullptr) logErr("Cannot load Surface from file");
    return image;
}

SDL_Texture* surface2Texture(SDL_Renderer* renderer, SDL_Surface* surface){
    SDL_Texture *texture = nullptr;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) logErr("Cannot load Surface from Texture")
    return texture;
}

void extractClipRect(int framesNum, SDL_Texture* image, SDL_Rect destination[]){
    int FRAME_W, FRAME_H;
    SDL_QueryTexture(image, NULL, NULL, &FRAME_W, &FRAME_H);
    FRAME_W /= framesNum;

    for (int iter = 0; iter < framesNum; iter++){
        destination[iter].w= FRAME_W;
        destination[iter].h= FRAME_H;
        destination[iter].x= FRAME_W * iter;
        destination[iter].y= 0;
    }
}

SDL_Texture* text2Texture(SDL_Renderer *renderer,TTF_Font *font, std::string message, SDL_Color &textColor){
    SDL_Surface *tmp = nullptr;
    tmp = TTF_RenderText_Solid(font, message.c_str(), textColor);
    if(tmp == nullptr) logErr("Cannot render text");
    SDL_Texture *ret = surface2Texture(renderer, tmp);
    SDL_FreeSurface(tmp);
    return ret;
}
