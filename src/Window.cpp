#include "../inc/Window.h"

Window::Window(std::string title, int w, int h, int x, int y):window(nullptr), renderer(nullptr){
    bounds.x = 0;
    bounds.y = 0;
    bounds.w = w;
    bounds.h = h;

    window = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_SHOWN);
    if (window == nullptr) logErr("Cannot create Window");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logErr("Cannot create Window");

    setRenderColor(0, 0, 0, 255);
    clean();
}

Window::~Window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Window::render(SDL_Texture* texture, SDL_Rect &dstRect, SDL_Rect *clip, float angle, int xPivot, int yPivot, SDL_RendererFlip flip){
    xPivot+=dstRect.w/2;
    yPivot+=dstRect.h/2;

    SDL_Point pivot = { xPivot, yPivot};
    SDL_RenderCopyEx(renderer, texture, clip, &dstRect, angle, &pivot, flip);
}

void Window::render(SDL_Texture* texture, SDL_Rect *clip, float angle, int xPivot, int yPivot, SDL_RendererFlip flip){
    render(texture, bounds, clip, angle, xPivot, yPivot, flip);
}

SDL_Surface* Window::getSurface(){
    return SDL_GetWindowSurface(window);
}

SDL_Renderer* Window::getRenderer(){
    return renderer;
}

void Window::present(){
    SDL_RenderPresent(renderer);
}

SDL_Rect Window::getBounds(){
    return bounds;
}

void Window::clean(){
    SDL_RenderClear(renderer);
}


void Window::setRenderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
