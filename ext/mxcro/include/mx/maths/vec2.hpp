#ifndef _MX_MATHS_VEC2_H_
#define _MX_MATHS_VEC2_H_

#include "calculus.hpp"


namespace mx {

/**
 * @brief Represent a 2D Vector (x and y)
 */
struct vec2
{
    /** @brief Coordinates of the vector */
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
     * @return vec2 - the normalized vector
     */
    vec2 normalized() const;
    /**
     * @brief Return the result of the dot product of this vector and other
     * @param other Another 2D vector 
     * @return float - the result of the dot product 
     */
    float dot(const vec2& other) const;
};

/**
 * @brief Linear Interpolate between two 2D vectors
 * @param start First vector
 * @param end Second vector
 * @param t interpolation [0-1]
 * @return vec2 - the vector obtained throught the interpolation
 */
vec2 lerp(vec2 start, vec2 end, float t);
std::ostream& operator<<(std::ostream& o, const vec2& v);

} // namespace mx

#endif //_MX_MATHS_VEC2_H_