#include "Mandelbrot.h"
#include <iostream>

Mandelbrot::Mandelbrot(long double width,
                        long double height,
                        long double pResolution,
                        long double pPrecision,
                        SDL_Renderer* renderer,
                        std::complex<long double> pZzero,
                        std::complex<long double> pOffset)
{
    //ctor
    resolution = pResolution;
    precision = pPrecision;
    MAX_ITERATIONS = pow(10 , precision);
    std::vector<long int> temp(MAX_ITERATIONS);
    Histogram = temp;
    Zzero = pZzero;
    unit = pResolution;//(double)1/(pow(10,resolution));
    originalU = unit;
    mathematicalW = width;
    w = mathematicalW/unit;
    originalW = w;
    mathematicalH = height;
    h = mathematicalH / unit;
    originalH = h;
    offset = pOffset;
    std::vector<long int> temp2(2*h);
    for(int x = 0; x < 2*w; x++){
        iterations.push_back(temp2);
    }
    SDL_GetDisplayBounds(0,&screen);

}

Mandelbrot::~Mandelbrot()
{
    //dtor
    SDL_DestroyTexture(Tex);
}

SDL_Texture* Mandelbrot::DrawTexture(SDL_Renderer* renderer){
    Tex = SDL_CreateTexture(renderer,
                            SDL_PIXELFORMAT_ARGB8888,
                            SDL_TEXTUREACCESS_TARGET,
                            2 * w,
                            2* h);
    std::complex<long double> c;

    SDL_SetRenderTarget(renderer,Tex);
    SDL_RenderClear(renderer);

    for(int x = -w; x < w; x++){
        for(int y = -h; y < h; y++){
            std::complex<long double> temp(x*unit + offset.real(), y*unit + offset.imag());
            c = temp;

            int n = CalculateIterations(c);
            iterations.at(x + w).at(y + h) = n;
        }
    }
    std::vector<int> bandlimits;
    bandlimits.push_back(1);//will always be 1
//    bandlimits.push_back(MAX_ITERATIONS * 0.24);
    bandlimits.push_back(MAX_ITERATIONS * 0.16);
    bandlimits.push_back(MAX_ITERATIONS * 0.42);
    bandlimits.push_back(MAX_ITERATIONS * 0.6425);
    bandlimits.push_back(MAX_ITERATIONS * 0.8575);
//    bandlimits.push_back(MAX_ITERATIONS * 0.8);
//    bandlimits.push_back(MAX_ITERATIONS * 0.9);
    bandlimits.push_back(MAX_ITERATIONS);
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

//    int band_total = 0;
//    for(int i = 1; i < MAX_ITERATIONS * 0.5; i++){
//        band_total += Histogram.at(i);
//    }
//    int running_total = 0;
//    std::vector<long double> percents(MAX_ITERATIONS);
//    for (int i = 2; i < MAX_ITERATIONS * 0.5; i++){
//        running_total += Histogram.at(i);
//        percents.at(i) = (long double)running_total/band_total;
//    }
//
//    band_total = 0;
//    for(int i = MAX_ITERATIONS * 0.5; i < MAX_ITERATIONS; i++){
//        band_total += Histogram.at(i);
//    }
//     running_total = 0;
//
//    for (int i = MAX_ITERATIONS * 0.5 +1 ; i < MAX_ITERATIONS; i++){
//        running_total += Histogram.at(i);
//        percents.at(i) = (long double)running_total/band_total;
//    }

    for(int x = -w; x < w; x++){
        for(int y = -h; y < h; y++){
            int n = iterations.at(x + w).at(y + h);
            if(n > bandlimits.at(0) && n<bandlimits.at(1)){
                r = 32 * percents.at(n);//155 * percents.at(n)+ 100;
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
            SDL_SetRenderDrawColor(renderer,r,g,b,a);
            SDL_RenderDrawPoint(renderer,w + x,
                                h + y);
        }
    }
    originalW = w;
    originalH = h;
    originalU = unit;
    SDL_SetRenderTarget(renderer, NULL);
    return Tex;
}


SDL_Texture* Mandelbrot::RedrawTexture(SDL_Renderer* renderer, std::complex<long double> pOffset, long double pResolution, int pWidth){
    offset = pOffset;
    resolution  = pResolution;
    unit = 1/(pow(10,resolution));

    w = pWidth/unit;
    std::cout << "offset:" << offset << "\nresolution" << resolution << "\nwidth:" << w;
    return DrawTexture(renderer);

}

int Mandelbrot::CalculateIterations(std::complex<long double> c){
    std::complex<long double> Z;
    long double distance = 0;
    std::complex<long double> Zn = Zzero;
    int n = 0;
    for( n = 0; n <= MAX_ITERATIONS && distance < 2; n++){
        Z = pow(Zn, 2) +c;
        distance = sqrt(pow(Z.real() , 2 ) + pow(Z.imag() - Zzero.imag() , 2));
        Zn = Z;
    }
//
    if(!(n < MAX_ITERATIONS )){
        n = -1;
    }
    else{
        Histogram[n] = Histogram[n] + 1;
    }

//    std::cout <<n ;
    return n;
}

void Mandelbrot::offsetToMousePos(){
    int x,y;
    SDL_GetMouseState(&x,&y);
    std::complex<long double> temp((double)x / screen.w * 2 * w * unit - w  * unit+ offset.real(), (double)y / - screen.h * 2 * h * unit + h * unit + offset.imag());
    offset = temp;
//    std::cout << w << "  " << (double)x/ screen.w * w << "  " << screen.w <<"  " << x << "\n" ;
    std::cout << temp.real() << "  " << temp.imag() << "\n";

}

SDL_Texture* Mandelbrot::zoom(long double percent, SDL_Renderer* renderer){
//    int tempW = w;
//    int tempH = h;
//    w = w * percent;
//    h =  (long double)w* screen.h / screen.w;
//    std::cout << "ratio after:  " << (double)h/w<< "\n";
//    long double iw = (long double)tempW/unit;
//
//    iterations.clear();
//    std::vector<long int> temp2(2*h);
//    for(int x = 0; x < 2*w; x++){
//        iterations.push_back(temp2);
//    }
//
//

    SDL_Texture* returnTex = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,2 * w, 2 * h);
    SDL_SetRenderTarget(renderer, returnTex);
    SDL_RenderClear(renderer);
    if(unit * percent < originalU){
        unit = unit*percent;


        SDL_Rect SrcR = {w - w * unit / originalU,h - h * unit / originalU,2 * w * unit / originalU, 2* h / originalU * unit};//{(tempW - w)/2,(tempH - h)/2,w, h};
        std::cout << unit << "\n";
        SDL_RenderCopy(renderer, Tex, &SrcR, NULL);}
    else{
        unit = unit * percent;
        Tex = DrawTexture(renderer);
    }


    SDL_SetRenderTarget(renderer, NULL);

   // returnTex = DrawTexture(renderer);
    return returnTex;
}

void Mandelbrot::increaseRes(double percent){
    std::cout << "ljadlfj";
    long double tempW = w * unit;
    long double tempH = h * unit;
    unit = unit * percent;
    w = tempW / unit;
    h = tempH / unit;
    iterations.clear();
    std::vector<long int> temp2(2*h);
    for(int x = 0; x < 2*w; x++){
        iterations.push_back(temp2);
    }
    std::cout << "w:" << w << "unit:" << unit << "\n";
}

void Mandelbrot::modifyPrecision(long double percent){
    MAX_ITERATIONS = MAX_ITERATIONS * percent;
    std::vector<long int> temp(MAX_ITERATIONS);
    Histogram = temp;
}
