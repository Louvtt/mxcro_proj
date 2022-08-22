#ifndef _MX_MATH_H_
#define _MX_MATH_H_

#include <array>
#include <random>

namespace mx
{

struct vec2
{
    float x, y;

    // operators
    
    vec2 operator-() const;
    vec2 operator+(const vec2& other) const;
    vec2 operator-(const vec2& other) const;
    vec2 operator*(const vec2& other) const;
    vec2 operator/(const vec2& other) const;

    vec2 operator*(float other) const;
    vec2 operator/(float other) const;

    void operator+=(const vec2& other);
    void operator-=(const vec2& other);
    void operator*=(const vec2& other);
    void operator/=(const vec2& other);

    void operator*=(float other);
    void operator/=(float other);

    bool operator==(const vec2& other) const;

    // calculus

    float length() const;
    float sqrLength() const;
    vec2 normalized() const;
    float dot(const vec2& other) const;
};

class mat4
{
public:
    // for model mat
    mat4(float identityValue = 1.f);
    // Ortho
    static mat4 ortho(float sizex, float sizey);
    // PERSP
    static mat4 persp(float fov, float aspectRatio, float far, float near);

    std::array<float, 16> data{};
};


// calculus

// linear interpolation between start and end
float lerp(float start, float end, float t);
vec2 lerp(vec2 start, vec2 end, float t);

float clamp(float value, float min, float max);

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


#endif //_MX_MATH_H_