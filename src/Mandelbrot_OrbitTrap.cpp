#include "Mandelbrot.h"
/*
*
*Return: An SDL_Texture* with an image of the mandelbrot set drawn using the orbittrap technique
*
*
**/
SDL_Texture* Mandelbrot::OrbitTrap(SDL_Renderer* renderer){
    Tex = SDL_CreateTexture(renderer,
                            SDL_PIXELFORMAT_ARGB8888,
                            SDL_TEXTUREACCESS_TARGET,
                            2 * w,
                            2* h);
    SDL_SetRenderTarget(renderer,Tex);
    SDL_RenderClear(renderer);
    long double minDistance = 0;
    long double maxDistance = 2 * sqrt(8);//this is equal to sqrt(4^2 + 4^2). The greatest distance in a four by four square.

    std::vector<long double> temp(2 * h);
    std::vector<std::vector<long double>> distanceV(0); //A vector with minimum distances to the orbittrap for every pixel. distanceV.at(pixelX).at(pixelY)
    for(int x = 0; x < 2 * w; x++){
        distanceV.push_back(temp);
    }

    for(int x = -w; x < w; x++){
        for(int y = -h; y < h; y++){
            std::complex<long double> c(x*unit + offset.real(), y*unit + offset.imag());
            std::complex<long double> Z(0,0);
            int n = 0;
            long double distance = 10e6;
            for( n = 0; n <= MAX_ITERATIONS && std::abs(Z) < 2; n++){
                Z = Z * Z +c;
                long double distanceX = std::abs(Z.real() - orbitTrapPoint.real());
                long double distanceY = std::abs(Z.imag() - orbitTrapPoint.imag());

                //using pythagoras theorem to calculate the minimum distance squared to avoid using unnecessary roots.
                distance = distanceY;
//                distance = std::min(distanceX,distanceY);
//                distance = std::min(distance, distanceX * distanceX + distanceY * distanceY);
            }
            //compensating for the squareing of distance above.
             distanceV.at(w + x).at(h + y) = distance;//sqrt(distance);

             maxDistance = std::max(maxDistance, distanceV.at(w + x).at(h + y));
             minDistance = std::min(minDistance, distanceV.at(w + x).at(h + y));
        }
    }

//---------------------colouring algorithm----------------------------------
    for(int x = -w; x < w; x++){
        for(int y = -h; y < h; y++){
            int r = 0;
            int g = 0;
            int b = round((distanceV.at(w + x).at(h + y) - minDistance) / maxDistance * 255);
            g = b;
            r = b;
            SDL_SetRenderDrawColor(renderer,r,g,b,a);
            SDL_RenderDrawPoint(renderer,w + x,
                                h + y);
        }
    }

    return Tex;
}
