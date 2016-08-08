#include "Mandelbrot.h"
SDL_Surface* Mandelbrot::ZoomSurface(long double percent,SDL_Surface* surface){

    SDL_Surface* returnSurf = SDL_CreateRGBSurface(0,2 * w, 2 * h,32,0,0,0,0);

    unit = unit * percent;
    SDL_Rect SrcR = {w - w * unit / originalU,h - h * unit / originalU,2 * w * unit / originalU, 2* h / originalU * unit};//{(tempW - w)/2,(tempH - h)/2,w, h};

    if(unit > originalU){//If zooming out so that the resulting image is bigger than the current one, Do this:
        int width = (double)w / ( unit / originalU/2);
        int height = (double)h / (unit / originalU/2);
        SDL_Rect DestR = {w -  0.5 * width,h -  0.5 * height, width, height};
        SDL_BlitSurface(surface,NULL,returnSurf,&DestR);
    }
    else{
        SDL_BlitSurface(surface,&SrcR,returnSurf,NULL);
    }

    return returnSurf;
}

