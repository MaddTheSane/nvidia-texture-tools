// This code is in the public domain -- Ignacio Castaño <castano@gmail.com>

#pragma once
#ifndef NV_MATH_PLANE_H
#define NV_MATH_PLANE_H

#include "nvmath.h"
#include <simd/simd.h>

#if NV_USE_ALTIVEC
#undef vector
#endif

namespace nv
{
    class Matrix;

    class NVMATH_CLASS Plane
    {
    public:
        Plane();
        Plane(float x, float y, float z, float w);
        Plane(const simd::float4 & v);
        Plane(const simd::float3 & v, float d);
        Plane(const simd::float3 & normal, const simd::float3 & point);
        Plane(const simd::float3 & v0, const simd::float3 & v1, const simd::float3 & v2);

        const Plane & operator=(const Plane & v);

        simd::float3 vector() const;
        float offset() const;

        void operator*=(float s);

        simd::float4 v;
    };

    Plane transformPlane(const Matrix &, const Plane &);

    simd::float3 planeIntersection(const Plane & a, const Plane & b, const Plane & c);


} // nv namespace

#endif // NV_MATH_PLANE_H
