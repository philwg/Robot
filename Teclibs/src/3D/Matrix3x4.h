// **********************************************************************
// * FILE  : Matrix3x4.h
// * GROUP : TecLibs/3D
// *---------------------------------------------------------------------
// * PURPOSE : Matrix 3x4
// * COMMENT : 
// *---------------------------------------------------------------------
// * DATES     : 23/06/2000
// * AUTHORS   : Antoine Leclercq (aleclercq@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************

#ifndef _Matrix3x4_h_
#define _Matrix3x4_h_

// **************************************************
// * Matrix3x4 class
// *-------------------------------------------------
// * - Matrix 3x4
// *
// *	e[0][0]	e[1][0]	e[2][0]	e[3][0]
// *	e[0][1]	e[1][1]	e[2][1]	e[3][1]
// *	e[0][2]	e[1][2]	e[2][2]	e[3][2]
// *
// **************************************************

class Matrix3x4
{
	friend class Matrix3x3;
	friend class Vector3D;
	friend class Quaternion;

public:

	Float e[4][3];
	
public:
// +---------
// | Life Cycle
// +---------
	inline Matrix3x4(){;}
	inline Matrix3x4(const Float& e00, const Float& e01, const Float& e02,
					 const Float& e10, const Float& e11, const Float& e12,
					 const Float& e20, const Float& e21, const Float& e22,
					 const Float& e30, const Float& e31, const Float& e32);
	inline Matrix3x4(const Matrix3x4& crMatrix);
	inline Matrix3x4(const Quaternion& cr_Quaternion, const Vector3D& cr_Vector);
	inline Matrix3x4(const Vector3D& vx, const Vector3D& vy, const Vector3D& vz, const Point3D& pos);
	
	void Set(const Quaternion& q, const Point3D& p);
	void Set(const Quaternion& q);

// +---------
// | Pure Matrix Operations [ Matrix operator???(Matrix) ]
// +---------
	inline void  SetIdentity();
	inline friend const Matrix3x4 Inv(const Matrix3x4 & cr_Matrix);
	inline friend const Float Det(const Matrix3x4 & cr_Matrix);
	inline friend const Float Norm(const Matrix3x4 & cr_Matrix);
	inline friend const Float NormSquare(const Matrix3x4 & cr_Matrix);
	inline friend const Float Trace(const Matrix3x4 & cr_Matrix);
	

	inline const Matrix3x4 operator+ (const Matrix3x4& crMatrix) const;
	inline const Matrix3x4 operator- (const Matrix3x4& crMatrix) const;
	inline const Matrix3x4 operator* (const Matrix3x4& crMatrix) const;
	inline void operator=(const Matrix3x4& crMatrix);

// +---------
// | Inner operators
// +---------
	inline void operator+=(const Matrix3x4& crMatrix);
	inline void operator-=(const Matrix3x4& crMatrix);
	inline void operator*=(const Matrix3x4& crMatrix);

// +---------
// | Matrix operators with Vectors
// +---------
	inline const Vector3D operator*(const Vector3D& cr_Vector) const; 
	inline const Point3D operator*(const Point3D& cr_Point) const ; 
	inline void TransformPoints(Point3D* tab, int count) const;
	inline void TransformVectors(Vector3D* tab, int count) const;
	
// +---------
// | Matrix operators with Floats
// +---------
	inline const Matrix3x4 operator*(const Float& crFloat); 
	inline friend const Matrix3x4 operator*(const Matrix3x4& crMatrix,const Float& crFloat); 
	inline void operator*=(const Float& crFloat);

// +---------
// | Operators specific to transformation matrices
// +---------
	inline void SetRotationX(const Float& Angle);
	inline void SetRotationY(const Float& Angle);
	inline void SetRotationZ(const Float& Angle);
	inline void PreRotateX(const Float& Angle);
	inline void PreRotateY(const Float& Angle);
	inline void PreRotateZ(const Float& Angle);
	inline void PostRotateX(const Float& Angle);
	inline void PostRotateY(const Float& Angle);
	inline void PostRotateZ(const Float& Angle);
	
	inline void SetRotationXYZ(const Float& AngleX,const Float& AngleY,const Float& AngleZ);
	inline void SetRotationZYX(const Float& AngleX,const Float& AngleY,const Float& AngleZ);

	inline void PreRotateXYZ(const Float& AngleX,const Float& AngleY,const Float& AngleZ);
	inline void PreRotateZYX(const Float& AngleX,const Float& AngleY,const Float& AngleZ);
	inline void PostRotateXYZ(const Float& AngleX,const Float& AngleY,const Float& AngleZ);
	inline void PostRotateZYX(const Float& AngleX,const Float& AngleY,const Float& AngleZ);

	inline void SetScale(const Float& ScaleX, const Float& ScaleY, const Float& ScaleZ);
	inline void PreScale(const Float& ScaleX, const Float& ScaleY, const Float& ScaleZ);
	inline void PostScale(const Float& ScaleX, const Float& ScaleY, const Float& ScaleZ);
	
	inline void SetTranslation(const Vector3D& Translation);
	inline void PreTranslate(const Vector3D& Translation);
	inline void PostTranslate(const Vector3D& Translation);

	inline void PreMultiply(const Matrix3x4& m);
	inline void PostMultiply(const Matrix3x4& m);
	
	inline const Vector3D GetTranslation() const;

    inline operator const Quaternion (void);
	inline operator const Matrix3x3& ();
};

#endif

