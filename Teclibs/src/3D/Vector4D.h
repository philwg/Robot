// **********************************************************************
// * FILE  : Vector4D.h
// * GROUP : TecLibs/3D
// *---------------------------------------------------------------------
// * PURPOSE : Class for 4D Vector (projective geometry)
// * COMMENT : 
// *---------------------------------------------------------------------
// * DATES     : 23/06/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/Teclab 2000
// **********************************************************************
#ifndef _Vector4D_h_
#define _Vector4D_h_



// ----------------------------------------------------------------------
// **************************************************
// * Vector4D
// *-------------------------------------------------
// * - Definition of 4D vector
// * - w=0 => vector 3D, w=1 => point 3D
// **************************************************
class Vector4D
{
public:
    // +---------
    // | Life-cyle
    // +---------
    // Constructors
    inline Vector4D();
        // DO NOTHING! (For immediate creation)
    inline Vector4D( const Float& fValue );
        // Set all coordinates to fValue
    inline Vector4D( const Float& x , const Float& y , const Float& z , const Float& w );
    inline Vector4D( const Vector4D& V );
    inline Vector4D( const Vector3D& V );
    inline Vector4D( const Point3D& P );
        // Convert 3D point or vector to 4D vector (w=0 for vector, and w=1 for point)

    // Set (constructors-like)
    inline void Set( const Float& fValue );
    inline void Set( const Float& x , const Float& y , const Float& z , const Float& w );
    inline void Set( const Vector4D& V );
    inline void Set( const Point3D& P );
    inline void Set( const Vector3D& V );

    // Assignement
    inline const Vector4D& operator =( const Vector4D& V );

    // Conversions
    inline operator const Point3D ( void );
    inline operator const Vector3D ( void );


    // +---------
    // | Addition/Substraction
    // +---------
    // With another vector (Internal laws)
    friend inline const Vector4D operator + ( const Vector4D& U , const Vector4D& V );
    friend inline const Vector4D operator - ( const Vector4D& U , const Vector4D& V );

    // With assignement
    inline const Vector4D& operator += ( const Vector4D& V );
    inline const Vector4D& operator -= ( const Vector4D& V );

    // Unary
    friend inline const Vector4D operator - ( const Vector4D& U );

    
    // +---------
    // | Multiplication/Division
    // +---------
    // With a scalar (External laws)
    friend inline const Vector4D operator * ( const Float& fValue , const Vector4D& V );
    friend inline const Vector4D operator * ( const Vector4D& V , const Float& fValue );
    friend inline const Vector4D operator / ( const Float& fValue , const Vector4D& V );
    friend inline const Vector4D operator / ( const Vector4D& V , const Float& fValue );

    // With assignement
    inline const Vector4D& operator *= ( const Float& fValue );
    inline const Vector4D& operator /= ( const Float& fValue );


//// ADD LLC: Peut-etre un jour?
//     // +---------
//     // | Cross product
//     // +---------
//     friend inline const Vector4D& operator ^ ( const Vector4D& U , const Vector4D& V );
// 
//     // With assignement
//     inline const Vector4D& operator ^= ( const Vector4D& V );
// 
// 
//// END

    // +---------
    // | Euclidian operations
    // +---------
    friend inline const Float Dot( const Vector4D& U , const Vector4D& V );
    friend inline const Float Norm( const Vector4D& V );
    friend inline const Float NormSquare( const Vector4D& V );

    // +---------
    // | Affine operations
    // +---------
    friend inline const Vector4D Mid( const Vector4D& U , const Vector4D& V );
    friend inline const Vector4D Mid( const Float& a , const Vector4D& U , const Float& b , const Vector4D& V );


    // +---------
    // | Utilities
    // +---------
    inline void Normalize( void );


    // +---------
    // | Coordinates
    // +---------
    Float   x;
    Float   y;
    Float   z;
    Float   w;



private:
    // +---------
    // | Variables
    // +---------
    // Temporary vector for inline returns
    static Vector4D ms_Vector;
};

#endif //_Vector4D_h_
