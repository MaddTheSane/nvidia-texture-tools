// This code is in the public domain -- castanyo@yahoo.es

#pragma once

#include <NVMath/nvmath.h>
#include <simd/simd.h>

namespace nv
{
    typedef simd::float2 Vector2 __attribute__((deprecated));
    typedef simd::float3 Vector3 __attribute__((deprecated));
    typedef simd::float4 Vector4 __attribute__((deprecated));
} // nv namespace

// If we had these functions, they would be ambiguous, the compiler would not know which one to pick:
//template <typename T> Vector2 to(const T & v) { return Vector2(v.x, v.y); }
//template <typename T> Vector3 to(const T & v) { return Vector3(v.x, v.y, v.z); }
//template <typename T> Vector4 to(const T & v) { return Vector4(v.x, v.y, v.z, v.z); }

// We could use a cast operator so that we could infer the expected type, but that doesn't work the same way in all compilers and produces horrible error messages.

// Instead we simply have explicit casts:
//template <typename T> T to(const nv::Vector2 & v) { NV_COMPILER_CHECK(sizeof(T) == sizeof(nv::Vector2)); return T(v.x, v.y); }
//template <typename T> T to(const nv::Vector3 & v) { NV_COMPILER_CHECK(sizeof(T) == sizeof(nv::Vector3)); return T(v.x, v.y, v.z); }
//template <typename T> T to(const nv::Vector4 & v) { NV_COMPILER_CHECK(sizeof(T) == sizeof(nv::Vector4)); return T(v.x, v.y, v.z, v.w); }
