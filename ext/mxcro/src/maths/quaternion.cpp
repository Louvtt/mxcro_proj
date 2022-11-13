#include "mx/maths/quaternion.hpp"

#include <iostream>

mx::Quaternion::Quaternion()
: real(0.0f), 
i(0.0f), j(0.0f), k(0.0f)
{ }

mx::Quaternion mx::Quaternion::operator+(const mx::Quaternion& other) const
{
    mx::Quaternion quat;
    quat.real = real + other.real;
    quat.i    = i + other.i;
    quat.j    = j + other.j;
    quat.k    = k + other.k;
    return quat;
}
mx::Quaternion mx::Quaternion::operator-(const mx::Quaternion& other) const
{
    mx::Quaternion quat;
    quat.real = real - other.real;
    quat.i    = i - other.i;
    quat.j    = j - other.j;
    quat.k    = k - other.k;
    return quat;
}
mx::Quaternion mx::Quaternion::operator*(const mx::Quaternion& other) const
{
    mx::Quaternion quat;
    // real part
    float s  = real * other.real;
          s -= i * other.i;
          s -= j * other.j;
          s -= k * other.k;
    // i axis
    float i  = real * other.i; // 1 i
          i += i * other.real; // i 1
          i += j * other.k;    // j k
          i -= k * other.j;    //-k j
    // j axis
    float j  = real * other.j;
          j += j * other.real;
          j += i * other.k;
          j -= k * other.i;
    // k axis
    float k  = real * other.k;
          k += k * other.real;
          k += i * other.j;
          k -= j * other.i;

    quat.real = s;
    quat.i    = i;
    quat.j    = j;
    quat.k    = k;
    return quat;
}

mx::Quaternion mx::Quaternion::operator*(float factor) const
{
    mx::Quaternion quat;
    quat.real = real * factor;
    quat.i    = i * factor;
    quat.j    = j * factor;
    quat.k    = k * factor;
    return quat;
}

mx::Quaternion mx::Quaternion::operator/(const mx::Quaternion& other) const
{
    return (*this) * other.inverse();
}

bool mx::Quaternion::operator==(const Quaternion& other) const
{
    return other.real == real
        && other.i    == i
        && other.j    == j
        && other.k    == k;
}


float mx::Quaternion::Re() const {
    return real;
}

mx::vec3 mx::Quaternion::Im() const {
    return mx::vec3{i, j, k};
}

float mx::Quaternion::norm() const {
    return sqrtf(real*real + i*i + j*j + k*k);
}

mx::Quaternion mx::Quaternion::conjugate() const
{
    mx::Quaternion quat;
    quat.real = real;
    quat.i = -i;
    quat.j = -j;
    quat.k = -k;
    return quat;
}

mx::Quaternion mx::Quaternion::inverse() const 
{
    float norm          = this->norm();
    mx::Quaternion conj = this->conjugate();
    return conj * norm;
}

// see http://www.songho.ca/opengl/gl_quaternion.html
mx::mat4 mx::Quaternion::toMat4() const
{
    mx::mat4 res;
    float twoRealSqr = 2.f * real * real;
    float twoiSqr    = 2.f * i * i;
    float twojSqr    = 2.f * j * j;
    float twokSqr    = 2.f * k * k;
    
    float twori = 2.f * real * i;
    float tworj = 2.f * real * j;
    float twork = 2.f * real * k;
    float twoij = 2.f * i * j;
    float twoik = 2.f * i * k;
    float twojk = 2.f * j * k;

    res.setData({
        1.f - twojSqr - twokSqr,           twoij - twork,           twoik + tworj, 0.f,
                  twoij + twork, 1.f - twoiSqr - twokSqr,           twojk - twori, 0.f,
                  twoik - tworj,           twojk + twori, 1.f - twoiSqr - twojSqr, 0.f,
                            0.f,                     0.f,                     0.f, 1.f
    });

    return res;
}
// @see https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
mx::Quaternion mx::Quaternion::fromEulerAngles(float x, float y, float z)
{
    float cosX = cosf(x * 0.5f);
    float sinX = sinf(x * 0.5f);
    float cosY = cosf(y * 0.5f);
    float sinY = sinf(y * 0.5f);
    float cosZ = cosf(z * 0.5f);
    float sinZ = sinf(z * 0.5f);

    mx::Quaternion quat;
    quat.real = cosX * cosY * cosZ + sinX * sinY * sinZ;
    quat.i    = sinX * cosY * cosZ - cosX * sinY * sinZ;
    quat.j    = cosX * sinY * cosZ + sinX * cosY * sinZ;
    quat.k    = cosX * cosY * sinZ - sinX * sinY * cosZ;

    return quat;
}

std::ostream& mx::operator<<(std::ostream& o, const mx::Quaternion& quat)
{
    float re    = quat.Re();
    mx::vec3 im = quat.Im();
    char buf[512];
    std::snprintf(&buf[0], 512, "Quaternion [%+5f %+5fi %+5fj %+5fk]", re, im.x, im.y, im.z);
    o << buf << '\n';
    return o;
}