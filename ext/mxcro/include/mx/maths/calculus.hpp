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

/**
 * @brief Convert degrees to radians
 * @param degrees angle in degrees
 * @return float angle in radians
 */
float degreesToRadians(float degrees);

////////////
// Calculus

/**
 * @brief Linear interpolate between start and end
 * @param start start value
 * @param end end value
 * @param t interpolation [0-1]
 * @return float - interpolated value
 */
float lerp(float start, float end, float t);
/**
 * @brief Clamp a value between min and max
 * @param value value to clamp
 * @param min minimum
 * @param max maximum
 * @return float the clamped value 
 */
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