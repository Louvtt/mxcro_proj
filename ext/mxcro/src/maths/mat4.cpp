#include "mx/maths/mat4.hpp"

#include <iostream>

#include <string.h>
////////////////////////////////////////
/// MAT4

#define IX(x, y) (x+y*4)

mx::mat4::mat4(float _identityValue)
{
    memset(&data[0], 0.f, 4*4*sizeof(float));
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
mx::mat4 mx::mat4::persp(float _fov, float _aspect, float _near, float _far)
{
    mx::mat4 proj = mx::mat4(); // identity
    float tangent = tanf(mx::degreesToRadians(_fov * .5f));

    // scales
    proj.data[IX(0, 0)] = 1.f / (_aspect * tangent);
    proj.data[IX(1, 1)] = 1.f / tangent;
    proj.data[IX(2, 2)] = -_far / (_far - _near);
    proj.data[IX(3, 3)] = 0.f;

    // translate
    proj.data[IX(0, 2)] =  0.f;
    proj.data[IX(1, 2)] =  0.f;
    proj.data[IX(3, 2)] = -1.f;
    proj.data[IX(2, 3)] = -(2.f * _far * _near) / (_far - _near);
    proj.data[IX(3, 3)] =  0.f;

    return proj;
}

mx::mat4 mx::mat4::translation(float _x, float _y, float _z)
{
    mx::mat4 mat = mx::mat4();
    mat.data[IX(0, 3)] = _x;
    mat.data[IX(1, 3)] = _y;
    mat.data[IX(2, 3)] = _z;
    return mat;
}
mx::mat4 mx::mat4::translation(vec3 _pos)
{
    mx::mat4 mat = mx::mat4();
    mat.data[IX(0, 3)] = _pos.x;
    mat.data[IX(1, 3)] = _pos.y;
    mat.data[IX(2, 3)] = _pos.z;
    return mat;
}

// see https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function

mx::mat4 mx::mat4::lookAt(vec3 _pos, vec3 _target, vec3 _up)
{
    mx::vec3 upNorm  = _up.normalized();
    mx::vec3 forward = (_pos - _target).normalized();
    mx::vec3 right   = upNorm.cross(forward).normalized();
    mx::vec3 up      = forward.cross(right).normalized();

    mx::mat4 res = mat4();
    // right (row 0)
    res.data[IX(0, 0)] = right.x;
    res.data[IX(0, 1)] = right.y;
    res.data[IX(0, 2)] = right.z;
    // up (row 1)
    res.data[IX(1, 0)] = up.x;
    res.data[IX(1, 1)] = up.y;
    res.data[IX(1, 2)] = up.z;
    // forward (row 2)
    res.data[IX(2, 0)] = forward.x;
    res.data[IX(2, 1)] = forward.y;
    res.data[IX(2, 2)] = forward.z;
    // translation (row 3)
    res.data[IX(0, 3)] = right.dot(-_pos);
    res.data[IX(1, 3)] = up.dot(-_pos);
    res.data[IX(2, 3)] = forward.dot(-_pos);
    res.data[IX(3, 3)] = 1.f;

    return res;
}

std::array<float, 16> mx::mat4::getData() const {
    return data;
}
void mx::mat4::setData(int i, int j, float value) {
    data[IX(i,j)] = value;
}
void mx::mat4::setData(std::array<float, 16> newData) {
    data = newData;
}

std::ostream& mx::operator<<(std::ostream& o, const mat4& m) {
    std::array<float, 16> data = m.getData();
    o << "mat4\n";
    char buf[512];
    snprintf(buf, 512, "[%+5f %+5f %+5f %+5f]\n", data[IX(0, 0)], data[IX(1, 0)], data[IX(2, 0)], data[IX(3, 0)]);
    o << buf;
    snprintf(buf, 512, "[%+5f %+5f %+5f %+5f]\n", data[IX(0, 1)], data[IX(1, 1)], data[IX(2, 1)], data[IX(3, 1)]);
    o << buf;
    snprintf(buf, 512, "[%+5f %+5f %+5f %+5f]\n", data[IX(0, 2)], data[IX(1, 2)], data[IX(2, 2)], data[IX(3, 2)]);
    o << buf;
    snprintf(buf, 512, "[%+5f %+5f %+5f %+5f]\n", data[IX(0, 3)], data[IX(1, 3)], data[IX(2, 3)], data[IX(3, 3)]);
    o << buf << '\n';
    return o;
}