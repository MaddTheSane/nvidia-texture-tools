/* -----------------------------------------------------------------------------
 
 Copyright (c) 2018 C.W. Betts                           computers57@hotmail.com
 
 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to    deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:
 
 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 -------------------------------------------------------------------------- */

#ifndef SimdVector_libsimd_h
#define SimdVector_libsimd_h

#include "nvcore/Memory.h"
#include <simd/simd.h>


namespace nv {

#define NV_SIMD_NATIVE NV_FORCEINLINE
#define NV_SIMD_INLINE inline

    class SimdVector
    {
    public:
        simd::float4 vec;

        typedef SimdVector const& Arg;

        NV_SIMD_NATIVE SimdVector() {}

        NV_SIMD_NATIVE explicit SimdVector(simd::float4 v) : vec(v) {}

        NV_SIMD_NATIVE explicit SimdVector(float f) {
            vec = simd::make_float4(f);
        }

        NV_SIMD_NATIVE explicit SimdVector(const float * v)
        {
            vec = simd::make_float4( v );
        }

        NV_SIMD_NATIVE SimdVector(float x, float y, float z, float w)
        {
            vec = simd::make_float4( x, y, z, w );
        }

        NV_SIMD_NATIVE SimdVector(const SimdVector & arg) : vec(arg.vec) {}

        NV_SIMD_NATIVE SimdVector & operator=(const SimdVector & arg)
        {
            vec = arg.vec;
            return *this;
        }

        NV_SIMD_INLINE float toFloat() const
        {
            float f = vec[0];
            return f;
        }

        NV_SIMD_INLINE Vector3 toVector3() const
        {
            return Vector3( vec[0], vec[1], vec[2] );
        }

        NV_SIMD_INLINE Vector4 toVector4() const
        {
            return Vector4( vec[0], vec[1], vec[2], vec[3] );
        }

        //TODO: is this what splatting is?
        NV_SIMD_NATIVE SimdVector splatX() const { return SimdVector( simd::make_float4( vec.x, vec.x, vec.x, vec.x ) ); }
        NV_SIMD_NATIVE SimdVector splatY() const { return SimdVector( simd::make_float4( vec.y, vec.y, vec.y, vec.y ) ); }
        NV_SIMD_NATIVE SimdVector splatZ() const { return SimdVector( simd::make_float4( vec.z, vec.z, vec.z, vec.z ) ); }
        NV_SIMD_NATIVE SimdVector splatW() const { return SimdVector( simd::make_float4( vec.w, vec.w, vec.w, vec.w ) ); }

        NV_SIMD_NATIVE SimdVector& operator+=( Arg v )
        {
            vec += v.vec;
            return *this;
        }

        NV_SIMD_NATIVE SimdVector& operator-=( Arg v )
        {
            vec -= v.vec;
            return *this;
        }

        NV_SIMD_NATIVE SimdVector& operator*=( Arg v )
        {
            vec *= v.vec;
            return *this;
        }
    };


    NV_SIMD_NATIVE SimdVector operator+( SimdVector::Arg left, SimdVector::Arg right  )
    {
        return SimdVector( left.vec + right.vec );
    }

    NV_SIMD_NATIVE SimdVector operator-( SimdVector::Arg left, SimdVector::Arg right  )
    {
        return SimdVector( left.vec - right.vec );
    }

    NV_SIMD_NATIVE SimdVector operator*( SimdVector::Arg left, SimdVector::Arg right  )
    {
        return SimdVector( left.vec * right.vec );
    }

    // Returns a*b + c
    NV_SIMD_INLINE SimdVector multiplyAdd( SimdVector::Arg a, SimdVector::Arg b, SimdVector::Arg c )
    {
        return SimdVector( a.vec * b.vec + c.vec );
    }

    // Returns -( a*b - c )
    NV_SIMD_INLINE SimdVector negativeMultiplySubtract( SimdVector::Arg a, SimdVector::Arg b, SimdVector::Arg c )
    {
        return SimdVector( -( a.vec * b.vec - c.vec ) );
    }

    NV_SIMD_INLINE SimdVector reciprocal( SimdVector::Arg v )
    {
        return SimdVector( simd::recip(v.vec) );
    }

    NV_SIMD_NATIVE SimdVector min( SimdVector::Arg left, SimdVector::Arg right )
    {
        return SimdVector( simd::min( left.vec, right.vec ) );
    }

    NV_SIMD_NATIVE SimdVector max( SimdVector::Arg left, SimdVector::Arg right )
    {
        return SimdVector( simd::max( left.vec, right.vec ) );
    }

    NV_SIMD_INLINE SimdVector truncate( SimdVector::Arg v )
    {
        return SimdVector( simd::trunc( v ) );
    }

    NV_SIMD_NATIVE SimdVector compareEqual( SimdVector::Arg left, SimdVector::Arg right )
    {
        simd::int4 toRet = left.vec == right.vec;
        
        return SimdVector( simd::make_float4( toRet ) );
    }

    NV_SIMD_INLINE SimdVector select( SimdVector::Arg off, SimdVector::Arg on, SimdVector::Arg bits )
    {
        simd::int4 predicate = simd::make_int4( bits );
        simd::float4 toRet = simd::select( off.vec, on.vec, predicate );
        
        return SimdVector( toRet );
    }

    NV_SIMD_INLINE bool compareAnyLessThan( SimdVector::Arg left, SimdVector::Arg right )
    {
        simd::int4 bits = left.vec < right.vec;
        return simd::any( bits );
    }

} // namespace nv

#endif /* SimdVector_libsimd_h */
