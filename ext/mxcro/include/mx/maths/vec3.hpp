#ifndef _MX_MATHS_VEC3_H_
#define _MX_MATHS_VEC3_H_

#include "calculus.hpp"

namespace mx
{

/**
 * @brief Represent a 3D Vector (x, y and z)
 */
struct vec3
{
    /** @brief Coordinates of the vector */
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

    /**
     * @brief Return the length of the vector
     * @return float - the length of the vector 
     */
    float length() const;
    /**
     * @brief Return the squared length of the vector
     * @return float - the squared length of the vector 
     */
    float sqrLength() const;
    /**
     * @brief Return a normalized vector of this vector
     * @return vec3 - the normalized vector
     */
    vec3 normalized() const;
    /**
     * @brief Return the result of the dot product of this vector and other
     * @param other Another 2D vector 
     * @return float - the result of the dot product 
     */
    float dot(const vec3& other) const;
    /**
     * @brief Return the result of the cross product of this vector and other
     * @param other Another 2D vector 
     * @return vec3 - the result of the cross product 
     */
    vec3 cross(const vec3& other) const;
};

/**
 * @brief Linear Interpolate between two 3D vectors
 * @param start First vector
 * @param end Second vector
 * @param t interpolation [0-1]
 * @return vec3 - the vector obtained throught the interpolation
 */
vec3 lerp(vec3 start, vec3 end, float t);
std::ostream& operator<<(std::ostream& o, const vec3& v);

} // namespace mx


#endif //_MX_MATHS_VEC3_H_