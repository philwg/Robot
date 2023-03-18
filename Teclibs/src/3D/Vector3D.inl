// **********************************************************************
// * FILE  : Vector3D.cpp
// * GROUP : TecLibs, section Math
// *---------------------------------------------------------------------
// * PURPOSE : Implementation of Vector3D
// *---------------------------------------------------------------------
// * DATES     : 16/05/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/Teclab 2000
// **********************************************************************



// ----------------------------------------------------------------------
// +---------
// | Life-cycle
// +---------
// Constructors
Vector3D::Vector3D()
{
    NULL;
}
Vector3D::Vector3D( const Float& fValue )
{
    x = y = z = fValue;
}
Vector3D::Vector3D( const Float& x , const Float& y , const Float& z )
:x(x),y(y),z(z)
{
    NULL;
}
Vector3D::Vector3D( const Vector3D& V )
:x(V.x),y(V.y),z(V.z)
{
    NULL;
}
Vector3D::Vector3D( const Point3D& P )
:x(P.x),y(P.y),z(P.z)
{
    NULL;
}
Vector3D::Vector3D( const Point3D& A , const Point3D& B )
:x(B.x-A.x),y(B.y-A.y),z(B.z-A.z)
{
    NULL;
}

// Set (constructors-like)
void Vector3D::Set( const Float& fValue )
{
    x = y = z = fValue;
}
void Vector3D::Set( const Float& x , const Float& y , const Float& z )
{
    this->x = x;
    this->y = y;
    this->z = z;
}
void Vector3D::Set( const Vector3D& V )
{
    x = V.x;
    y = V.y;
    z = V.z;
}
void Vector3D::Set( const Point3D& P )
{
    x = P.x;
    y = P.y;
    z = P.z;
}
void Vector3D::Set( const Point3D& A , const Point3D& B )
{
    x = B.x - A.x;
    y = B.y - A.y;
    z = B.z - A.z;
}

// Assignement
const Vector3D& Vector3D::operator=( const Vector3D& V )
{
    x = V.x;
    y = V.y;
    z = V.z;

    return *this;
}

// Conversions
Vector3D::operator const Point3D& () const
{
    return *(Point3D*)this;
}

Vector3D::operator const Vector4D ( void ) const
{
    return Vector4D(x, y, z, 0);
}


// ----------------------------------------------------------------------
// +---------
// | Addition/Substraction
// +---------
// With another vector (Internal laws)
const Vector3D operator + ( const Vector3D& U , const Vector3D& V )
{
    return Vector3D(U.x + V.x, U.y + V.y, U.z + V.z);
}

const Vector3D operator - ( const Vector3D& U , const Vector3D& V )
{
    return Vector3D( U.x - V.x, U.y - V.y, U.z - V.z);
}

// With assignement
const Vector3D& Vector3D::operator += ( const Vector3D& V )
{
    x += V.x;
    y += V.y;
    z += V.z;

    return *this;
}
const Vector3D& Vector3D::operator -= ( const Vector3D& V )
{
    x -= V.x;
    y -= V.y;
    z -= V.z;

    return *this;
}

// Unary
const Vector3D operator - ( const Vector3D& V )
{
    return Vector3D(-V.x, -V.y, -V.z);
}


// ----------------------------------------------------------------------
// +---------
// | Multiplication/Division
// +---------
// With a scalar (External laws)

const Vector3D operator * ( const Float& fValue , const Vector3D& V )
{
    return Vector3D(fValue * V.x, fValue * V.y, fValue * V.z);
}

const Vector3D operator * ( const Vector3D& V , const Float& fValue )
{
	return Vector3D( V.x * fValue, V.y * fValue, V.z * fValue);
}

const Vector3D operator * ( const Vector3D& V , const Vector3D& W )
{
	return Vector3D( V.x * W.x, V.y * W.y, V.z * W.z);
}

const Vector3D operator / ( const Float& fValue , const Vector3D& V )
{
    return Vector3D(fValue / V.x, fValue / V.y, fValue / V.z);
}

const Vector3D operator / ( const Vector3D& V , const Float& fValue )
{
	Float fval = 1 / fValue;
    return Vector3D(V.x * fval, V.y * fval, V.z * fval);
}

const Vector3D operator / ( const Vector3D& V , const Vector3D& W )
{
    return Vector3D(V.x / W.x, V.y / W.y, V.z / W.z);
}


