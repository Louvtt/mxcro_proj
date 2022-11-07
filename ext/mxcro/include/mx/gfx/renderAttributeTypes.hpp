#ifndef _MX_RENDERATTRIBUTES_TYPES_H_
#define _MX_RENDERATTRIBUTES_TYPES_H_

namespace mx
{

/**
 * @brief Type of attributes supported in the renderers
 */
enum class AttributeType
{
    // float
    Float,
    // float[2] or mx::vec2
    Float2,
    // float[3] or mx::vec3
    Float3,
    // float[4] or mx::Color
    Float4,
    // int
    Int,
    // float[4][4] or float[16] or mx::mat4
    Mat4,
    
    RGBA  = Float4,
    Pos2D = Float2,
    Pos3D = Float3, 
    TexCoords2D = Float2
};

/**
 * @brief Get the Size of an attribute in bytes
 * @param type attribute type
 * @return int the size in bytes
 */
int getAttributeTypeSize(AttributeType type);
/**
 * @brief Get the count of elements in an attribute type. Ex: Float4 gives 4
 * @param type attribute type
 * @return int the count of elements
 */
int getAttributeTypeCount(AttributeType type);

} // namespace mx

#endif //_MX_RENDERATTRIBUTES_TYPES_H_