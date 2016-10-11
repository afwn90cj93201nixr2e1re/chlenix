#pragma once

#include "vector2d.h"

#pragma warning(disable:4244)

// Used to make certain code easier to read.
#define X_INDEX	0
#define Y_INDEX	1
#define Z_INDEX	2

// 3D Vector
class Vector
{
public:
	// Members
	vec_t x , y , z;

	// Construction/destruction:
	Vector( void );
	Vector( vec_t X , vec_t Y , vec_t Z );
	Vector( vec_t* clr );

	// Initialization
	void Init( vec_t ix = 0.0f , vec_t iy = 0.0f , vec_t iz = 0.0f );
	// TODO (Ilya): Should there be an init that takes a single float for consistency?

	// Got any nasty NAN's?
	bool IsValid() const;
	void Invalidate();

	// array access...
	vec_t operator[]( int i ) const;
	vec_t& operator[]( int i );

	// Base address...
	vec_t* Base();
	vec_t const* Base() const;

	// Cast to Vector2D...
	Vector2D& AsVector2D();
	const Vector2D& AsVector2D() const;

	inline void Zero(); ///< zero out a vector

						// equality
	bool operator==( const Vector& v ) const;
	bool operator!=( const Vector& v ) const;

	// arithmetic operations
	FORCEINLINE Vector&	operator+=( const Vector &v );
	FORCEINLINE Vector&	operator-=( const Vector &v );
	FORCEINLINE Vector&	operator*=( const Vector &v );
	FORCEINLINE Vector&	operator*=( float s );
	FORCEINLINE Vector&	operator/=( const Vector &v );
	FORCEINLINE Vector&	operator/=( float s );
	FORCEINLINE Vector&	operator+=( float fl ); ///< broadcast add
	FORCEINLINE Vector&	operator-=( float fl ); ///< broadcast sub			

												// negate the vector components
	void	Negate();

	// Get the vector's magnitude.
	inline vec_t	Length() const;

	// Get the vector's magnitude squared.
	FORCEINLINE vec_t LengthSqr( void ) const
	{
		return ( x*x + y*y + z*z );
	}

	// Get one over the vector's length
	// via fast hardware approximation
	inline vec_t LengthRecipFast( void ) const
	{
		return FastRSqrtFast( LengthSqr() );
	}

	// return true if this vector is (0,0,0) within tolerance
	bool IsZero( float tolerance = 0.01f ) const
	{
		return ( x > -tolerance && x < tolerance &&
				 y > -tolerance && y < tolerance &&
				 z > -tolerance && z < tolerance );
	}

	inline bool IsZeroFast() const
	{
		return ( *reinterpret_cast<const int *>( &x ) == 0 &&
				 *reinterpret_cast<const int *>( &y ) == 0 &&
				 *reinterpret_cast<const int *>( &z ) == 0 );
	}

	vec_t	NormalizeInPlace();
	Vector	Normalized() const;
	bool	IsLengthGreaterThan( float val ) const;
	bool	IsLengthLessThan( float val ) const;

	// check if a vector is within the box defined by two other vectors
	FORCEINLINE bool WithinAABox( Vector const &boxmin , Vector const &boxmax );

	// Get the distance from this vector to the other one.
	vec_t	DistTo( const Vector &vOther ) const;

	// Get the distance from this vector to the other one squared.
	// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' inline.  
	// may be able to tidy this up after switching to VC7
	FORCEINLINE vec_t DistToSqr( const Vector &vOther ) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}

	// Copy
	void	CopyToArray( float* rgfl ) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual vector equation (because it's done per-component
	// rather than per-vector).
	void	MulAdd( const Vector& a , const Vector& b , float scalar );

	// Dot product.
	vec_t	Dot( const Vector& vOther ) const;

	// assignment
	Vector& operator=( const Vector &vOther );

	// returns 0, 1, 2 corresponding to the component with the largest absolute value
	inline int LargestComponent() const;

	// 2d
	vec_t	Length2D( void ) const;
	vec_t	Length2DSqr( void ) const;

	/// get the component of this vector parallel to some other given vector
	inline Vector  ProjectOnto( const Vector& onto );

	// copy constructors

	// arithmetic operations
	Vector	operator-( void ) const;

	Vector	operator+( const Vector& v ) const;
	Vector	operator-( const Vector& v ) const;
	Vector	operator*( const Vector& v ) const;
	Vector	operator/( const Vector& v ) const;
	Vector	operator*( float fl ) const;
	Vector	operator/( float fl ) const;

	// Cross product between two vectors.
	Vector	Cross( const Vector &vOther ) const;

	// Returns a vector with the min or max in X, Y, and Z.
	Vector	Min( const Vector &vOther ) const;
	Vector	Max( const Vector &vOther ) const;
};

