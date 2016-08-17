#include "CApp.h"

void CApp::HandleRendering(){
    SDL_SetRenderTarget(Main_Renderer, NULL);
    SDL_RenderClear(Main_Renderer);

    SDL_RenderCopyEx(Main_Renderer,Tex,NULL,NULL,angle,NULL, SDL_FLIP_VERTICAL);
    SDL_RenderPresent(Main_Renderer);
}
