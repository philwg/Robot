// **********************************************************************
// * FILE  : Vector4D.cpp
// * GROUP : TecLibs, section Math
// *---------------------------------------------------------------------
// * PURPOSE : Implementation of Vector4D
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
Vector4D::Vector4D()
{
    NULL;
}
Vector4D::Vector4D( const Float& fValue )
{
    x = y = z = w = fValue;
}
Vector4D::Vector4D( const Float& x , const Float& y , const Float& z , const Float& w )
:x(x),y(y),z(z),w(w)
{
    NULL;
}
Vector4D::Vector4D( const Vector4D& V )
:x(V.x),y(V.y),z(V.z),w(V.w)
{
    NULL;
}
Vector4D::Vector4D( const Vector3D& V )
:x(V.x),y(V.y),z(V.z),w(0)
{
    NULL;
}
Vector4D::Vector4D( const Point3D& P )
:x(P.x),y(P.y),z(P.z),w(1)
{
    NULL;
}

// Set (constructors-like)
void Vector4D::Set( const Float& fValue )
{
    x = y = z = w = fValue;
}
void Vector4D::Set( const Float& x , const Float& y , const Float& z , const Float& w )
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}
void Vector4D::Set( const Vector4D& V )
{
    x = V.x;
    y = V.y;
    z = V.z;
    w = V.w;
}
void Vector4D::Set( const Vector3D& V )
{
    x = V.x;
    y = V.y;
    z = V.z;
    w = 0;
}
void Vector4D::Set( const Point3D& P )
{
    x = P.x;
    y = P.y;
    z = P.z;
    w = 1;
}

// Assignement
const Vector4D& Vector4D::operator =( const Vector4D& V )
{
    x = V.x;
    y = V.y;
    z = V.z;
    w = V.w;

    return *this;
}

// Conversions
Vector4D::operator const Point3D ( void )
{
    static Point3D s_Point;

    s_Point.x = x;
    s_Point.y = y;
    s_Point.z = z;

    return s_Point;
}
Vector4D::operator const Vector3D ( void )
{
    static Vector3D s_Vector;

    s_Vector.x = x;
    s_Vector.y = y;
    s_Vector.z = z;

    return s_Vector;
}


// ----------------------------------------------------------------------
// +---------
// | Addition/Substraction
// +---------
// With another vector (Internal laws)
const Vector4D operator + ( const Vector4D& U , const Vector4D& V )
{
    Vector4D::ms_Vector.x = U.x + V.x;
    Vector4D::ms_Vector.y = U.y + V.y;
    Vector4D::ms_Vector.z = U.z + V.z;
    Vector4D::ms_Vector.w = U.w + V.w;

    return Vector4D::ms_Vector;
}
const Vector4D operator - ( const Vector4D& U , const Vector4D& V )
{
    Vector4D::ms_Vector.x = U.x - V.x;
    Vector4D::ms_Vector.y = U.y - V.y;
    Vector4D::ms_Vector.z = U.z - V.z;
    Vector4D::ms_Vector.w = U.w - V.w;

    return Vector4D::ms_Vector;
}

// With assignement
const Vector4D& Vector4D::operator += ( const Vector4D& V )
{
    x += V.x;
    y += V.y;
    z += V.z;
    w += V.w;

    return *this;
}
const Vector4D& Vector4D::operator -= ( const Vector4D& V )
{
    x -= V.x;
    y -= V.y;
    z -= V.z;
    w -= V.w;

    return *this;
}

// Unary
const Vector4D operator - ( const Vector4D& V )
{
    Vector4D::ms_Vector.x = -V.x;
    Vector4D::ms_Vector.y = -V.y;
    Vector4D::ms_Vector.z = -V.z;
    Vector4D::ms_Vector.w = -V.w;

    return Vector4D::ms_Vector;
}