// With assignement
const Vector3D& Vector3D::operator *= ( const Float& fValue )
{
    x *= fValue;
    y *= fValue;
    z *= fValue;

    return *this;
}

const Vector3D& Vector3D::operator *= ( const Vector3D& V )
{
    x *= V.x;
    y *= V.y;
    z *= V.z;

    return *this;
}

const Vector3D& Vector3D::operator /= ( const Float& fValue )
{
    x /= fValue;
    y /= fValue;
    z /= fValue;

    return *this;
}

const Vector3D& Vector3D::operator /= ( const Vector3D& V )
{
    x /= V.x;
    y /= V.y;
    z /= V.z;

    return *this;
}

// ----------------------------------------------------------------------
// +---------
// | Cross product
// +---------
const Vector3D operator ^ ( const Vector3D& U , const Vector3D& V )
{
    return Vector3D((U.y * V.z) - (U.z * V.y),
					(U.z * V.x) - (U.x * V.z),
					(U.x * V.y) - (U.y * V.x));
}

// With assignement
const Vector3D& Vector3D::operator ^= ( const Vector3D& V )
{
	Float _x = x, _y = y;
    x = (_y * V.z) - (z * V.y);
    y = (z * V.x) - (_x * V.z);
    z = (_x * V.y) - (_y * V.x);

    return *this;
}

void Vector3D::CrossProduct( const Vector3D& V, const Vector3D& W )
{
    x = (V.y * W.z) - (V.z * W.y);
    y = (V.z * W.x) - (V.x * W.z);
    z = (V.x * W.y) - (V.y * W.x);
}

// ----------------------------------------------------------------------
// +---------
// | Euclidian operations
// +---------
const Float Dot( const Vector3D& U , const Vector3D& V )
{
    return ((U.x * V.x) + (U.y * V.y) + (U.z * V.z));
}

const Float NormSquare( const Vector3D& V )
{
    return (sqr(V.x) + sqr(V.y) + sqr(V.z));
}

const Float Norm( const Vector3D& V )
{
    return (sqrt( sqr(V.x) + sqr(V.y) + sqr(V.z) ));
}

// ----------------------------------------------------------------------
// +---------
// | Affine operations
// +---------
const Vector3D Mid( const Vector3D& U , const Vector3D& V )
{
    return Vector3D( (U.x + V.x) * (Float)0.5,
					 (U.y + V.y) * (Float)0.5,
					 (U.z + V.z) * (Float)0.5 );
}
const Vector3D Mid( const Float& a , const Vector3D& U , const Float& b , const Vector3D& V )
{
    return Vector3D( ((a * U.x) + (b * V.x)) * (Float)0.5,
					 ((a * U.y) + (b * V.y)) * (Float)0.5, 
					 ((a * U.z) + (b * V.z)) * (Float)0.5 );
}


// ----------------------------------------------------------------------
// +---------
// | Utilities
// +---------
void Vector3D::Normalize( void )
{
    Float tmp = Norm( *this );
    if (tmp != (Float)0.0)
	{
		tmp = ((Float)1.0) / tmp;
	    x *= tmp;
	    y *= tmp;
	    z *= tmp;
	}
}

bool operator<( const Vector3D& U , const Vector3D& V )
{
	return (U.x < V.x && U.y < V.y && U.z < V.z);
}

bool operator<=( const Vector3D& U , const Vector3D& V )
{
	return (U.x <= V.x && U.y <= V.y && U.z <= V.z);
}

bool operator>( const Vector3D& U , const Vector3D& V )
{
	return (U.x > V.x && U.y > V.y && U.z > V.z);
}

bool operator>=( const Vector3D& U , const Vector3D& V )
{
	return (U.x >= V.x && U.y >= V.y && U.z >= V.z);
}

bool operator==( const Vector3D& U , const Vector3D& V )
{
	return (U.x == V.x && U.y == V.y && U.z == V.z);
}

bool operator!=( const Vector3D& U , const Vector3D& V )
{
	return (U.x != V.x || U.y != V.y || U.z != V.z);
}

// +---------
// | Acces Operators
// +---------
const Float& Vector3D::operator[](Int i) const
{
	assert(i>=0 && i<3);
	return *((&x)+i);
}

Float& Vector3D::operator[](Int i)
{
	assert(i>=0 && i<3);
	return *((&x)+i);
}
