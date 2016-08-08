#include "Mandelbrot.h"

/*
*Draws a mandelbrot image onto a SDL_Surface, similar to DrawTexture()
*
*
*
*
*/
SDL_Surface* Mandelbrot::DrawSurface(){

    /*using the default masks for the depth: */
    SDL_Surface* surface = SDL_CreateRGBSurface(0,w * 2 ,h * 2,32,0,0,0,0);

 for(int x = -w; x < w; x++){
        for(int y = -h; y < h; y++){
            std::complex<long double> c(x*unit + offset.real(), y*unit + offset.imag());

            int n = CalculateIterations(c);
            iterations.at(x + w).at(y + h) = n;
        }
    }
    int highestIteration = MAX_ITERATIONS;
    std::vector<int> bandlimits;
    bandlimits.push_back(1);//will always be 1
    bandlimits.push_back(highestIteration * 0.16);
    bandlimits.push_back(highestIteration * 0.42);
    bandlimits.push_back(highestIteration * 0.6425);
    bandlimits.push_back(highestIteration * 0.8575);
    bandlimits.push_back(highestIteration);
    std::vector<long double> percents(MAX_ITERATIONS);
    for(int a = 1; a < bandlimits.size(); a++){
        int band_total = 0;
        for(int b = bandlimits.at(a - 1); b < bandlimits.at(a) ;b++){
            band_total += Histogram.at(b);
        }
        int running_total = 0;

        for(int b = bandlimits.at(a- 1) + 1; b < bandlimits.at(a); b++){
            running_total += Histogram.at(b);
            percents.at(b) = (long double)running_total / band_total;
        }
    }

    std::vector<int> rValue;
    std::vector<int> gValue;
    std::vector<int> bValue;
    //first colour
    rValue.push_back(32);
    for(int x = -w; x < w; x++){
        for(int y = -h; y < h; y++){
            int n = iterations.at(x + w).at(y + h);
            if(n > bandlimits.at(0) && n<bandlimits.at(1)){
                r = 32 * (1 - percents.at(n));//155 * percents.at(n)+ 100;
                g = 7 * (1.0 - percents.at(n)) + 107 * percents.at(n);
                b = 100 * (1.0 - percents.at(n)) + 203 * percents.at(n) ;
                a = 255;

            }
            else if(n > bandlimits.at(1) && n < bandlimits.at(2)){
                r = 32 * (1.0-percents.at(n)) + 237 * percents.at(n);//255;// - 255*percents.at(n);
                g = 107 * (1.0 - percents.at(n)) + 255 * percents.at(n) ;
                b = 203 * (1.0 - percents.at(n)) + 255 *percents.at(n);//155 * percents.at(n) + 100;

                a = 255;
            }
            else if(n > bandlimits.at(2) && n < bandlimits.at(3)){
                r = 237 * (1.0 - percents.at(n)) + 255 *percents.at(n);
                g = 255 * (1.0 - percents.at(n)) + 170 * percents.at(n) ;
                b = 255 * (1.0 - percents.at(n)); //155 * percents.at(n);
                a = 255;
            }
            else if(n > bandlimits.at(3) && n < bandlimits.at(4)){
                r = 255 * (1.0 - percents.at(n));
                g = 170 * (1.0 - percents.at(n)) + 2 * percents.at(n) ;
                b = 0 ; //155 * percents.at(n);
                a = 255;
            }
            else if(n < 0){
                r = 0;
                g = 0;
                b = 0;
                a = 0;

            }
               SDL_PixelFormat* format = surface->format;
            SDL_Rect destR = {x + w,y + h,1,1};
            SDL_FillRect(surface,&destR,SDL_MapRGB(format,r,g,b));
        }
    }
    return surface;
}
