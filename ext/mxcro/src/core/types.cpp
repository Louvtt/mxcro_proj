#include "mx/core/types.hpp"

constexpr float inv_255 = 1.f / 255.f;
mx::Color::Color(float _r, float _g, float _b, float _a)
: r(_r), g(_g), b(_b), a(_a) {}
mx::Color::Color(int _r, int _g, int _b, float _a)
: a(_a), r((float)_r * inv_255), g((float)_g * inv_255), b((float)_b * inv_255)
{}