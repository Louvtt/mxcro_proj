#include "mx/maths/math.hpp"

#include <time.h>
#include <string.h>
#include <limits.h>

constexpr float DEG2RAD = M_PI / 180.f;
float mx::degreesToRadians(float degrees)
{
    return degrees * DEG2RAD;
}

// calculus


float mx::lerp(float start, float end, float t)
{
    return t * end + (1 - t) * start;
}

float mx::clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

mx::Random::Random() {
    gen = std::mt19937(device());
    gen.seed(time(NULL));
    f32Distribution = std::uniform_real_distribution<float>(0.f, 1.f);
}

float mx::Random::operator()() {
    return f32Distribution(gen);
}

float mx::Random::range(float _min, float _max) {
    return f32Distribution(gen) * (_max - _min) + _min;
}