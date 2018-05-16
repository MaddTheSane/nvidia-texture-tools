// This code is in the public domain -- Ignacio Castaño <castano@gmail.com>

#pragma once
#ifndef NV_MATH_PLANE_INL
#define NV_MATH_PLANE_INL

#include "Plane.h"

namespace nv
{
    inline Plane::Plane() {}
    inline Plane::Plane(float x, float y, float z, float w) : v(simd::make_float4(x, y, z, w)) {}
    inline Plane::Plane(const simd::float4 & v) : v(v) {}
    inline Plane::Plane(const simd::float3 & v, float d) : v(simd::make_float4(v, d)) {}
    inline Plane::Plane(const simd::float3 & normal, const simd::float3 & point) : v(simd::make_float4(normal, -simd::dot(normal, point))) {}
    inline Plane::Plane(const simd::float3 & v0, const simd::float3 & v1, const simd::float3 & v2) {
        simd::float3 n = simd::cross(v1-v0, v2-v0);
        float d = -simd::dot(n, v0);
        v = simd::make_float4(n, d);
    }

    inline const Plane & Plane::operator=(const Plane & p) { v = p.v; return *this; }

    inline simd::float3 Plane::vector() const { return v.xyz; }
    inline float Plane::offset() const { return v.w; }
	inline simd::float3 Plane::normal() const { return simd::normalize(vector()); }

    // Normalize plane.
    inline Plane normalize(const Plane & plane, float epsilon = NV_EPSILON)
    {
        const float len = simd::length(plane.vector());
        const float inv = isZero(len, epsilon) ? 0 : 1.0f / len;
        return Plane(plane.v * inv);
    }

    // Get the signed distance from the given point to this plane.
    inline float distance(const Plane & plane, const simd::float3 & point)
    {
        return simd::dot(plane.vector(), point) + plane.offset();
    }

    inline void Plane::operator*=(float s)
    {
        v *= s;
    }

} // nv namespace

#endif // NV_MATH_PLANE_H
