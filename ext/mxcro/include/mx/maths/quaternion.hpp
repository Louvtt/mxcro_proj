#ifndef _MX_MATHS_QUATERNION_H_
#define _MX_MATHS_QUATERNION_H_

namespace mx
{

class Quaternion {
public:
    Quaternion();
    
private:
    float scalar;
    float i, j, k;
};

} // namespace mx


#endif //_MX_MATHS_QUATERNION_H_