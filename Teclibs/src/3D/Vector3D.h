// **********************************************************************
// * FILE  : Vector3D.h
// * GROUP : TecLibs/3D
// *---------------------------------------------------------------------
// * PURPOSE : Class for 3D Vector
// * COMMENT : 
// *---------------------------------------------------------------------
// * DATES     : 23/06/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * MODIFIED  : Cédric Guérin (cguerin@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/Teclab 2000
// **********************************************************************
#ifndef _Vector3D_h_
#define _Vector3D_h_

// ----------------------------------------------------------------------
// **************************************************
// * Vector3D
// *-------------------------------------------------
// * - Definition of 3D vector
// * - 
// **************************************************
class Vector3D
{
	friend class Matrix3x3;
	friend class Matrix3x4;
public:
    // +---------
    // | Life-cyle
    // +---------
    // Constructors
    inline Vector3D();
        // DO NOTHING! (For immediate creation)
    inline Vector3D( const Float& fValue );
        // Set all coordinates to fValue
    inline Vector3D( const Float& x , const Float& y , const Float& z );
    inline Vector3D( const Vector3D& V );
    inline Vector3D( const Point3D& P );
        // Convert point to vector
    inline Vector3D( const Point3D& A , const Point3D& B );
        // Create the vector AB

    // Set (constructors-like)
    inline void Set( const Float& fValue );
    inline void Set( const Float& x , const Float& y , const Float& z );
    inline void Set( const Vector3D& V );
    inline void Set( const Point3D& P );
    inline void Set( const Point3D& A , const Point3D& B );

    // Assignement
    inline const Vector3D& operator =( const Vector3D& V );

    // Conversions
    inline operator const Point3D& () const;
	inline operator const Vector4D ( void ) const;


    // +---------
    // | Addition/Substraction
    // +---------
    // With another vector (Internal laws)
    friend inline const Vector3D operator + ( const Vector3D& U , const Vector3D& V );
    friend inline const Vector3D operator - ( const Vector3D& U , const Vector3D& V );

    // With assignement
    inline const Vector3D& operator += ( const Vector3D& V );
    inline const Vector3D& operator -= ( const Vector3D& V );

    // Unary
    friend inline const Vector3D operator - ( const Vector3D& V );

    
    // +---------
    // | Multiplication/Division
    // +---------
    // With a scalar (External laws)
    friend inline const Vector3D operator * ( const Float& fValue , const Vector3D& V );
    friend inline const Vector3D operator * ( const Vector3D& V , const Float& fValue );
    friend inline const Vector3D operator * ( const Vector3D& V , const Vector3D& W );
    friend inline const Vector3D operator / ( const Float& fValue , const Vector3D& V );
    friend inline const Vector3D operator / ( const Vector3D& V , const Float& fValue );
    friend inline const Vector3D operator / ( const Vector3D& V , const Vector3D& W );

    // With assignement
    inline const Vector3D& operator *= ( const Float& fValue );
    inline const Vector3D& operator *= ( const Vector3D& W);
    inline const Vector3D& operator /= ( const Float& fValue );
    inline const Vector3D& operator /= ( const Vector3D& W);


    // +---------
    // | Cross product
    // +---------
    friend inline const Vector3D operator ^ ( const Vector3D& U , const Vector3D& V );

    // With assignement
    inline const Vector3D& operator ^= ( const Vector3D& V );
	inline void CrossProduct( const Vector3D& V, const Vector3D& W );
		

    // +---------
    // | Euclidian operations
    // +---------
    friend inline const Float Dot( const Vector3D& U , const Vector3D& V );
    friend inline const Float Norm( const Vector3D& V );
    friend inline const Float NormSquare( const Vector3D& V );

    // +---------
    // | Affine operations
    // +---------
    friend inline const Vector3D Mid( const Vector3D& U , const Vector3D& V );
    friend inline const Vector3D Mid( const Float& a , const Vector3D& U , const Float& b , const Vector3D& V );


    // +---------
    // | Utilities
    // +---------
    inline void Normalize( void );
	
	friend inline bool operator<( const Vector3D& U , const Vector3D& V );
	friend inline bool operator<=( const Vector3D& U , const Vector3D& V );
	friend inline bool operator>( const Vector3D& U , const Vector3D& V );
	friend inline bool operator>=( const Vector3D& U , const Vector3D& V );
	friend inline bool operator==( const Vector3D& U , const Vector3D& V );
	friend inline bool operator!=( const Vector3D& U , const Vector3D& V );

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

#endif //_Vector3D_h_
