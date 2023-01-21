#ifndef _MX_SHAPE_H_
#define _MX_SHAPE_H_

#include "../core/types.hpp"
#include "renderAttributeTypes.hpp"
#include <vector>

namespace mx
{

class Shader;

class Shape {
public:
    virtual ~Shape() = default;

    virtual void draw(Shader* shader) = 0;

    void bind();
    void unbind();

    u32 getAttributeCount() const;

    u32 getRendererID() const;

protected:
    Shape();

    void internalDestroy();

    u32 attributeCount;
    u32 rendererID;
    void setAttributes(std::vector<AttributeType> attributes, u32 vertexDataSize);
};

} // namespace mx


#endif //_MX_SHAPE_H_