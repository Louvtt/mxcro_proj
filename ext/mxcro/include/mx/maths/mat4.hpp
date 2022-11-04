#ifndef _MX_MATHS_MAT4_H_
#define _MX_MATHS_MAT4_H_

#include "calculus.hpp"
#include <array>
#include "vec3.hpp"

namespace mx {

class mat4
{
public:
    // for model mat
    mat4(float identityValue = 1.f);
    // Ortho
    static mat4 ortho(float sizex, float sizey);
    // PERSP
    static mat4 persp(float fov, float aspectRatio, float far, float near);
    // Translation
    static mat4 translation(float x, float y, float z);
    static mat4 translation(vec3 pos);
    // Look at
    static mat4 lookAt(vec3 pos, vec3 target, vec3 up = vec3{0.f, 1.f, 0.f});

    // column major
    std::array<float, 16> data{};
};

std::ostream& operator<<(std::ostream& o, const mat4& m);

} // namespace mx


#endif //_MX_MATHS_MAT4_H_