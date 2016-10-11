#pragma once

#include "types.h"
#include "math_pfns.h"

class Vector2D
{
public:
	// Members
	vec_t x , y;

	// Construction/destruction
	Vector2D( void );
	Vector2D( vec_t X , vec_t Y );
	Vector2D( const float *pFloat );

	// Initialization
	void Init( vec_t ix = 0.0f , vec_t iy = 0.0f );

	// Got any nasty NAN's?
	bool IsValid() const;

	// array access...
	vec_t operator[]( int i ) const;
	vec_t& operator[]( int i );

	// Base address...
	vec_t* Base();
	vec_t const* Base() const;

	// equality
	bool operator==( const Vector2D& v ) const;
	bool operator!=( const Vector2D& v ) const;

	// arithmetic operations
	Vector2D&	operator+=( const Vector2D &v );
	Vector2D&	operator-=( const Vector2D &v );
	Vector2D&	operator*=( const Vector2D &v );
	Vector2D&	operator*=( float s );
	Vector2D&	operator/=( const Vector2D &v );
	Vector2D&	operator/=( float s );

	// negate the Vector2D components
	void	Negate();

	// Get the Vector2D's magnitude.
	vec_t	Length() const;

	// Get the Vector2D's magnitude squared.
	vec_t	LengthSqr( void ) const;

	// return true if this vector is (0,0) within tolerance
	bool IsZero( float tolerance = 0.01f ) const
	{
		return ( x > -tolerance && x < tolerance &&
				 y > -tolerance && y < tolerance );
	}

	// Normalize in place and return the old length.
	vec_t	NormalizeInPlace();

	// Compare length.
	bool	IsLengthGreaterThan( float val ) const;
	bool	IsLengthLessThan( float val ) const;

	// Get the distance from this Vector2D to the other one.
	vec_t	DistTo( const Vector2D &vOther ) const;

	// Get the distance from this Vector2D to the other one squared.
	vec_t	DistToSqr( const Vector2D &vOther ) const;

