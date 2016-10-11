#pragma once

class Color
{
public:

	Color()
	{
		*((int *)this) = 0;
	}

	Color(int _r,int _g,int _b)
	{
		SetColor(_r, _g, _b, 255);
	}

	Color(int _r,int _g,int _b,int _a)
	{
		SetColor(_r, _g, _b, _a);
	}

	void SetColor(int _r, int _g, int _b, int _a = 0)
	{
		_color[0] = (unsigned char)_r;
		_color[1] = (unsigned char)_g;
		_color[2] = (unsigned char)_b;
		_color[3] = (unsigned char)_a;
	}

	void GetColor(int &_r, int &_g, int &_b, int &_a) const
	{
		_r = _color[0];
		_g = _color[1];
		_b = _color[2];
		_a = _color[3];
	}

	void SetRawColor( int color32 )
	{
		*((int *)this) = color32;
	}

	int GetRawColor() const
	{
		return *((int *)this);
	}

	inline int r() const	{ return _color[0]; }
	inline int g() const	{ return _color[1]; }
	inline int b() const	{ return _color[2]; }
	inline int a() const	{ return _color[3]; }
	
	unsigned char &operator[](int index)
	{
		return _color[index];
	}

	const unsigned char &operator[](int index) const
	{
		return _color[index];
	}

	bool operator == (const Color &rhs) const
	{
		return ( *((int *)this) == *((int *)&rhs) );
	}

	bool operator != (const Color &rhs) const
	{
		return !(operator==(rhs));
	}

	Color &operator=( const Color &rhs )
	{
		SetRawColor( rhs.GetRawColor() );
		return *this;
	}
	
private:
	unsigned char _color[4];
};

typedef struct color32_s
{
	bool operator!=( const struct color32_s &other ) const;
	byte r , g , b , a;

	// assign and copy by using the whole register rather
	// than byte-by-byte copy. (No, the compiler is not
	// smart enough to do this for you. /FAcs if you 
	// don't believe me.)
	inline unsigned* asInt( void ) { return reinterpret_cast<unsigned*>( this ); }
	inline unsigned long* asDword( void ) { return reinterpret_cast<unsigned long*>( this ); }
	inline const unsigned* asInt( void ) const { return reinterpret_cast<const unsigned*>( this ); }
	// This thing is in a union elsewhere, and union members can't have assignment
	// operators, so you have to explicitly assign using this, or be slow. SUCK.
	inline void Copy( const color32_s &rhs )
	{
		*asInt() = *rhs.asInt();
	}

} color32;

inline bool color32::operator!=( const color32 &other ) const
{
	return r != other.r || g != other.g || b != other.b || a != other.a;
}