class QAngleByValue;

class QAngle
{
public:
	// Members
	vec_t x , y , z;

	// Construction/destruction
	QAngle( void );
	QAngle( vec_t X , vec_t Y , vec_t Z );

	// Allow pass-by-value
	operator QAngleByValue &( ) { return *( (QAngleByValue *)( this ) ); }
	operator const QAngleByValue &( ) const { return *( (const QAngleByValue *)( this ) ); }

	// Initialization
	void Init( vec_t ix = 0.0f , vec_t iy = 0.0f , vec_t iz = 0.0f );

	// Got any nasty NAN's?
	bool IsValid() const;
	void Invalidate();

	// array access...
	vec_t operator[]( int i ) const;
	vec_t& operator[]( int i );

	// Base address...
	vec_t* Base();
	vec_t const* Base() const;

	// equality
	bool operator==( const QAngle& v ) const;
	bool operator!=( const QAngle& v ) const;

	// arithmetic operations
	QAngle&	operator+=( const QAngle &v );
	QAngle&	operator-=( const QAngle &v );
	QAngle&	operator*=( float s );
	QAngle&	operator/=( float s );

	// Get the vector's magnitude.
	vec_t	Length() const;
	vec_t	LengthSqr() const;
};

inline QAngle::QAngle( void )
{
}

inline QAngle::QAngle( vec_t X , vec_t Y , vec_t Z )
{
	x = X; y = Y; z = Z;
}

class QAngleByValue : public QAngle
{
public:
	// Construction/destruction:
	QAngleByValue( void ) : QAngle() { }
	QAngleByValue( vec_t X , vec_t Y , vec_t Z ) : QAngle( X , Y , Z ) { }
	QAngleByValue( const QAngleByValue& vOther ) { *this = vOther; }
};

inline void QAngle::Init( vec_t ix , vec_t iy , vec_t iz )
{
	x = ix; y = iy; z = iz;
}

inline bool QAngle::IsValid() const
{
	bool valid = ( *this != QAngle( 0 , 0 , 0 ) );
	return IsFinite( x ) && IsFinite( y ) && IsFinite( z ) && valid;
}

inline void QAngle::Invalidate()
{
	x = y = z = VEC_T_NAN;
}

inline vec_t QAngle::operator[]( int i ) const
{
	return ( ( vec_t* )this )[i];
}

inline vec_t& QAngle::operator[]( int i )
{
	return ( ( vec_t* )this )[i];
}

inline vec_t* QAngle::Base()
{
	return ( vec_t* )this;
}

inline vec_t const* QAngle::Base() const
{
	return ( vec_t const* )this;
}

inline bool QAngle::operator==( const QAngle& src ) const
{
	return ( src.x == x ) && ( src.y == y ) && ( src.z == z );
}

inline bool QAngle::operator!=( const QAngle& src ) const
{
	return ( src.x != x ) || ( src.y != y ) || ( src.z != z );
}

inline QAngle& QAngle::operator+=( const QAngle& v )
{
	x += v.x; y += v.y; z += v.z;
	return *this;
}

