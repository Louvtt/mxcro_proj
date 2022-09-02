#pragma once

#ifndef _PHSX_NARROWPHASE_H_
#define _PHSX_NARROWPHASE_H_

#include "math.h"
#include "colliders.h"
#include <unordered_map>
#include <functional>

namespace mx
{

class Broadphase;
class Rigidbody;

struct Manifold {
    Rigidbody* first;
    Rigidbody* second;
    
    mx::vec2 normal;
    float depth;
};

struct TypePair {
    mx::BaseCollider::Type typeA;
    mx::BaseCollider::Type typeB;
};
bool operator==(const TypePair& a, const TypePair& b);


class Narrowphase
{
public:
    Narrowphase(Broadphase* broadphase);

    void step(float delta);

    

private:
    using ManifoldSolver = std::function<bool(Manifold*)>;
    static std::unordered_map<TypePair, ManifoldSolver> solvers;

    mx::Broadphase* broadphase;

private:
    void computeManifold(Manifold* manifold);

    void positionalCorrection(Manifold manifold);
    void impulseResolution(Manifold manifold);
};

} // namespace phsx

namespace std {
    template <>
    struct hash<::mx::TypePair>
    {
        std::size_t operator()(const ::mx::TypePair& k) const
        {
            return ((int)k.typeA << 4) & (int)k.typeB;
        }
    };

} // namespace std


#endif //_PHSX_NARROWPHASE_H_