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
   
#ifndef NV_SQUISH_MATHS_H
#define NV_SQUISH_MATHS_H

#if NV_USE_ALTIVEC
#undef vector
#endif

#include <cmath>
#include <algorithm>
#include <simd/simd.h>
#include "config.h"

#if NV_USE_ALTIVEC
#define vector __vector
#endif

namespace nvsquish {

typedef simd::float3 Vec3;

inline float LengthSquared( const Vec3 &v )
{
	return simd::length_squared(v);
}

class Sym3x3
{
public:
	Sym3x3()
	{
	}

	Sym3x3( float a )
	{
		for( int i = 0; i < 6; ++i )
			m_x[i] = a;
	}

	float operator[]( int index ) const
	{
		return m_x[index];
	}

	float& operator[]( int index )
	{
		return m_x[index];
	}

private:
	float m_x[6];
};

Sym3x3 ComputeWeightedCovariance( int n, Vec3 const* points, float const* weights, const Vec3 &metric );
Vec3 ComputePrincipleComponent( Sym3x3 const& matrix );

} // namespace nvsquish

#endif // ndef SQUISH_MATHS_H
