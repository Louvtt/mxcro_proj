#include "mx/maths/vec2.hpp"


// VEC2 

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

mx::vec2 mx::lerp(mx::vec2 start, mx::vec2 end, float t)
{
    return end * t + start * (1 - t);
}