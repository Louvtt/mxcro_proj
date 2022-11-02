#ifndef _MX_TYPES_H_
#define _MX_TYPES_H_

#include <memory>
#include <string>

using u8  = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using i16 = short;
using i32 = int;
using i64 = long long;

using f32 = float;
using f64 = double;

namespace mx {
    struct Color
    { 
        float r, g, b;
        float a;

        Color(float r, float g, float b, float a=1.f);
        Color(int r, int g, int b, float a = 1.f);
    };
}


#endif //_MX_TYPES_H_