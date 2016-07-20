#include <iostream>
#include "CApp.h"


int main()
{
    std::cout <<"Controls\n - Up-Arrow  -- Zoom in\n - Down-Arrow -- Zoom out\n - Period( . ) -- increase the resolution\n - Comma( , ) -- decrease the resolution\n - P -- increase the precision(the max number of iterations)\n - Shift + P -- decrease the precision(the max number of iterations)\n - R -- Rerender the image( with the new resolution and precision)\n - Space -- Set the center of the image at the mouse pointer and rerender the image";
    CApp theApp;
    theApp.OnDefault();


    return 0;
}
