// This code is in the public domain -- Ignacio Castaño <castano@gmail.com>

#pragma once

#include <NVMath/nvmath.h>
#include <simd/simd.h>

namespace nv
{
    class Matrix;

    class Plane
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
        simd::float3 normal() const;

        void operator*=(float s);

        simd::float4 v;
    };

    Plane transformPlane(const Matrix &, const Plane &);

    simd::float3 planeIntersection(const Plane & a, const Plane & b, const Plane & c);


} // nv namespace
