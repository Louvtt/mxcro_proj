#include "mx/maths/vec3.hpp"

#include <iostream>

///////////////////////////////////////
// VEC3

mx::vec3 mx::vec3::operator-() const
{
    return mx::vec3{-x, -y, -z};
}
mx::vec3 mx::vec3::operator+(const mx::vec3& other) const
{
    return mx::vec3{x + other.x, y + other.y, z + other.z};
}
mx::vec3 mx::vec3::operator-(const mx::vec3& other) const
{
    return mx::vec3{x - other.x, y - other.y, z - other.z};
}
mx::vec3 mx::vec3::operator*(const mx::vec3& other) const
{
    return mx::vec3{x * other.x, y * other.y, z * other.z};
}
mx::vec3 mx::vec3::operator/(const mx::vec3& other) const
{   
    return mx::vec3{x / other.x, y / other.y, z / other.z};
}

mx::vec3 mx::vec3::operator*(float other) const
{
    return mx::vec3{x * other, y * other, z * other};
}
mx::vec3 mx::vec3::operator/(float other) const
{   
    float inv_o = 1.f/other;
    return mx::vec3{x * inv_o, y * inv_o, z * inv_o};
}

void mx::vec3::operator+=(const mx::vec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
} 
void mx::vec3::operator-=(const mx::vec3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
} 
void mx::vec3::operator*=(const mx::vec3& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
} 
void mx::vec3::operator/=(const mx::vec3& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
} 

void mx::vec3::operator*=(float other)
{
    x *= other;
    y *= other;
    z *= other;
} 
void mx::vec3::operator/=(float other)
{
    float inv = 1.f / other;
    x *= inv;
    y *= inv;
    z *= inv;
} 

bool mx::vec3::operator==(const mx::vec3& other) const
{
    return (
        x == other.x &&
        y == other.y &&
        z == other.z
    );
}

float mx::vec3::length() const
{
    return sqrt(x*x + y*y + z*z);
}
float mx::vec3::sqrLength() const
{
    return x*x + y*y + z*z;
}
mx::vec3 mx::vec3::normalized() const
{
    float l = sqrt(x*x + y*y + z*z);
    // avoid dividing by zero
    if(l == 0) return mx::vec3{0.f, 0.f, 0.f};

    float inv_l = 1.f / l;
    return mx::vec3{
        x * inv_l,
        y * inv_l,
        z * inv_l
    };
}
float mx::vec3::dot(const mx::vec3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

mx::vec3 mx::vec3::cross(const mx::vec3& other) const
{
    return mx::vec3 {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}
std::ostream& mx::operator<<(std::ostream& o, const mx::vec3& v)
{
    o << "vec3 [" << v.x << ", " << v.y << ", " << v.z << "]";
    return o;
}

mx::vec3 mx::lerp(vec3 start, vec3 end, float t)
{
    return end * t + start * (1 - t);
}
