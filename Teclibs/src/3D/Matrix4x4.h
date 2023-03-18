// **********************************************************************
// * FILE  : Matrix4x4.h
// * GROUP : TecLibs/3D
// *---------------------------------------------------------------------
// * PURPOSE : Matrix 4x4
// * COMMENT : 
// *---------------------------------------------------------------------
// * DATES     : 23/06/2000
// * AUTHORS   : Antoine Leclercq (aleclercq@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************

#ifndef _Matrix4x4_h_
#define _Matrix4x4_h_

// **************************************************
// * Matrix4x4 class
// *-------------------------------------------------
// * - Square Matrix 4x4
// *
// *	e[0][0]	e[1][0]	e[2][0]	e[3][0]
// *	e[0][1]	e[1][1]	e[2][1]	e[3][1]
// *	e[0][2]	e[1][2]	e[2][2]	e[3][2]
// *	e[0][3]	e[1][3]	e[2][3]	e[3][3]
// *
// **************************************************

class Matrix4x4
{
	friend class Matrix3x3;
	friend class Matrix3x4;
	friend class Quaternion;
public:

	Float e[4][4];
public:
// +---------
// | Life Cycle
// +---------
	inline Matrix4x4(){;}
	inline Matrix4x4(const Matrix4x4& cr_Matrix);
	inline Matrix4x4(const Quaternion& cr_Quaternion, const Vector3D& cr_Vector);

// +---------
// | Pure Matrix Operations [ Matrix operator???(Matrix) ]
// +---------
	inline void SetIdentity();
	inline const Matrix4x4& Inv();
	inline const Float& Det();
	inline const Float& Norm();
	inline const Float& NormSquare();
	inline const Float& Trace();

	inline const Matrix4x4& operator+ (const Matrix4x4& crMatrix);
	inline const Matrix4x4& operator- (const Matrix4x4& crMatrix);
	inline const Matrix4x4& operator* (const Matrix4x4& crMatrix);
	inline void operator=(const Matrix4x4& crMatrix);

// +---------
// | Unary Operator
// +---------
	inline void operator-();

// +---------
// | Inner operators
// +---------
	inline void operator+=(const Matrix4x4& crMatrix);
	inline void operator-=(const Matrix4x4& crMatrix);
	inline void operator*=(const Matrix4x4& crMatrix);
	inline void operator*=(const Float& crFloat);


// +---------
// | Matrix operators with Vectors
// +---------
	inline const Vector3D& operator*(const Vector3D& crVector); 
	inline const Vector3D& operator*(const Point3D& crVector); 
	inline const Vector3D& operator*(const Vector4D& crVector); 


// +---------
// | Matrix operators with Floats
// +---------
	inline const Vector3D& operator*(const Float& crFloat); 
	inline friend const Matrix4x4& operator*(const Float& crFloat,const Matrix4x4& crMatrix); 

// +---------
// | Operators specific to transformation matrices
// +---------
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
	inline void SetScale(const Float& ScaleX, const Float &ScaleY, const Float ScaleZ);
	inline void PreScale(const Float& ScaleX, const Float &ScaleY, const Float ScaleZ);
	inline void PostScale(const Float& ScaleX, const Float &ScaleY, const Float ScaleZ);
	inline void SetTranslation(const Vector3D& Translation);
	inline void AddTranslation(const Vector3D& Translation);

private:
	static Matrix4x4 ms_Matrix;
};

#endif

