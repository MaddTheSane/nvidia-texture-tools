// This code is in the public domain -- castanyo@yahoo.es

#pragma once
#ifndef NV_MATH_BOX_H
#define NV_MATH_BOX_H

#include <NVMath/Vector.h>

#include <float.h> // FLT_MAX

namespace nv
{
    class Stream;
    class Sphere;

    // Axis Aligned Bounding Box.
    class Box
    {
    public:

        inline Box() {}
        inline Box(const Box & b) : minCorner(b.minCorner), maxCorner(b.maxCorner) {}
        inline Box(const simd::float3 & mins, const simd::float3 & maxs) : minCorner(mins), maxCorner(maxs) {}

        Box & operator=(const Box & b);

        operator const float * () const { return reinterpret_cast<const float *>(this); }

        // Clear the bounds.
        void clearBounds();

        // min < max
        bool isValid() const;

        // Build a cube centered on center and with edge = 2*dist
        void cube(const simd::float3 & center, float dist);

        // Build a box, given center and extents.
        void setCenterExtents(const simd::float3 & center, const simd::float3 & extents);

        // Get box center.
        simd::float3 center() const;

        // Return extents of the box.
        simd::float3 extents() const;

        // Return extents of the box.
        float extents(uint axis) const;

        // Add a point to this box.
        void addPointToBounds(const simd::float3 & p);

        // Add a box to this box.
        void addBoxToBounds(const Box & b);

        // Add sphere to this box.
        void addSphereToBounds(const simd::float3 & p, float r);

        // Translate box.
        void translate(const simd::float3 & v);

        // Scale the box.
        void scale(float s);

        // Expand the box by a fixed amount.
        void expand(float r);

        // Get the area of the box.
        float area() const;
 
        // Get the volume of the box.
        float volume() const;

        // Return true if the box contains the given point.
        bool contains(const simd::float3 & p) const;

        // Split the given box in 8 octants and assign the ith one to this box.
        void setOctant(const Box & box, const simd::float3 & center, int i);


        // Clip the given segment against this box.
        bool clipSegment(const simd::float3 & origin, const simd::float3 & dir, float * t_near, float * t_far) const;


        friend Stream & operator<< (Stream & s, Box & box);

        const simd::float3 & corner(int i) const { return (&minCorner)[i]; }

        simd::float3 minCorner;
        simd::float3 maxCorner;
    };

    float distanceSquared(const Box &box, const simd::float3 &point);
    bool overlap(const Box &box, const Sphere &sphere);

    // p is ray origin, id is inverse ray direction.
    bool intersect(const Box & box, const simd::float3 & p, const simd::float3 & id, float * t);

} // nv namespace


#endif // NV_MATH_BOX_H
