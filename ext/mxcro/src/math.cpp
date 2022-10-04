#include "mx/math.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <limits.h>
constexpr float DEG2RAD = M_PI / 180.f;

mx::vec2 mx::vec2::operator-() const
{
    return mx::vec2{-x, -y};
}
mx::vec2 mx::vec2::operator+(const mx::vec2& other) const
{
    return mx::vec2{x + other.x, y + other.y};
}
mx::vec2 mx::vec2::operator-(const mx::vec2& other) const
{
    return mx::vec2{x - other.x, y - other.y};
}
mx::vec2 mx::vec2::operator*(const mx::vec2& other) const
{
    return mx::vec2{x * other.x, y * other.y};
}
mx::vec2 mx::vec2::operator/(const mx::vec2& other) const
{   
    return mx::vec2{x / other.x, y / other.y};
}

mx::vec2 mx::vec2::operator*(float other) const
{
    return mx::vec2{x * other, y * other};
}
mx::vec2 mx::vec2::operator/(float other) const
{   
    return mx::vec2{x / other, y / other};
}

void mx::vec2::operator+=(const mx::vec2& other)
{
    x += other.x;
    y += other.y;
} 
void mx::vec2::operator-=(const mx::vec2& other)
{
    x -= other.x;
    y -= other.y;
} 
void mx::vec2::operator*=(const mx::vec2& other)
{
    x *= other.x;
    y *= other.y;
} 
void mx::vec2::operator/=(const mx::vec2& other)
{
    x /= other.x;
    y /= other.y;
} 

void mx::vec2::operator*=(float other)
{
    x *= other;
    y *= other;
} 
void mx::vec2::operator/=(float other)
{
    float inv = 1.f / other;
    x *= inv;
    y *= inv;
} 

bool mx::vec2::operator==(const mx::vec2& other) const
{
    return (
        x == other.x &&
        y == other.y
    );
}

float mx::vec2::length() const
{
    return sqrt(x*x + y*y);
}
float mx::vec2::sqrLength() const
{
    return x*x + y*y;
}
mx::vec2 mx::vec2::normalized() const
{
    float l     = sqrt(x*x + y*y);
    // avoid dividing by zero
    if(l == 0) return mx::vec2{0.f, 0.f};

    float inv_l = 1.f / l;
    return mx::vec2{
        x * inv_l,
        y * inv_l
    };
}
float mx::vec2::dot(const mx::vec2& other) const
{
    return x * other.x + y * other.y;
}

#define IX(x, y) (x+y*4)

mx::mat4::mat4(float _identityValue)
{
    for(int i = 0; i < 4; ++i)
       for(int j = 0; j < 4; ++j)
            data[IX(i,j)] = (i == j) ?  _identityValue : 0.f;
}
mx::mat4 mx::mat4::ortho(float _sizex, float _sizey)
{
    mx::mat4 proj = mx::mat4(); // identity

    float right = _sizex * .5f;
    float left  = -right;
    float top    = _sizey * .5f;
    float bottom = -top;

    float rl = _sizex; // width
    float tb = _sizey; // height

    // scale
    proj.data[IX(0, 0)] = 2.f / rl;
    proj.data[IX(1, 1)] = 2.f / tb;
    proj.data[IX(2, 2)] = 1.f;
    proj.data[IX(3, 3)] = 1.f;

    // translation
    proj.data[IX(0, 3)] = -(right + left) / rl;
    proj.data[IX(1, 3)] = -(top + bottom) / tb;
    proj.data[IX(2, 3)] = 0.f;

    return proj;
}
mx::mat4 mx::mat4::persp(float _fov, float _aspect, float _far, float _near)
{
    mx::mat4 proj = mx::mat4(); // identity
    float tangent = tanf(_fov * .5f * DEG2RAD);
    float height  = _near * tangent;
    float width  = height * _aspect;

    // scales
    proj.data[IX(0, 0)] = _near / width;
    proj.data[IX(1, 1)] = _near / height;
    proj.data[IX(2, 2)] = -(_far + _near) / (_far - _near);

    // translate
    proj.data[IX(0, 2)] = 0.f;
    proj.data[IX(1, 2)] = 0.f;
    proj.data[IX(3, 2)] =-1.f;
    proj.data[IX(2, 3)] =-(2.f * _far * _near) / (_far - _near);
    proj.data[IX(3, 3)] = 0.f;

    return proj;
}

// calculus


float mx::lerp(float start, float end, float t)
{
    return t * end + (1 - t) * start;
}
mx::vec2 mx::lerp(mx::vec2 start, mx::vec2 end, float t)
{
    return end * t + start * (1 - t);
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