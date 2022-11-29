#ifndef _MX_MATHS_MAT4_H_
#define _MX_MATHS_MAT4_H_

#include "calculus.hpp"
#include <array>
#include "vec3.hpp"

namespace mx {

/**
 * @brief Represent a 4x4 matrix
 */
class mat4
{
public:
    /**
     * @brief Construct a 4x4 identity matrix 
     * @param identityValue value of the diagonal
     */
    mat4(float identityValue = 1.f);
    /**
     * @brief Create a 4x4 orthogonal projection matrix
     * @param sizex Size x
     * @param sizey Size y
     * @return mat4 - the orthogonal projection matrix
     */
    static mat4 ortho(float sizex, float sizey);
    /**
     * @brief Create a 4x4 perspective projection matrix
     * @param fov Field Of View (in degrees)
     * @param aspectRatio Aspect Ratio (Width/Height)
     * @param far Far plane
     * @param near Near Plane
     * @return mat4 - the perspective projection matrix
     */
    static mat4 persp(float fov, float aspectRatio, float far = .01f, float near = 100.f);
    // Translation
    /**
     * @brief Return a 4x4 translation matrix
     * @param x translation x
     * @param y translation y
     * @param z translation z
     * @return mat4 - the translation matrix
     */
    static mat4 translation(float x, float y, float z);
    /**
     * @brief Return a 4x4 translation matrix
     * 
     * @param pos translation
     * @return mat4 - the translation matrix
     */
    static mat4 translation(vec3 pos);
    // Look at
    /**
     * @brief Create a 4x4 look at matrix
     * @param pos position where the camera is
     * @param target position of the target to look at
     * @param up up direction of the camera
     * @return mat4 - the look at matrix
     */
    static mat4 lookAt(vec3 pos, vec3 target, vec3 up = vec3{0.f, 1.f, 0.f});

    /**
     * @brief Get the matrix data
     * @return std::array<float, 16> - the matrix data
     */
    std::array<float, 16> getData() const;
    /**
     * @brief Get the matrix data ptr
     * @return float* - the data ptr
     */
    float* getDataPtr() const;
    /**
     * @brief Set a value in the matrix
     * @param i column index
     * @param j row index
     * @param value value
     */
    void setData(int i, int j, float value);
    /**
     * @brief Set the data of the matrix
     * @param newData new data of the matrix
     */
    void setData(std::array<float, 16> newData);

    // Operators

    bool operator==(const mat4& other);
    mx::mat4 operator*(const mat4& other);

private:
    // column major
    std::array<float, 16> data{};
};

std::ostream& operator<<(std::ostream& o, const mat4& m);

} // namespace mx


#endif //_MX_MATHS_MAT4_H_