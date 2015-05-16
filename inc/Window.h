#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"
#include <string>
#include "debug.h"


#define STANDARD_WIDTH      640
#define STANDARD_HEIGHT     480

#define NONE                0

class Window
{
    public:
        Window(std::string title = "Window", int w = STANDARD_WIDTH, int h = STANDARD_HEIGHT, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED);
        ~Window();

        //Rendering
        void clean();
        void render(SDL_Texture* texture, SDL_Rect *clip = NULL, float angle = NONE, int xPivot = NONE, int yPivot = NONE, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void render(SDL_Texture* texture, SDL_Rect &dstRect, SDL_Rect *clip = NULL, float angle = NONE, int xPivot = NONE, int yPivot = NONE, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void setRenderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void present();

        SDL_Rect getBounds();
        SDL_Surface *getSurface();
        SDL_Renderer* getRenderer();

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Rect bounds;
};

#endif // WINDOW_H
