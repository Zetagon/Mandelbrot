#ifndef CAPP_H
#define CAPP_H
#include <SDL.h>
#include "Mandelbrot.h"
#include <memory>
class CApp
{
    public:
        CApp();
        virtual ~CApp();
        void OnDefault();
        void HandleInput();
        void HandleRendering();
    protected:
    private:
        SDL_Renderer* Main_Renderer;
        SDL_Window* window;
        SDL_Rect screen;
        SDL_Texture* Tex;
        std::unique_ptr<Mandelbrot> brot;
        bool useOrbitTrap;
        int angle;
        bool running;
};

#endif // CAPP_H
