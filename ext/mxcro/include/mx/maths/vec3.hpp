#ifndef _MX_MATHS_VEC3_H_
#define _MX_MATHS_VEC3_H_

#include "calculus.hpp"

namespace mx
{

struct vec3
{
    float x, y, z;

    // operators
    
    vec3 operator-() const;
    vec3 operator+(const vec3& other) const;
    vec3 operator-(const vec3& other) const;
    vec3 operator*(const vec3& other) const;
    vec3 operator/(const vec3& other) const;

    vec3 operator*(float other) const;
    vec3 operator/(float other) const;

    void operator+=(const vec3& other);
    void operator-=(const vec3& other);
    void operator*=(const vec3& other);
    void operator/=(const vec3& other);

    void operator*=(float other);
    void operator/=(float other);

    bool operator==(const vec3& other) const;

    // calculus

    float length() const;
    float sqrLength() const;
    vec3 normalized() const;
    float dot(const vec3& other) const;
    vec3 cross(const vec3& other) const;
};

} // namespace mx


#endif //_MX_MATHS_VEC3_H_