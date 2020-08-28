/* -----------------------------------------------------------------------------

	Copyright (c) 2006 Simon Brown                          si@sjbrown.co.uk

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the 
	"Software"), to	deal in the Software without restriction, including
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
   
#ifndef NV_SQUISH_SIMD_H
#define NV_SQUISH_SIMD_H

#include <simd/simd.h>
#include <cassert>
#include "maths.h"

#ifdef __GNUC__
#	define SQUISH_ALIGN_16 __attribute__ ((__aligned__ (16)))
#else
#	define SQUISH_ALIGN_16 __declspec(align(16))
#endif

#define SQUISH_SSE_SPLAT( a )										\
	( ( a ) | ( ( a ) << 2 ) | ( ( a ) << 4 ) | ( ( a ) << 6 ) )

namespace nvsquish {

#define VEC4_CONST( X ) simd::make_float4( X )

	typedef simd::float4 Vec4;
	//! Returns a*b + c
    inline Vec4 MultiplyAdd( Vec4 const & a, Vec4 const & b, Vec4 const & c )
	{
		return a*b + c;
	}

	//! Returns -( a*b - c )
    inline Vec4 NegativeMultiplySubtract( Vec4 const & a, Vec4 const & b, Vec4 const & c )
	{
		return  -( a * b - c );
	}

    inline Vec4 Reciprocal( Vec4 const &  v )
	{
		// get the reciprocal estimate
		simd::float4 estimate = 1 / v ;

		// one round of Newton-Rhaphson refinement
		simd::float4 diff = simd_make_float4( 1.0f ) - estimate * v;
		return diff * estimate + estimate;
	}

	inline Vec4 Truncate( Vec4 const & v )
	{
        return simd::trunc(v);
	}

	inline bool CompareAnyLessThan( Vec4 const & left, Vec4 const & right )
	{
		simd::int4 bits = left < right;
		return simd::any( bits );
	}

} // namespace squish

#endif // ndef SQUISH_SIMD_SSE_H
