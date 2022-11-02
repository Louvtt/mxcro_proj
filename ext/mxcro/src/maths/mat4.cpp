#include "mx/maths/mat4.hpp"

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
mx::mat4 mx::mat4::persp(float _fov, float _aspect, float _far, float _near)
{
    mx::mat4 proj = mx::mat4(); // identity
    float tangent = tanf(mx::degreesToRadians(_fov * .5f));
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

// see https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/gluLookAt.xml
mx::mat4 mx::mat4::lookAt(vec3 _pos, vec3 _target, vec3 _up)
{
    mx::vec3 up = _up.normalized();
    mx::vec3 f = (_target - _pos).normalized();
    mx::vec3 s = f * up;
    mx::vec3 u = f * s.normalized();

    mx::mat4 res = mat4();
    // s
    res.data[IX(0, 0)] = s.x;
    res.data[IX(0, 1)] = s.y;
    res.data[IX(0, 2)] = s.z;
    // u
    res.data[IX(1, 0)] = u.x;
    res.data[IX(1, 1)] = u.y;
    res.data[IX(1, 2)] = u.z;
    // f
    res.data[IX(2, 0)] = -f.x;
    res.data[IX(2, 1)] = -f.y;
    res.data[IX(2, 2)] = -f.z;

    return res;
}