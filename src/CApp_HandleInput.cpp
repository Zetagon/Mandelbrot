#include "CApp.h"
#include <iostream>
void CApp::HandleInput(){
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    SDL_Rect screen;
    SDL_GetDisplayBounds(0,&screen);

    {//this block is to keep scrollUnit local
        double scrollUnit = 0.1;
        if(keystates[SDL_SCANCODE_W]){
            Tex = brot->moveOffset(Main_Renderer,0,scrollUnit);
        }
        if(keystates[SDL_SCANCODE_S]){
            Tex = brot->moveOffset(Main_Renderer,0,-scrollUnit);
        }
        if(keystates[SDL_SCANCODE_A]){
            Tex = brot->moveOffset(Main_Renderer,-scrollUnit ,0);
        }
        if(keystates[SDL_SCANCODE_D]){
            Tex = brot->moveOffset(Main_Renderer,scrollUnit ,0);
        }
    }
    if(keystates[SDL_SCANCODE_O]){
        if(useOrbitTrap)
            useOrbitTrap = false;
        else
            useOrbitTrap = true;
        SDL_Delay(200);
    }

    if(keystates[SDL_SCANCODE_COMMA]){
        brot->increaseRes(1.5);
        SDL_Delay(200);
    }
    if(keystates[SDL_SCANCODE_PERIOD]){
        brot->increaseRes(1/1.5);
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
        Tex = brot->getTexture();
        SDL_Delay(200);
    }

    double zoomModifier = 1.02;
    if(keystates[SDL_SCANCODE_UP]){
        while(keystates[SDL_SCANCODE_UP]){
            Tex = brot->zoom(1/zoomModifier, Main_Renderer);

             SDL_SetRenderTarget(Main_Renderer, NULL);
            SDL_RenderClear(Main_Renderer);
            SDL_RenderCopyEx(Main_Renderer,Tex,NULL,NULL,angle,NULL, SDL_FLIP_VERTICAL);
            SDL_RenderPresent(Main_Renderer);

            SDL_PumpEvents();
        }
        if(useOrbitTrap)
            Tex = brot->OrbitTrap(Main_Renderer);
        else
            Tex = brot->DrawTexture(Main_Renderer);

    }
    if(keystates[SDL_SCANCODE_DOWN]){
        while(keystates[SDL_SCANCODE_DOWN]){
            Tex = brot->zoom(zoomModifier, Main_Renderer);

             SDL_SetRenderTarget(Main_Renderer, NULL);
            SDL_RenderClear(Main_Renderer);
            SDL_RenderCopyEx(Main_Renderer,Tex,NULL,NULL,angle,NULL, SDL_FLIP_VERTICAL);
            SDL_RenderPresent(Main_Renderer);

            SDL_PumpEvents();
        }
        std::cout << "down";
        if(useOrbitTrap)
            Tex = brot->OrbitTrap(Main_Renderer);
        else
            Tex = brot->DrawTexture(Main_Renderer);
    }

    if (keystates[SDL_SCANCODE_ESCAPE]){
        running = false;
    }
    if (keystates[SDL_SCANCODE_R]){
        if(useOrbitTrap)
            Tex = brot->OrbitTrap(Main_Renderer);
        else
            Tex = brot->DrawTexture(Main_Renderer);
        Tex = brot->getTexture();
        SDL_Delay(200);
    }
    if(keystates[SDL_SCANCODE_P]){
        if(keystates[SDL_SCANCODE_RSHIFT]){
            brot->modifyPrecision(1/1.2);
        }
        else{
            brot->modifyPrecision(1.2);
        }
        SDL_Delay(200);
    }
    if(keystates[SDL_SCANCODE_V]){
        brot->genVideo(5,Main_Renderer);
    }
    if(keystates[SDL_SCANCODE_SPACE]){
        brot->offsetToMousePos(window);
        if(useOrbitTrap)
            Tex = brot->OrbitTrap(Main_Renderer);
        else
            Tex = brot->DrawTexture(Main_Renderer);
        SDL_Delay(500);
    }

    SDL_PumpEvents();
}
