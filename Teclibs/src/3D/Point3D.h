// **********************************************************************
// * FILE  : Point3D.h
// * GROUP : TecLibs/3D
// *---------------------------------------------------------------------
// * PURPOSE : Class for 3D Point
// * COMMENT : Difference with Vector3D is not "Cross product" section,
// *           and not "Dot" operator.
// *---------------------------------------------------------------------
// * DATES     : 23/06/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/Teclab 2000
// **********************************************************************
#ifndef _Point3D_h_
#define _Point3D_h_



// ----------------------------------------------------------------------
// **************************************************
// * Point3D
// *-------------------------------------------------
// * - Definition of 3D vector
// * - 
// **************************************************
class Point3D
{
    friend class Matrix3x4;
public:
    // +---------
    // | Life-cyle
    // +---------
    // Constructors
    inline Point3D();
        // DO NOTHING! (For immediate creation)
    inline Point3D( const Float& fValue );
        // Set all coordinates to fValue
    inline Point3D( const Float& x , const Float& y , const Float& z );
    inline Point3D( const Point3D& P );
    inline Point3D( const Vector3D& V );
        // Convert vector to point

    // Set (constructors-like)
    inline void Set( const Float& fValue );
    inline void Set( const Float& x , const Float& y , const Float& z );
    inline void Set( const Point3D& V );
    inline void Set( const Vector3D& P );

    // Assignement
    inline const Point3D& operator =( const Point3D& V );

    // Conversions
    inline operator const Vector3D& ( void );
    inline operator const Vector4D ( void );


    // +---------
    // | Addition/Substraction
    // +---------
    // With another vector (Internal laws)
    friend inline const Point3D operator + ( const Point3D& U , const Point3D& V );
    friend inline const Point3D operator - ( const Point3D& U , const Point3D& V );

    // With assignement
    inline const Point3D& operator += ( const Point3D& V );
    inline const Point3D& operator -= ( const Point3D& V );

    // Unary
    friend inline const Point3D operator - ( const Point3D& V );

    
    // +---------
    // | Multiplication/Division
    // +---------
    // With a scalar (External laws)
    friend inline const Point3D operator * ( const Float& fValue , const Point3D& V );
    friend inline const Point3D operator * ( const Point3D& V , const Float& fValue );
    friend inline const Point3D operator * ( const Point3D& V , const Point3D& W );
    friend inline const Point3D operator / ( const Float& fValue , const Point3D& V );
    friend inline const Point3D operator / ( const Point3D& V , const Float& fValue );
    friend inline const Point3D operator / ( const Point3D& V , const Point3D& W );

    // With assignement
    inline const Point3D& operator *= ( const Float& fValue );
    inline const Point3D& operator /= ( const Float& fValue );


    // +---------
    // | Euclidian operations
    // +---------
    friend inline const Float Norm( const Point3D& P );
    friend inline const Float NormSquare( const Point3D& P );

    // +---------
    // | Affine operations
    // +---------
    friend inline const Point3D Mid( const Point3D& P , const Point3D& Q );
    friend inline const Point3D Mid( const Float& a , const Point3D& P , const Float& b , const Point3D& Q );

    friend inline const Point3D Lerp( const Point3D& P , const Point3D& Q, const Float& t );


    // +---------
    // | Utilities
    // +---------
    inline void Normalize( void );

	// +---------
	// | Acces Operators
	// +---------
	inline const Float& operator[](Int i) const;
	inline Float& operator[](Int i);

    // +---------
    // | Coordinates
    // +---------
    Float   x;
    Float   y;
    Float   z;
};

#endif //_Point3D_h_
