#include "Mandelbrot_Keyframe.h"

Mandelbrot_Keyframe::Mandelbrot_Keyframe(long double pUnit, long double pOffsetX, long double pOffsetY, int pMax_iterations)
{
    //ctor
    unit = pUnit;
    offsetX = pOffsetX;
    offsetY = pOffsetY;
    MAX_ITERATIONS = pMax_iterations;
}

Mandelbrot_Keyframe::~Mandelbrot_Keyframe()
{
    //dtor
}