// ----------------------------------------------------------------------
// +---------
// | Multiplication/Division
// +---------
// With a scalar (External laws)
const Vector4D operator * ( const Float& fValue , const Vector4D& V )
{
    Vector4D::ms_Vector.x = fValue * V.x;
    Vector4D::ms_Vector.y = fValue * V.y;
    Vector4D::ms_Vector.z = fValue * V.z;
    Vector4D::ms_Vector.w = fValue * V.w;

    return Vector4D::ms_Vector;
}
const Vector4D operator * ( const Vector4D& V , const Float& fValue )
{
    Vector4D::ms_Vector.x = fValue * V.x;
    Vector4D::ms_Vector.y = fValue * V.y;
    Vector4D::ms_Vector.z = fValue * V.z;
    Vector4D::ms_Vector.w = fValue * V.w;

    return Vector4D::ms_Vector;
}
const Vector4D operator / ( const Float& fValue , const Vector4D& V )
{
    Vector4D::ms_Vector.x = fValue / V.x;
    Vector4D::ms_Vector.y = fValue / V.y;
    Vector4D::ms_Vector.z = fValue / V.z;
    Vector4D::ms_Vector.w = fValue / V.w;

    return Vector4D::ms_Vector;
}
const Vector4D operator / ( const Vector4D& V , const Float& fValue )
{
    Vector4D::ms_Vector.x = V.x / fValue;
    Vector4D::ms_Vector.y = V.y / fValue;
    Vector4D::ms_Vector.z = V.z / fValue;
    Vector4D::ms_Vector.w = V.w / fValue;

    return Vector4D::ms_Vector;
}

// With assignement
const Vector4D& Vector4D::operator *= ( const Float& fValue )
{
    x *= fValue;
    y *= fValue;
    z *= fValue;
    w *= fValue;

    return *this;
}
const Vector4D& Vector4D::operator /= ( const Float& fValue )
{
    x /= fValue;
    y /= fValue;
    z /= fValue;
    w /= fValue;

    return *this;
}



// ----------------------------------------------------------------------
// +---------
// | Euclidian operations
// +---------
const Float Dot( const Vector4D& U , const Vector4D& V )
{
    static Float s_Float;

    s_Float = (U.x * V.x) + (U.y * V.y) + (U.z * V.z) + (U.w * V.w);
    
    return s_Float;
}
const Float Norm( const Vector4D& V )
{
    static Float s_Float;

    s_Float = sqrt( sqr(V.x) + sqr(V.y) + sqr(V.z)  + sqr(V.w));
    
    return s_Float;
}
const Float NormSquare( const Vector4D& V )
{
    static Float s_Float;

    s_Float = sqr(V.x) + sqr(V.y) + sqr(V.z) + sqr(V.w);
    
    return s_Float;
}

// ----------------------------------------------------------------------
// +---------
// | Affine operations
// +---------
const Vector4D Mid( const Vector4D& U , const Vector4D& V )
{
    Vector4D::ms_Vector.x = (U.x + V.x) / 2;
    Vector4D::ms_Vector.y = (U.y + V.y) / 2;
    Vector4D::ms_Vector.z = (U.z + V.z) / 2;
    Vector4D::ms_Vector.w = (U.w + V.w) / 2;

    return Vector4D::ms_Vector;
}
const Vector4D Mid( const Float& a , const Vector4D& U , const Float& b , const Vector4D& V )
{
    Vector4D::ms_Vector.x = ((a * U.x) + (b * V.x)) / 2;
    Vector4D::ms_Vector.y = ((a * U.y) + (b * V.y)) / 2;
    Vector4D::ms_Vector.z = ((a * U.z) + (b * V.z)) / 2;
    Vector4D::ms_Vector.w = ((a * U.w) + (b * V.w)) / 2;

    return Vector4D::ms_Vector;
}


// ----------------------------------------------------------------------
// +---------
// | Utilities
// +---------
void Vector4D::Normalize( void )
{
    static Float s_Float;

    s_Float = Norm( *this );
    
    x /= s_Float;
    y /= s_Float;
    z /= s_Float;
    w /= s_Float;
}


