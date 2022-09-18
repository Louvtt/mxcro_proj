#include "mx/renderAttributeTypes.h"

int mx::getAttributeTypeSize(mx::AttributeType type)
{
    switch(type)
    {
        case mx::AttributeType::Int:
        case mx::AttributeType::Float:  return 4;
        case mx::AttributeType::Float2: return 4 * 2;
        case mx::AttributeType::Float3: return 4 * 3;
        case mx::AttributeType::Float4: return 4 * 4;

        case mx::AttributeType::Mat4: return 4 * 4 * 4;
    }
    return 0;
}

int mx::getAttributeTypeCount(mx::AttributeType type)
{
    switch(type)
    {
        case mx::AttributeType::Int:
        case mx::AttributeType::Float:  return 1;
        case mx::AttributeType::Float2: return 2;
        case mx::AttributeType::Float3: return 3;
        case mx::AttributeType::Float4: return 4;

        case mx::AttributeType::Mat4: return 4 * 4;
    }
    return 0;
}