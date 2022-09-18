#ifndef _MX_RENDERATTRIBUTES_TYPES_H_
#define _MX_RENDERATTRIBUTES_TYPES_H_

namespace mx
{

enum class AttributeType
{
    Float,
    Float2,
    Float3,
    Float4,
    Int,
    Mat4,
    
    RGBA  = Float4,
    Pos2D = Float2,
    Pos3D = Float3, 
    TexCoords2D = Float2
};

int getAttributeTypeSize(AttributeType type);
int getAttributeTypeCount(AttributeType type);

} // namespace mx

#endif //_MX_RENDERATTRIBUTES_TYPES_H_