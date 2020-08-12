// This code is in the public domain -- castanyo@yahoo.es

#pragma once

#include "Vector.h"
#include "nvmath.h"

#include "nvcore/Utils.h" // min, max
#include "nvcore/Hash.h" // hash

//Kept for legacy reasons.

namespace nv
{
    inline simd::float2 lerp(const simd::float2 & v1, const simd::float2 & v2, float t)
    {
        const float s = 1.0f - t;
        simd::float2 sV = v1 * s;
        simd::float2 tV = t * v2;
        return sV + tV;
    }
	
    inline simd::float2 normalizeSafe(const simd::float2 & v, const simd::float2 & fallback, float epsilon = NV_EPSILON)
    {
        float l = simd::length(v);
        if (isZero(l, epsilon)) {
            return fallback;
        }
        return simd::normalize(v);
    }
	
    inline simd::float2 clamp(const simd::float2 & v, float min, float max)
    {
        return simd::make_float2(clamp(v.x, min, max), clamp(v.y, min, max));
    }

    inline simd::float2 saturate(const simd::float2 & v)
    {
        return simd::make_float2(saturate(v.x), saturate(v.y));
    }

    inline simd::float3 lerp(const simd::float3 & v1, const simd::float3 & v2, float t)
    {
        const float s = 1.0f - t;
        simd::float3 sV = v1 * s;
        simd::float3 tV = t * v2;
        return sV + tV;
    }

    inline simd::float3 normalizeSafe(const simd::float3 & v, const simd::float3 & fallback, float epsilon = NV_EPSILON)
    {
        float l = simd::length(v);
        if (isZero(l, epsilon)) {
            return fallback;
        }
        return simd::normalize(v);
    }
	
    inline simd::float3 clamp(const simd::float3 & v, float min, float max)
    {
        return simd::make_float3(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max));
    }

    inline simd::float3 saturate(const simd::float3 & v)
    {
        return simd::make_float3(saturate(v.x), saturate(v.y), saturate(v.z));
    }

    inline simd::float4 lerp(const simd::float4 & v1, const simd::float4 & v2, float t)
    {
        const float s = 1.0f - t;
        simd::float4 sV = v1 * s;
        simd::float4 tV = t * v2;
        return sV + tV;
    }

    inline simd::float4 normalizeSafe(const simd::float4 & v, const simd::float4 & fallback, float epsilon = NV_EPSILON)
    {
        float l = simd::length(v);
        if (isZero(l, epsilon)) {
            return fallback;
        }
        return simd::normalize(v);
    }

    inline simd::float4 clamp(const simd::float4 & v, float min, float max)
    {
        return simd::make_float4(clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max), clamp(v.w, min, max));
    }
	
    inline simd::float4 saturate(const simd::float4 & v)
    {
        return simd::make_float4(saturate(v.x), saturate(v.y), saturate(v.z), saturate(v.w));
    }

} // nv namespace
