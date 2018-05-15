// This code is in the public domain -- castanyo@yahoo.es

#pragma once
#ifndef NV_MATH_BOX_INL
#define NV_MATH_BOX_INL

#include "Box.h"
#include "Vector.inl"

#include <float.h> // FLT_MAX

namespace nv
{
    // Default ctor.
    //inline Box::Box() { };

    // Copy ctor.
    //inline Box::Box(const Box & b) : minCorner(b.minCorner), maxCorner(b.maxCorner) { }

    // Init ctor.
    //inline Box::Box(const simd::float3 & mins, const simd::float3 & maxs) : minCorner(mins), maxCorner(maxs) { }

    // Assignment operator.
    inline Box & Box::operator=(const Box & b) { minCorner = b.minCorner; maxCorner = b.maxCorner; return *this; }

    // Clear the bounds.
    inline void Box::clearBounds()
    {
        minCorner = simd::make_float3(FLT_MAX, FLT_MAX, FLT_MAX);
        maxCorner = simd::make_float3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    }

    // min < max
    inline bool Box::isValid() const
    {
        return minCorner.x <= maxCorner.x && minCorner.y <= maxCorner.y && minCorner.z <= maxCorner.z;
    }

    // Build a cube centered on center and with edge = 2*dist
    inline void Box::cube(const simd::float3 & center, float dist)
    {
        setCenterExtents(center, simd::make_float3(dist));
    }

    // Build a box, given center and extents.
    inline void Box::setCenterExtents(const simd::float3 & center, const simd::float3 & extents)
    {
        minCorner = center - extents;
        maxCorner = center + extents;
    }

    // Get box center.
    inline simd::float3 Box::center() const
    {
        return (minCorner + maxCorner) * 0.5f;
    }

    // Return extents of the box.
    inline simd::float3 Box::extents() const
    {
        return (maxCorner - minCorner) * 0.5f;
    }

    // Return extents of the box.
    inline float Box::extents(uint axis) const
    {
        nvDebugCheck(axis < 3);
        if (axis == 0) return (maxCorner.x - minCorner.x) * 0.5f;
        if (axis == 1) return (maxCorner.y - minCorner.y) * 0.5f;
        if (axis == 2) return (maxCorner.z - minCorner.z) * 0.5f;
        nvUnreachable();
        return 0.0f;
    }

    // Add a point to this box.
    inline void Box::addPointToBounds(const simd::float3 & p)
    {
        minCorner = simd::min(minCorner, p);
        maxCorner = simd::max(maxCorner, p);
    }

    // Add a box to this box.
    inline void Box::addBoxToBounds(const Box & b)
    {
        minCorner = simd::min(minCorner, b.minCorner);
        maxCorner = simd::max(maxCorner, b.maxCorner);
    }

    // Add sphere to this box.
    inline void Box::addSphereToBounds(const simd::float3 & p, float r) {
        minCorner = simd::min(minCorner, p - r);
        maxCorner = simd::min(maxCorner, p + r);
    }

    // Translate box.
    inline void Box::translate(const simd::float3 & v)
    {
        minCorner += v;
        maxCorner += v;
    }

    // Scale the box.
    inline void Box::scale(float s)
    {
        minCorner *= s;
        maxCorner *= s;
    }

    // Expand the box by a fixed amount.
    inline void Box::expand(float r) {
        minCorner -= simd::make_float3(r,r,r);
        maxCorner += simd::make_float3(r,r,r);
    }

    // Get the area of the box.
    inline float Box::area() const
    {
        const simd::float3 d = extents();
        return 8.0f * (d.x*d.y + d.x*d.z + d.y*d.z);
    }	

    // Get the volume of the box.
    inline float Box::volume() const
    {
        simd::float3 d = extents();
        return 8.0f * (d.x * d.y * d.z);
    }

    // Return true if the box contains the given point.
    inline bool Box::contains(const simd::float3 & p) const
    {
        return 
            minCorner.x < p.x && minCorner.y < p.y && minCorner.z < p.z &&
            maxCorner.x > p.x && maxCorner.y > p.y && maxCorner.z > p.z;
    }

    // Split the given box in 8 octants and assign the ith one to this box.
    inline void Box::setOctant(const Box & box, const simd::float3 & center, int i)
    {
        minCorner = box.minCorner;
        maxCorner = box.maxCorner;

        if (i & 4) minCorner.x = center.x;
        else       maxCorner.x = center.x;
        if (i & 2) minCorner.y = center.y;
        else       maxCorner.y = center.y;
        if (i & 1) minCorner.z = center.z;
        else       maxCorner.z = center.z;
    }

} // nv namespace


#endif // NV_MATH_BOX_INL
