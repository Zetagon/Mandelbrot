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
}

CApp::~CApp()
{
    //dtor
    SDL_DestroyRenderer(Main_Renderer);
    SDL_DestroyWindow(window);
}

void CApp::OnDefault(){
    bool useOrbitTrap = false;

    std::complex<long double> Z(0.0,0.0);
    long double tempX = -0.743643887037151;//-0.743643887037151;
    long double tempY = 0.131825904205330;//0.131825904205330;
//    std::cout << "Enter the value of the X-coordinate please:";
    //std::cin >> tempX;
//    std::cout << "Enter the value of the Y-coordinate please:";
    //std::cin >> tempY;
    std::complex<long double> offset(tempX,tempY);

    long double p = 2;

    long double resolution = 0.01;//1/(pow(10,resolution));
    long double width = 2;//M0.000000000051299;
    long double height = (double)screen.h / screen.w * width;
        Mandelbrot brot(width, height, resolution,p,Main_Renderer,Z,offset);
        SDL_Texture* Tex;
        if(useOrbitTrap)
            Tex = brot.OrbitTrap(Main_Renderer);
        else
            Tex = brot.DrawTexture(Main_Renderer);

        SDL_RenderCopy(Main_Renderer, Tex, NULL, NULL);
        SDL_RenderPresent(Main_Renderer);

        SDL_SetRenderDrawColor(Main_Renderer,255,255,255,0);
        bool running = true;
        int scrollModifierX = 0;//screen.w * MAX_SIZE/2 ;
        int scrollModifierY = 0;//screen.h * MAX_SIZE/2;
        int angle = 0;
        long double zoomModifier = 0;
        while(running){
        const Uint8 *keystates = SDL_GetKeyboardState(NULL);
        SDL_Rect screen;
        if(SDL_GetDisplayBounds(0,&screen) != 0);



            if(keystates[SDL_SCANCODE_W]){
                Tex = brot.moveOffset(Main_Renderer,0,1);
            }
            if(keystates[SDL_SCANCODE_S]){
                Tex = brot.moveOffset(Main_Renderer,0,-1);
            }
            if(keystates[SDL_SCANCODE_A]){
                Tex = brot.moveOffset(Main_Renderer,-1 ,0);
            }
            if(keystates[SDL_SCANCODE_D]){
                Tex = brot.moveOffset(Main_Renderer,1 ,0);
            }
            if(keystates[SDL_SCANCODE_O]){
                if(useOrbitTrap)
                    useOrbitTrap = false;
                else
                    useOrbitTrap = true;
                SDL_Delay(200);
            }
            if(keystates[SDL_SCANCODE_LEFT]){
                angle += 5;
                if(angle > 360){angle = 0;}
            }
            if(keystates[SDL_SCANCODE_RIGHT]){
                angle -= 5;
                if(angle < 0){angle = 360;}
            }
            if(keystates[SDL_SCANCODE_COMMA]){
                brot.increaseRes(1.5);
                SDL_Delay(200);
            }
            if(keystates[SDL_SCANCODE_PERIOD]){
                brot.increaseRes(1/1.5);
                SDL_Delay(200);
            }
            if(keystates[SDL_SCANCODE_RETURN]){
                int texW;
                int texH;
                SDL_QueryTexture(Tex,NULL,NULL,&texW,&texH);
                int winW;
                int winH;
                SDL_GetWindowSize(window,&winW,&winH);
                if (winW == texW && winH == texH){
                    SDL_SetWindowSize(window,screen.w,screen.h);
                }
                else{
                    SDL_SetWindowSize(window,texW,texH);
                }
                SDL_Delay(200);
            }
            if(keystates[SDL_SCANCODE_UP]){
                while(keystates[SDL_SCANCODE_UP]){
                    Tex = brot.zoom(1/1.02, Main_Renderer);

                     SDL_SetRenderTarget(Main_Renderer, NULL);
                    SDL_RenderClear(Main_Renderer);
                    SDL_RenderCopyEx(Main_Renderer,Tex,NULL,NULL,angle,NULL, SDL_FLIP_VERTICAL);
                    SDL_RenderPresent(Main_Renderer);

                    SDL_PumpEvents();
                }
                if(useOrbitTrap)
                    Tex = brot.OrbitTrap(Main_Renderer);
                else
                    Tex = brot.DrawTexture(Main_Renderer);

            }
            if(keystates[SDL_SCANCODE_DOWN]){
                while(keystates[SDL_SCANCODE_DOWN]){
                    Tex = brot.zoom(1.02, Main_Renderer);

                     SDL_SetRenderTarget(Main_Renderer, NULL);
                    SDL_RenderClear(Main_Renderer);
                    SDL_RenderCopyEx(Main_Renderer,Tex,NULL,NULL,angle,NULL, SDL_FLIP_VERTICAL);
                    SDL_RenderPresent(Main_Renderer);

                    SDL_PumpEvents();
                }
                if(useOrbitTrap)
                    Tex = brot.OrbitTrap(Main_Renderer);
                else
                    Tex = brot.DrawTexture(Main_Renderer);
            }
            if (keystates[SDL_SCANCODE_ESCAPE]){
                running = false;
            }
            if (keystates[SDL_SCANCODE_R]){
                if(useOrbitTrap)
                    Tex = brot.OrbitTrap(Main_Renderer);
                else
                    Tex = brot.DrawTexture(Main_Renderer);
                SDL_Delay(200);
            }
            if(keystates[SDL_SCANCODE_P]){
                if(keystates[SDL_SCANCODE_RSHIFT]){
                    brot.modifyPrecision(1/1.2);
                }
                else{
                    brot.modifyPrecision(1.2);
                }
                SDL_Delay(200);
            }
            if(keystates[SDL_SCANCODE_V]){
                brot.genVideo(5,Main_Renderer);
            }
            if(keystates[SDL_SCANCODE_SPACE]){
                brot.offsetToMousePos(window);
                if(useOrbitTrap)
                    Tex = brot.OrbitTrap(Main_Renderer);
                else
                    Tex = brot.DrawTexture(Main_Renderer);
                SDL_Delay(500);
            }

            else{
    //            SDL_SetRenderTarget(Main_Renderer, srcTex);
    //            SDL_RenderPresent(Main_Renderer);

                SDL_SetRenderTarget(Main_Renderer, NULL);
                SDL_RenderClear(Main_Renderer);

                SDL_RenderCopyEx(Main_Renderer,Tex,NULL,NULL,angle,NULL, SDL_FLIP_VERTICAL);
                SDL_RenderPresent(Main_Renderer);
            }
                SDL_PumpEvents();
            }

        SDL_DestroyTexture(Tex);
        p += 0.1;
        std::cout << p;


}
