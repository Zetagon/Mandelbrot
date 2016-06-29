#ifndef MANDELBROT_H
#define MANDELBROT_H
#include <SDL2/SDL.h>
#include <complex>
#include <cmath>
#include <vector>


class Mandelbrot
{
    public:
        Mandelbrot(long double width,
                    long double height,
                    long double pResolution,
                    long double pPrecision,
                    SDL_Renderer* renderer,
                    std::complex<long double> pZzero,
                    std::complex<long double> pOffset);

        virtual ~Mandelbrot();
        SDL_Texture* DrawTexture(SDL_Renderer* renderer);
        SDL_Texture* RedrawTexture(SDL_Renderer* renderer, std::complex<long double> pOffset, long double pResolution,int pWidth);
        void modifyPrecision(long double percent);
        SDL_Rect screen;
        int CalculateIterations(std::complex<long double> c);
        void offsetToMousePos();
        SDL_Texture* zoom(long double percent, SDL_Renderer* renderer);
        void increaseRes(double percent);

        long double precision;
        int resolution;
        SDL_Texture* Tex;
        std::complex<long double> Zzero;
        std::complex<long double> offset;
        int MAX_ITERATIONS;
        std::vector<long int> Histogram;
        std::vector<std::vector<long int>> iterations;
        int r;
        int g;
        int b;
        int a;
        int w;
        int originalW;
        int originalH;
        long double originalU;
        int h;
        long double mathematicalW;
        long double mathematicalH;
        long double unit;
    protected:
    private:
};

#endif // MANDELBROT_H
