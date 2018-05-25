#include "Mandelbrot.h"
/*
*
*Creates a 'keyframe', a saved state in.
*The state can be found in the vector<std::unique_ptr<Mandelbrot>> keyFrames
*
*
*/
void Mandelbrot::CreateKeyFrame(SDL_Renderer* renderer){
    std::unique_ptr<Mandelbrot_Keyframe>temp(new Mandelbrot_Keyframe(unit,offset.real(),offset.imag(),MAX_ITERATIONS)) ;
    keyFrames.push_back(std::move(temp));
}
