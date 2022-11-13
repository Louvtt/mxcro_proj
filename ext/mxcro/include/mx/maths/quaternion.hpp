#ifndef _MX_MATHS_QUATERNION_H_
#define _MX_MATHS_QUATERNION_H_

#include "vec3.hpp"
#include "mat4.hpp"

namespace mx
{

/**
 * @brief Represent a Quaternion
 * 
 * @see https://en.wikipedia.org/wiki/Quaternion#Multiplication_of_basis_elements
 */
class Quaternion {
public:
    Quaternion();
    
    Quaternion operator+(const Quaternion& other) const;
    Quaternion operator-(const Quaternion& other) const;
    Quaternion operator*(const Quaternion& other) const;
    Quaternion operator*(float factor) const;
    Quaternion operator/(const Quaternion& other) const;

    bool operator==(const Quaternion& other) const;
    
    float    Re() const;
    mx::vec3 Im() const;
    float norm() const;

    Quaternion conjugate() const;
    Quaternion inverse() const;

    mx::mat4 toMat4() const;

    /**
     * @brief Create a quaternion based on rotation axis angles
     * 
     * @param x roll  (rotation on x axis)
     * @param y pitch (rotation y axis)
     * @param z yaw   (rotation z axis)
     * @return mx::Quaternion 
     */
    static mx::Quaternion fromEulerAngles(float x, float y, float z);
private:
    float real;
    float i, j, k;
};

std::ostream& operator<<(std::ostream& o, const mx::Quaternion& quat);

} // namespace mx


#endif //_MX_MATHS_QUATERNION_H_