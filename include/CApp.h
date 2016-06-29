#ifndef CAPP_H
#define CAPP_H
#include <SDL2/SDL.h>
#include "Mandelbrot.h"

class CApp
{
    public:
        CApp();
        virtual ~CApp();
        void OnDefault();
    protected:
    private:
        SDL_Renderer* Main_Renderer;
        SDL_Window* window;
        SDL_Rect screen;
};

#endif // CAPP_H