	// Copy
	void	CopyToArray( float* rgfl ) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual Vector2D equation (because it's done per-component
	// rather than per-Vector2D).
	void	MulAdd( const Vector2D& a , const Vector2D& b , float scalar );

	// Dot product.
	vec_t	Dot( const Vector2D& vOther ) const;

	// assignment
	Vector2D& operator=( const Vector2D &vOther );

	// copy constructors
	Vector2D( const Vector2D &vOther );

	// arithmetic operations
	Vector2D	operator-( void ) const;

	Vector2D	operator+( const Vector2D& v ) const;
	Vector2D	operator-( const Vector2D& v ) const;
	Vector2D	operator*( const Vector2D& v ) const;
	Vector2D	operator/( const Vector2D& v ) const;
	Vector2D	operator*( float fl ) const;
	Vector2D	operator/( float fl ) const;

	// Returns a Vector2D with the min or max in X, Y, and Z.
	Vector2D	Min( const Vector2D &vOther ) const;
	Vector2D	Max( const Vector2D &vOther ) const;
};

inline void Vector2DAdd( const Vector2D& a , const Vector2D& b , Vector2D& c )
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

inline void Vector2DSubtract( const Vector2D& a , const Vector2D& b , Vector2D& c )
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

inline void Vector2DMultiply( const Vector2D& a , vec_t b , Vector2D& c )
{
	c.x = a.x * b;
	c.y = a.y * b;
}

inline void Vector2DMultiply( const Vector2D& a , const Vector2D& b , Vector2D& c )
{
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}

inline void Vector2DDivide( const Vector2D& a , vec_t b , Vector2D& c )
{
	vec_t oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

inline void Vector2DDivide( const Vector2D& a , const Vector2D& b , Vector2D& c )
{
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

inline vec_t Vector2DNormalize( Vector2D& v )
{
	vec_t l = v.Length();
	if ( l != 0.0f )
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f;
	}
	return l;
}

inline vec_t Vector2DLength( const Vector2D& v )
{
	return (vec_t)FastSqrt( v.x*v.x + v.y*v.y );
}

inline vec_t DotProduct2D( const Vector2D& a , const Vector2D& b )
{
	return( a.x*b.x + a.y*b.y );
}

inline Vector2D::Vector2D( void )
{
}

inline Vector2D::Vector2D( vec_t X , vec_t Y )
{
	x = X; y = Y;
}

inline Vector2D::Vector2D( const float *pFloat )
{
	x = pFloat[0]; y = pFloat[1];
}

inline void Vector2D::Init( vec_t ix , vec_t iy )
{
	x = ix; y = iy;
}

inline bool Vector2D::IsValid() const
{
	bool valid = ( *this != Vector2D( 0 , 0 ) );
	return IsFinite( x ) && IsFinite( y ) && valid;
}

inline vec_t Vector2D::operator[]( int i ) const
{
	return ( ( vec_t* )this )[i];
}

inline vec_t& Vector2D::operator[]( int i )
{
	return ( ( vec_t* )this )[i];
}

inline vec_t* Vector2D::Base()
{
	return ( vec_t* )this;
}

inline vec_t const* Vector2D::Base() const
{
	return ( vec_t const* )this;
}

inline bool Vector2D::operator==( const Vector2D& src ) const
{
	return ( src.x == x ) && ( src.y == y );
}

inline bool Vector2D::operator!=( const Vector2D& src ) const
{
	return ( src.x != x ) || ( src.y != y );
}

inline Vector2D& Vector2D::operator+=( const Vector2D& v )
{
	x += v.x; y += v.y;
	return *this;
}

inline Vector2D& Vector2D::operator-=( const Vector2D& v )
{
	x -= v.x; y -= v.y;
	return *this;
}

inline void Vector2D::Negate()
{
	x = -x; y = -y;
}

inline vec_t Vector2D::Length( void ) const
{
	return Vector2DLength( *this );
}

inline vec_t Vector2D::LengthSqr( void ) const
{
	return ( x*x + y*y );
}

inline Vector2D& Vector2D::operator*=( const Vector2D& v )
{
	x *= v.x;
	y *= v.y;
	return *this;
}

inline Vector2D& Vector2D::operator*=( float fl )
{
	x *= fl;
	y *= fl;
	return *this;
}

inline Vector2D& Vector2D::operator/=( const Vector2D& v )
{
	x /= v.x;
	y /= v.y;
	return *this;
}

inline Vector2D& Vector2D::operator/=( float fl )
{
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	return *this;
}

inline vec_t Vector2D::NormalizeInPlace()
{
	return Vector2DNormalize( *this );
}

inline bool Vector2D::IsLengthGreaterThan( float val ) const
{
	return LengthSqr() > val*val;
}

inline bool Vector2D::IsLengthLessThan( float val ) const
{
	return LengthSqr() < val*val;
}

inline vec_t Vector2D::DistTo( const Vector2D &vOther ) const
{
	Vector2D delta;
	Vector2DSubtract( *this , vOther , delta );
	return delta.Length();
}

inline vec_t Vector2D::DistToSqr( const Vector2D &vOther ) const
{
	Vector2D delta;
	Vector2DSubtract( *this , vOther , delta );
	return delta.LengthSqr();
}

inline void	Vector2D::CopyToArray( float* rgfl ) const
{
	rgfl[0] = x; rgfl[1] = y;
}

inline void	Vector2D::MulAdd( const Vector2D& a , const Vector2D& b , float scalar )
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

inline Vector2D& Vector2D::operator=( const Vector2D &vOther )
{
	x = vOther.x; y = vOther.y;
	return *this;
}

inline vec_t Vector2D::Dot( const Vector2D& vOther ) const
{
	return DotProduct2D( *this , vOther );
}

inline Vector2D::Vector2D( const Vector2D &vOther )
{
	x = vOther.x; y = vOther.y;
}

inline Vector2D Vector2D::operator-( void ) const
{
	return Vector2D( -x , -y );
}

inline Vector2D Vector2D::operator+( const Vector2D& v ) const
{
	Vector2D res;
	Vector2DAdd( *this , v , res );
	return res;
}

inline Vector2D Vector2D::operator-( const Vector2D& v ) const
{
	Vector2D res;
	Vector2DSubtract( *this , v , res );
	return res;
}

inline Vector2D Vector2D::operator*( const Vector2D& v ) const
{
	Vector2D res;
	Vector2DMultiply( *this , v , res );
	return res;
}

inline Vector2D Vector2D::operator/( const Vector2D& v ) const
{
	Vector2D res;
	Vector2DDivide( *this , v , res );
	return res;
}

inline Vector2D Vector2D::operator*( float fl ) const
{
	Vector2D res;
	Vector2DMultiply( *this , fl , res );
	return res;
}

inline Vector2D Vector2D::operator/( float fl ) const
{
	Vector2D res;
	Vector2DDivide( *this , fl , res );
	return res;
}

inline Vector2D Vector2D::Min( const Vector2D &vOther ) const
{
	return Vector2D( x < vOther.x ? x : vOther.x ,
					 y < vOther.y ? y : vOther.y );
}

inline Vector2D Vector2D::Max( const Vector2D &vOther ) const
{
	return Vector2D( x > vOther.x ? x : vOther.x ,
					 y > vOther.y ? y : vOther.y );
}