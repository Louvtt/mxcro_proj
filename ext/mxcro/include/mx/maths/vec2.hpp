#ifndef _MX_MATHS_VEC2_H_
#define _MX_MATHS_VEC2_H_

#include "calculus.hpp"

namespace mx {

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

vec2 lerp(vec2 start, vec2 end, float t);

} // namespace mx

#endif //_MX_MATHS_VEC2_H_