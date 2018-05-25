#ifndef MANDELBROT_KEYFRAME_H
#define MANDELBROT_KEYFRAME_H


class Mandelbrot_Keyframe
{
    public:
        Mandelbrot_Keyframe(long double pUnit, long double pOffsetX, long double pOffsetY, int pMax_iterations);
        virtual ~Mandelbrot_Keyframe();

        long double unit;
        int MAX_ITERATIONS;
        long double offsetX;
        long double offsetY;

    protected:

    private:

};

#endif // MANDELBROT_KEYFRAME_H
