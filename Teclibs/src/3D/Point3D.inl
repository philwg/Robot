// **********************************************************************
// * FILE  : Point3D.cpp
// * GROUP : TecLibs, section Math
// *---------------------------------------------------------------------
// * PURPOSE : Implementation of Point3D
// *---------------------------------------------------------------------
// * DATES     : 16/05/2000
// * DATES     : 22/01/2001 - Removed all uses of static ms_Point in calculations. CG
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * AUTHORS   : Cédric Guérin (cguerin@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/Teclab 2000
// **********************************************************************



// ----------------------------------------------------------------------
// +---------
// | Life-cycle
// +---------
// Constructors
Point3D::Point3D()
{
    NULL;
}
Point3D::Point3D( const Float& fValue )
{
    x = y = z = fValue;
}
Point3D::Point3D( const Float& x , const Float& y , const Float& z )
:x(x),y(y),z(z)
{
    NULL;
}
Point3D::Point3D( const Vector3D& V )
:x(V.x),y(V.y),z(V.z)
{
    NULL;
}
Point3D::Point3D( const Point3D& P )
:x(P.x),y(P.y),z(P.z)
{
    NULL;
}

// Set (constructors-like)
void Point3D::Set( const Float& fValue )
{
    x = y = z = fValue;
}
void Point3D::Set( const Float& x , const Float& y , const Float& z )
{
    this->x = x;
    this->y = y;
    this->z = z;
}
void Point3D::Set( const Vector3D& V )
{
    x = V.x;
    y = V.y;
    z = V.z;
}
void Point3D::Set( const Point3D& P )
{
    x = P.x;
    y = P.y;
    z = P.z;
}

// Assignement
const Point3D& Point3D::operator =( const Point3D& V )
{
    x = V.x;
    y = V.y;
    z = V.z;

    return *this;
}

// Conversions
Point3D::operator const Vector3D& ( void )
{
    return *(Vector3D*)this;
}
Point3D::operator const Vector4D ( void )
{
    static Vector4D s_Vector;

    s_Vector.x = x;
    s_Vector.y = y;
    s_Vector.z = z;
    s_Vector.w = 0;

    return s_Vector;
}


// ----------------------------------------------------------------------
// +---------
// | Addition/Substraction
// +---------
// With another vector (Internal laws)
const Point3D operator + ( const Point3D& U , const Point3D& V )
{
    return Point3D(U.x + V.x, U.y + V.y, U.z + V.z);
}

const Point3D operator - ( const Point3D& U , const Point3D& V )
{
	return Point3D(U.x - V.x, U.y - V.y, U.z - V.z);
}

// With assignement
const Point3D& Point3D::operator += ( const Point3D& V )
{
    x += V.x;
    y += V.y;
    z += V.z;

    return *this;
}
const Point3D& Point3D::operator -= ( const Point3D& V )
{
    x -= V.x;
    y -= V.y;
    z -= V.z;

    return *this;
}

// Unary
const Point3D operator - ( const Point3D& V )
{
    return Point3D(-V.x, -V.y, -V.z);
}


// ----------------------------------------------------------------------
// +---------
// | Multiplication/Division
// +---------
// With a scalar (External laws)
const Point3D operator * ( const Float& fValue , const Point3D& V )
{
    return Point3D(fValue * V.x, fValue * V.y, fValue * V.z);
}

const Point3D operator * ( const Point3D& V , const Float& fValue )
{
    return Point3D(V.x * fValue, V.y * fValue, V.z * fValue);
}

const Point3D operator * ( const Point3D& V , const Point3D& W )
{
	return Point3D(V.x * W.x, V.y * W.y, V.z * W.z);
}

const Point3D operator / ( const Float& fValue , const Point3D& V )
{
    return Point3D(fValue / V.x, fValue / V.y, fValue / V.z);
}

const Point3D operator / ( const Point3D& V , const Float& fValue )
{
    return Point3D(V.x / fValue, V.y / fValue, V.z / fValue);
}

const Point3D operator / ( const Point3D& V , const Point3D& W )
{
	return Point3D(V.x / W.x, V.y / W.y, V.z / W.z);
}


// With assignement
const Point3D& Point3D::operator *= ( const Float& fValue )
{
    x *= fValue;
    y *= fValue;
    z *= fValue;

    return *this;
}
const Point3D& Point3D::operator /= ( const Float& fValue )
{
    x /= fValue;
    y /= fValue;
    z /= fValue;

    return *this;
}


// ----------------------------------------------------------------------
// +---------
// | Euclidian operations
// +---------
const Float Norm( const Point3D& P )
{
    static Float s_Float;

    s_Float = sqrt( sqr(P.x) + sqr(P.y) + sqr(P.z) );
    
    return s_Float;
}
const Float NormSquare( const Point3D& P )
{
    static Float s_Float;

    s_Float = sqr(P.x) + sqr(P.y) + sqr(P.z);
    
    return s_Float;
}

// ----------------------------------------------------------------------
// +---------
// | Affine operations
// +---------
const Point3D Mid( const Point3D& P , const Point3D& Q )
{
    return Point3D( (P.x + Q.x) * (Float)0.5,
		(P.y + Q.y) * (Float)0.5,
		(P.z + Q.z) * (Float)0.5 );
}

const Point3D Mid( const Float& a , const Point3D& P , const Float& b , const Point3D& Q )
{
    return Point3D( ((a * P.x) + (b * Q.x)) * (Float)0.5,
		((a * P.y) + (b * Q.y)) * (Float)0.5,
		((a * P.z) + (b * Q.z)) * (Float)0.5 );
}


// ----------------------------------------------------------------------
// +---------
// | Utilities
// +---------
void Point3D::Normalize( void )
{
    register Float tmp = Norm( *this );
    if (tmp != (Float)0.0)
	{
		tmp = ((Float)1.0)/tmp;
		x *= tmp;
		y *= tmp;
		z *= tmp;
	}
}

inline const Point3D Lerp( const Point3D& P , const Point3D& Q, const Float& t )
{
	register Float s = (Float)1.0 - t;
    return Point3D( (s * P.x) + (t * Q.x),
		(s * P.y) + (t * Q.y),
		(s * P.z) + (t * Q.z) );
}


// +---------
// | Acces Operators
// +---------
const Float& Point3D::operator[](Int i) const
{
	assert(i>=0 && i<3);
	return *((&x)+i);
}

Float& Point3D::operator[](Int i)
{
	assert(i>=0 && i<3);
	return *((&x)+i);
}

