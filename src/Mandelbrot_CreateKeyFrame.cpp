#include "Mandelbrot.h"
/*
*
*Creates a 'keyframe', a saved state in.
*The state can be found in the vector<std::unique_ptr<Mandelbrot>> keyFrames
*
*
*/
void Mandelbrot::CreateKeyFrame(SDL_Renderer* renderer){
    std::unique_ptr<Mandelbrot>(new Mandelbrot(w, h, unit, MAX_ITERATIONS, renderer,offset));
}
