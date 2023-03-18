// **********************************************************************
// * FILE  : Matrix3x3.h
// * GROUP : TecLibs/3D
// *---------------------------------------------------------------------
// * PURPOSE : Base Classe for all the Matrices
// * COMMENT : 
// *---------------------------------------------------------------------
// * DATES     : 23/06/2000
// * AUTHORS   : Antoine Leclercq (aleclercq@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************

#ifndef _Matrix3x3_h_
#define _Matrix3x3_h_

// **************************************************
// * Matrix3x3 class
// *-------------------------------------------------
// * - Square Matrix 3x3
// *
// *	e[0][0]	e[1][0]	e[2][0]
// *	e[0][1]	e[1][1]	e[2][1]
// *	e[0][2]	e[1][2]	e[2][2]
// *
// **************************************************


class Matrix3x3 
{
	friend class Quaternion;
	friend class Matrix3x4;
	friend class Matrix4x4;

public:
	Float e[3][3];


public:
// +---------
// | Life Cycle
// +---------
	inline Matrix3x3();
	inline Matrix3x3(const Matrix3x3& cr_Matrix);
	inline Matrix3x3(const Quaternion& cr_Quaternion);


// +---------
// | Pure Matrix Operations [ Matrix operator???(Matrix) ]
// +---------
	inline void SetIdentity();
	inline friend const Matrix3x3 Inv(const Matrix3x3 & cr_Matrix);
	inline friend const Float Det(const Matrix3x3 & cr_Matrix);
	inline friend const Float Norm(const Matrix3x3 & cr_Matrix);
	inline friend const Float NormSquare(const Matrix3x3 & cr_Matrix);
	inline friend const Float Trace(const Matrix3x3 & cr_Matrix);


	inline const Matrix3x3 operator+ (const Matrix3x3& crMatrix);
	inline const Matrix3x3 operator- (const Matrix3x3& crMatrix);
	inline const Matrix3x3 operator* (const Matrix3x3& crMatrix);
	inline void operator=(const Matrix3x3& crMatrix);

// +---------
// | Unary Operator
// +---------
	inline void operator-();

// +---------
// | Inner operators
// +---------
	inline void operator+=(const Matrix3x3& crMatrix);
	inline void operator-=(const Matrix3x3& crMatrix);
	inline void operator*=(const Matrix3x3& crMatrix);


// +---------
// | Matrix operators with Vectors
// +---------
	inline const Vector3D operator*(const Vector3D& crVector) const; 


// +---------
// | Matrix operators with Floats
// +---------
	inline const Matrix3x3 operator*(const Float& crFloat); 
	inline friend const Matrix3x3 operator*(const Matrix3x3& crMatrix, const Float& crFloat); 
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

	inline void SetScale(const Float& ScaleX, const Float &ScaleY, const Float ScaleZ);
	inline void PreScale(const Float& ScaleX, const Float &ScaleY, const Float ScaleZ);
	inline void PostScale(const Float& ScaleX, const Float &ScaleY, const Float ScaleZ);


// +---------
// | Cast to Quaternion
// +---------
	inline operator const Quaternion (void);

// +---------
// | Cast To Matrix3x4
// +---------
	inline operator const Matrix3x4 (void);

// +---------
// | Cast To Matrix4x4
// +---------
	inline operator const Matrix4x4 (void);

private:
	static Matrix3x3 ms_Matrix;
	static Float ms_Float;
};

#endif

