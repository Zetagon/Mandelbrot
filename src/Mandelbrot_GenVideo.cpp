#include "Mandelbrot.h"
#include <fstream>
#include <string>
#include <sstream>
template < typename T > std::string to_string(const T& n){
    std::ostringstream stm;
    stm << n;
    return stm.str();
}
void Mandelbrot::genVideo(int frames,SDL_Renderer* renderer){

    SDL_Surface* surface;
    for(int i = frames; i > 0; i--){
        surface = DrawSurface();

        std::string filename= "videoFile" + to_string(i);
        std::fstream my_stream;
        my_stream.open(filename.c_str(),std::fstream::binary | std::fstream::in | std::fstream::out|std::fstream::trunc);
        my_stream.close();

        SDL_SaveBMP(surface,filename.c_str());
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopyEx(renderer,texture,NULL,NULL,0,NULL, SDL_FLIP_VERTICAL);

        SDL_RenderPresent(renderer);

        ZoomSurface(0.9, surface);
        }
    SDL_FreeSurface(surface);
}
