#include "Mandelbrot.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

void Mandelbrot::saveBMP(SDL_Renderer* renderer){
  SDL_Surface* surface = this->DrawSurface();
  std::string filename= "Saved_Image.bmp";

  std::fstream my_stream;
  my_stream.open(filename.c_str(),std::fstream::binary | std::fstream::in | std::fstream::out|std::fstream::trunc);
  my_stream.close();

  SDL_SaveBMP(surface,filename.c_str());
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_RenderCopyEx(renderer,texture,NULL,NULL,0,NULL, SDL_FLIP_VERTICAL);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}
