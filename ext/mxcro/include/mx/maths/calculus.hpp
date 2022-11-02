#ifndef _MX_MATHS_CALCULUS_H_
#define _MX_MATHS_CALCULUS_H_

#define _USE_MATH_DEFINES
#include <math.h>
#include <array>
#include <random>

namespace mx
{

////////////
// Helpers

float degreesToRadians(float degrees);

////////////
// Calculus

// linear interpolation between start and end
float lerp(float start, float end, float t);
float clamp(float value, float min, float max);

//////////
// RANDOM

class Random {
public:
    Random();
    float operator()() ;
    float range(float min, float max) ;

private:
    std::uniform_real_distribution<float> f32Distribution;
    std::random_device device;
    std::mt19937 gen;
};

} // namespace mx

#endif //_MX_MATHS_CALCULUS_H_