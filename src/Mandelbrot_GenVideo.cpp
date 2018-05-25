#include "Mandelbrot.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
template < typename T > std::string to_string(const T& n){
    std::ostringstream stm;
    stm << n;
    return stm.str();
}
void Mandelbrot::genVideo(int frames,SDL_Renderer* renderer){


    std::vector<long double> kUnitV;
    std::vector<long double> mUnitV;
    std::vector<long double> kOffsetXV;
    std::vector<long double> mOffsetXV;
    std::vector<long double> kOffsetYV;
    std::vector<long double> mOffsetYV;
    std::vector<double> kMax_IterationsV;
    std::vector<double> mMax_IterationsV;

    int framesPerKeyFrame = frames;
    for(unsigned int i = 0; i < keyFrames.size() - 1; i++){
        //y = k * x + m
        long double kUnit = (keyFrames.at(i + 1)->unit - keyFrames.at(i)->unit) / framesPerKeyFrame;//k-värdet för Unit, unit kommer att förrändras enligt en rät linje mellan två keyframes
        kUnitV.push_back(kUnit);
        mUnitV.push_back(keyFrames.at(i)->unit);

        long double kOffsetX = (keyFrames.at(i + 1)->offsetX - keyFrames.at(i)->offsetX) / framesPerKeyFrame;
        long double kOffsetY = (keyFrames.at(i + 1)->offsetY - keyFrames.at(i)->offsetY) / framesPerKeyFrame;
        kOffsetXV.push_back(kOffsetX);
        kOffsetYV.push_back(kOffsetY);
        mOffsetXV.push_back(keyFrames.at(i)->offsetX);
        mOffsetYV.push_back(keyFrames.at(i)->offsetY);

        double kMax_Iterations = (keyFrames.at(i + 1)->MAX_ITERATIONS - keyFrames.at(i)->MAX_ITERATIONS) / (double)framesPerKeyFrame;
        kMax_IterationsV.push_back(kMax_Iterations);
        mMax_IterationsV.push_back(keyFrames.at(i)->MAX_ITERATIONS);
    }
    //makes  'graphs' y = k * x + m, where y is  ex. tempUnit, k is ex. kUnitV.at(i), and m is ex. mUnitV.at(i)
    //the graphs are straight lines between the keyframes attributes(unit, maxiterations and offset)
    for(unsigned int i = 0; i < keyFrames.size() - 1; i++){
        for(int x = 0; x < framesPerKeyFrame; x++){
            long double tempUnit = kUnitV.at(i) * x + mUnitV.at(i);
            long double tempOffsetX = kOffsetXV.at(i) * x +mOffsetXV.at(i);
            long double tempOffsetY = kOffsetYV.at(i) * x +mOffsetYV.at(i);
            std::complex<long double> tempOffset(tempOffsetX,tempOffsetY);
            double tempMax_Iterations = kMax_IterationsV.at(i) * x + mMax_IterationsV.at(i);
//            Mandelbrot brot(w,h,tempUnit,tempMax_Iterations,renderer, tempOffset);
            Mandelbrot brot(w * tempUnit,h * tempUnit,tempUnit,tempMax_Iterations,renderer, tempOffset);
//            brot.w = w;
//            brot.h = h;
            SDL_Surface* surface = brot.DrawSurface();
            int t = x + framesPerKeyFrame * i;
            std::string filename= "1\\videoFile" + to_string(t) + ".bmp";
            std::fstream my_stream;
            my_stream.open(filename.c_str(),std::fstream::binary | std::fstream::in | std::fstream::out|std::fstream::trunc);
            my_stream.close();

            SDL_SaveBMP(surface,filename.c_str());
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_RenderCopyEx(renderer,texture,NULL,NULL,0,NULL, SDL_FLIP_VERTICAL);

            SDL_RenderPresent(renderer);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }
}
