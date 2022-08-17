#ifndef _MX_MATH_H_
#define _MX_MATH_H_


namespace mx
{

struct vec2
{
    float x, y;

    // operators
    
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

    float data[16];
};


// calculus

// linear interpolation between start and end
template <typename T>
T lerp(T start, T end, float t);
template <>
float lerp(float start, float end, float t);
template <>
vec2 lerp(vec2 start, vec2 end, float t);

template <typename T>
constexpr T clamp(T value, T min, T max);

} // namespace mx


#endif //_MX_MATH_H_