#ifndef _MXPHSX_TYPES_H_
#define _MXPHSX_TYPES_H_

#include "math.h"

namespace mx
{

struct Rect {
    mx::vec2 pos;
    mx::vec2 size;
};

struct Transform {
    mx::vec2 size;
    float rot;
};

} // namespace mx


#endif //_MXPHSX_TYPES_H_