#include "CApp.h"
#include <iostream>
CApp::CApp()
{
    //ctor
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GetDisplayBounds(0,&screen);

    window = SDL_CreateWindow("The Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          screen.w,screen.h,
                           SDL_WINDOW_BORDERLESS);

    Main_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    SDL_SetRenderDrawColor(Main_Renderer,255,255,255,255);
    SDL_RenderClear(Main_Renderer);

    useOrbitTrap = false;

    long double tempX = -0.743643887037151;//-0.743643887037151;
    long double tempY = 0.131825904205330;//0.131825904205330;
    angle = 0;
    running = true;
//    std::cout << "Enter the value of the X-coordinate please:";
    //std::cin >> tempX;
//    std::cout << "Enter the value of the Y-coordinate please:";
    //std::cin >> tempY;
    std::complex<long double> offset(tempX,tempY);

    long double p = 50;

    long double resolution = 0.01;//1/(pow(10,resolution));
    long double width = 2;//M0.000000000051299;
    long double height = (double)screen.h / screen.w * width;
    std::unique_ptr<Mandelbrot> temp(new Mandelbrot(width, height, resolution,p,Main_Renderer,offset));
    brot = std::move(temp);
    if(useOrbitTrap)
        Tex = brot->OrbitTrap(Main_Renderer);
    else
        Tex = brot->DrawTexture(Main_Renderer);

    SDL_RenderCopy(Main_Renderer, Tex, NULL, NULL);
    SDL_RenderPresent(Main_Renderer);

    SDL_SetRenderDrawColor(Main_Renderer,255,255,255,0);
}

CApp::~CApp()
{
    //dtor
    SDL_DestroyRenderer(Main_Renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(Tex);
}

void CApp::OnDefault(){
        while(running){
            HandleInput();
            HandleRendering();
        }
}
