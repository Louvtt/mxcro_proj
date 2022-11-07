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
    /**
     * @brief RGBA Color
     */
    struct Color
    { 
        /** color channels */
        float r, g, b;
        /** alpha channel */
        float a;

        /**
         * @brief Construct a new Color
         * 
         * @param red red channel [0-1]
         * @param green green channel [0-1]
         * @param blue blue channel [0-1]
         * @param alpha alpha channel [0-1]
         */
        Color(float red, float green, float blue, float alpha=1.f);
        /**
         * @brief Construct a new Color
         * 
         * @param red red channel [0-255]
         * @param green green channel [0-255]
         * @param blue blue channel [0-255]
         * @param alpha alpha channel [0-1]
         */
        Color(int red, int green, int blue, float alpha = 1.f);
    };
}


#endif //_MX_TYPES_H_