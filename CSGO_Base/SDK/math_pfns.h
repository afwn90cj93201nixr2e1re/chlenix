#pragma once

#include <math.h>
#include <xmmintrin.h>

__forceinline float FastSqrt( float x )
{
	__m128 root = _mm_sqrt_ss( _mm_load_ss( &x ) );
	return *( reinterpret_cast<float *>( &root ) );
}

__forceinline float FastRSqrtFast( float x )
{
	// use intrinsics
	__m128 rroot = _mm_rsqrt_ss( _mm_load_ss( &x ) );
	return *( reinterpret_cast<float *>( &rroot ) );
}