inline QAngle& QAngle::operator-=( const QAngle& v )
{
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

inline QAngle& QAngle::operator*=( float fl )
{
	x *= fl;
	y *= fl;
	z *= fl;
	return *this;
}

inline QAngle& QAngle::operator/=( float fl )
{
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	return *this;
}

inline vec_t QAngle::Length() const
{
	return (vec_t)FastSqrt( LengthSqr() );
}


inline vec_t QAngle::LengthSqr() const
{
	return x * x + y * y + z * z;
}

class TableVector
{
public:
	vec_t x , y , z;

	operator Vector &( ) { return *( (Vector *)( this ) ); }
	operator const Vector &( ) const { return *( (const Vector *)( this ) ); }

	// array access...
	inline vec_t& operator[]( int i )
	{
		return ( ( vec_t* )this )[i];
	}

	inline vec_t operator[]( int i ) const
	{
		return ( ( vec_t* )this )[i];
	}
};

FORCEINLINE void VectorAdd( const Vector& a , const Vector& b , Vector& c )
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

FORCEINLINE void VectorSubtract( const Vector& a , const Vector& b , Vector& c )
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

FORCEINLINE void VectorMultiply( const Vector& a , vec_t b , Vector& c )
{
	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;
}

FORCEINLINE void VectorMultiply( const Vector& a , const Vector& b , Vector& c )
{
	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
}

FORCEINLINE void VectorDivide( const Vector& a , vec_t b , Vector& c )
{
	vec_t oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
	c.z = a.z * oob;
}

FORCEINLINE void VectorDivide( const Vector& a , const Vector& b , Vector& c )
{
	c.x = a.x / b.x;
	c.y = a.y / b.y;
	c.z = a.z / b.z;
}

inline vec_t NormalizeVector( Vector& v )
{
	vec_t l = v.Length();
	if ( l != 0.0f )
	{
		v /= l;
	}
	else
	{
		// FIXME: 
		// Just copying the existing implemenation; shouldn't res.z == 0?
		v.x = v.y = 0.0f; v.z = 1.0f;
	}
	return l;
}

inline void CrossProduct( const Vector& a , const Vector& b , Vector& result )
{
	result.x = a.y*b.z - a.z*b.y;
	result.y = a.z*b.x - a.x*b.z;
	result.z = a.x*b.y - a.y*b.x;
}

inline vec_t VectorLength( const Vector& v )
{
	return (vec_t)FastSqrt( v.x*v.x + v.y*v.y + v.z*v.z );
}

FORCEINLINE vec_t DotProduct( const Vector& a , const Vector& b )
{
	return( a.x*b.x + a.y*b.y + a.z*b.z );
}

inline Vector::Vector( void )
{
}

inline Vector::Vector( vec_t X , vec_t Y , vec_t Z )
{
	x = X; y = Y; z = Z;
}

inline Vector::Vector( vec_t* clr )
{
	x = clr[0]; y = clr[1]; z = clr[2];
}

inline void Vector::Init( vec_t ix , vec_t iy , vec_t iz )
{
	x = ix; y = iy; z = iz;
}

inline bool Vector::IsValid() const
{
	bool valid = ( *this != Vector( 0 , 0 , 0 ) );
	return IsFinite( x ) && IsFinite( y ) && IsFinite( z ) && valid;
}

inline void Vector::Invalidate()
{
	x = y = z = VEC_T_NAN;
}

inline vec_t Vector::operator[]( int i ) const
{
	return ( ( vec_t* )this )[i];
}

inline vec_t& Vector::operator[]( int i )
{
	return ( ( vec_t* )this )[i];
}

inline vec_t* Vector::Base()
{
	return ( vec_t* )this;
}

inline vec_t const* Vector::Base() const
{
	return ( vec_t const* )this;
}

inline Vector2D& Vector::AsVector2D()
{
	return *( Vector2D* )this;
}

inline const Vector2D& Vector::AsVector2D() const
{
	return *( const Vector2D* )this;
}

inline void Vector::Zero()
{
	x = y = z = 0.0f;
}

inline bool Vector::operator==( const Vector& src ) const
{
	return ( src.x == x ) && ( src.y == y ) && ( src.z == z );
}

inline bool Vector::operator!=( const Vector& src ) const
{
	return ( src.x != x ) || ( src.y != y ) || ( src.z != z );
}

FORCEINLINE Vector& Vector::operator+=( const Vector& v )
{
	x += v.x; y += v.y; z += v.z;
	return *this;
}

FORCEINLINE Vector& Vector::operator-=( const Vector& v )
{
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

FORCEINLINE Vector& Vector::operator*=( const Vector& v )
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

FORCEINLINE Vector& Vector::operator*=( float fl )
{
	x *= fl;
	y *= fl;
	z *= fl;
	return *this;
}

FORCEINLINE Vector& Vector::operator/=( const Vector& v )
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

FORCEINLINE Vector& Vector::operator/=( float fl )
{
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	return *this;
}

FORCEINLINE Vector&	Vector::operator+=( float fl )
{
	x += fl;
	y += fl;
	z += fl;
	return *this;
}

FORCEINLINE Vector&	Vector::operator-=( float fl )
{
	x -= fl;
	y -= fl;
	z -= fl;
	return *this;
}

inline void Vector::Negate()
{
	x = -x; y = -y; z = -z;
}

inline vec_t Vector::Length( void ) const
{
	return VectorLength( *this );
}

inline vec_t Vector::NormalizeInPlace()
{
	return NormalizeVector( *this );
}

inline Vector Vector::Normalized() const
{
	Vector norm = *this;
	NormalizeVector( norm );
	return norm;
}

inline bool Vector::IsLengthGreaterThan( float val ) const
{
	return LengthSqr() > val*val;
}

inline bool Vector::IsLengthLessThan( float val ) const
{
	return LengthSqr() < val*val;
}

bool Vector::WithinAABox( Vector const &boxmin , Vector const &boxmax )
{
	return (
		( x >= boxmin.x ) && ( x <= boxmax.x ) &&
		( y >= boxmin.y ) && ( y <= boxmax.y ) &&
		( z >= boxmin.z ) && ( z <= boxmax.z )
		);
}

inline vec_t Vector::DistTo( const Vector &vOther ) const
{
	Vector delta;
	VectorSubtract( *this , vOther , delta );
	return delta.Length();
}

inline void	Vector::CopyToArray( float* rgfl ) const
{
	rgfl[0] = x , rgfl[1] = y , rgfl[2] = z;
}

inline void	Vector::MulAdd( const Vector& a , const Vector& b , float scalar )
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
	z = a.z + b.z * scalar;
}

inline vec_t Vector::Dot( const Vector& vOther ) const
{
	return DotProduct( *this , vOther );
}

inline Vector& Vector::operator=( const Vector &vOther )
{
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}

inline int Vector::LargestComponent() const
{
	float flAbsx = fabs( x );
	float flAbsy = fabs( y );
	float flAbsz = fabs( z );
	if ( flAbsx > flAbsy )
	{
		if ( flAbsx > flAbsz )
			return X_INDEX;
		return Z_INDEX;
	}
	if ( flAbsy > flAbsz )
		return Y_INDEX;
	return Z_INDEX;
}

inline vec_t Vector::Length2D( void ) const
{
	return (vec_t)FastSqrt( x*x + y*y );
}

inline vec_t Vector::Length2DSqr( void ) const
{
	return ( x*x + y*y );
}

inline Vector Vector::ProjectOnto( const Vector& onto )
{
	return onto * ( this->Dot( onto ) / ( onto.LengthSqr() ) );
}

inline Vector Vector::operator-( void ) const
{
	return Vector( -x , -y , -z );
}

inline Vector Vector::operator+( const Vector& v ) const
{
	Vector res;
	VectorAdd( *this , v , res );
	return res;
}

inline Vector Vector::operator-( const Vector& v ) const
{
	Vector res;
	VectorSubtract( *this , v , res );
	return res;
}

inline Vector Vector::operator*( const Vector& v ) const
{
	Vector res;
	VectorMultiply( *this , v , res );
	return res;
}

inline Vector Vector::operator/( const Vector& v ) const
{
	Vector res;
	VectorDivide( *this , v , res );
	return res;
}

inline Vector Vector::operator*( float fl ) const
{
	Vector res;
	VectorMultiply( *this , fl , res );
	return res;
}

inline Vector Vector::operator/( float fl ) const
{
	Vector res;
	VectorDivide( *this , fl , res );
	return res;
}

inline Vector Vector::Cross( const Vector& vOther ) const
{
	Vector res;
	CrossProduct( *this , vOther , res );
	return res;
}

inline Vector Vector::Min( const Vector &vOther ) const
{
	return Vector( x < vOther.x ? x : vOther.x ,
				   y < vOther.y ? y : vOther.y ,
				   z < vOther.z ? z : vOther.z );
}

inline Vector Vector::Max( const Vector &vOther ) const
{
	return Vector( x > vOther.x ? x : vOther.x ,
				   y > vOther.y ? y : vOther.y ,
				   z > vOther.z ? z : vOther.z );
}