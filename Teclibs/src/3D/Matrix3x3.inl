// ******************************
// * Default constructor
// *-----------------------------
// ******************************
Matrix3x3::Matrix3x3()
{
	NULL;
}


// ******************************
// * Copy constructor
// *-----------------------------
// ******************************
#include <string.h>

inline Matrix3x3::Matrix3x3(const Matrix3x3& cr_Matrix)
{
	memcpy(e,cr_Matrix.e,sizeof(Matrix3x3));
}


// ******************************
// * Constructor with a Quaternion
// ******************************
inline Matrix3x3::Matrix3x3(const Quaternion& cr_Quaternion)
{
	Float xx = cr_Quaternion.V.x * cr_Quaternion.V.x;
	Float xy = cr_Quaternion.V.x * cr_Quaternion.V.y;
	Float xz = cr_Quaternion.V.x * cr_Quaternion.V.z;
	Float xw = cr_Quaternion.V.x * cr_Quaternion.w;

	Float yy = cr_Quaternion.V.y * cr_Quaternion.V.y;
	Float yz = cr_Quaternion.V.y * cr_Quaternion.V.z;
	Float yw = cr_Quaternion.V.y * cr_Quaternion.w;
	Float zz = cr_Quaternion.V.z * cr_Quaternion.V.z;
	Float zw = cr_Quaternion.V.z * cr_Quaternion.w;

		e[0][0]  = 1 - 2 * ( yy + zz );
		e[1][0]  =     2 * ( xy - zw );
		e[2][0]  =     2 * ( xz + yw );

		e[0][1]  =     2 * ( xy + zw );
		e[1][1]  = 1 - 2 * ( xx + zz );
		e[2][1]  =     2 * ( yz - xw );

		e[0][2]  =     2 * ( xz - yw );
		e[1][2]  =     2 * ( yz + xw );
		e[2][2]  = 1 - 2 * ( xx + yy );	
}


// ******************************
// * SetIdentity
// ******************************
inline void Matrix3x3::SetIdentity()
{
	e[0][0] = e[1][1] = e[2][2] = 1.0;
	e[1][0] = e[2][0] = e[0][1] = e[2][1] = e[0][2] = e[1][2] = 0.0;
}


inline const Matrix3x3 Inv(const Matrix3x3 & cr_Matrix)
{
	Float t4 = cr_Matrix.e[0][0]*cr_Matrix.e[1][1];
	Float t6 = cr_Matrix.e[0][0]*cr_Matrix.e[2][1];
	Float t8 = cr_Matrix.e[1][0]*cr_Matrix.e[0][1];
	Float t10 = cr_Matrix.e[2][0]*cr_Matrix.e[0][1];
	Float t12 = cr_Matrix.e[1][0]*cr_Matrix.e[0][2];
	Float t14 = cr_Matrix.e[2][0]*cr_Matrix.e[0][2];
	Float t17 = (static_cast<Float>(1.0))/(t4*cr_Matrix.e[2][2]-t6*cr_Matrix.e[1][2]-t8*cr_Matrix.e[2][2]+t10*cr_Matrix.e[1][2]+t12*cr_Matrix.e[2][1]-t14*cr_Matrix.e[1][1]);
	Matrix3x3::ms_Matrix.e[0][0] = (cr_Matrix.e[1][1]*cr_Matrix.e[2][2]-cr_Matrix.e[2][1]*cr_Matrix.e[1][2])*t17;
	Matrix3x3::ms_Matrix.e[0][1] = -(cr_Matrix.e[0][1]*cr_Matrix.e[2][2]-cr_Matrix.e[2][1]*cr_Matrix.e[0][2])*t17;
	Matrix3x3::ms_Matrix.e[0][2] = (cr_Matrix.e[0][1]*cr_Matrix.e[1][2]-cr_Matrix.e[1][1]*cr_Matrix.e[0][2])*t17;
	Matrix3x3::ms_Matrix.e[1][0] = -(cr_Matrix.e[1][0]*cr_Matrix.e[2][2]-cr_Matrix.e[2][0]*cr_Matrix.e[1][2])*t17;
	Matrix3x3::ms_Matrix.e[1][1] = (cr_Matrix.e[0][0]*cr_Matrix.e[2][2]-t14)*t17;
	Matrix3x3::ms_Matrix.e[1][2] = -(cr_Matrix.e[0][0]*cr_Matrix.e[1][2]-t12)*t17;
	Matrix3x3::ms_Matrix.e[2][0] = (cr_Matrix.e[1][0]*cr_Matrix.e[2][1]-cr_Matrix.e[2][0]*cr_Matrix.e[1][1])*t17;
	Matrix3x3::ms_Matrix.e[2][1] = -(t6-t10)*t17;
	Matrix3x3::ms_Matrix.e[2][2] = (t4-t8)*t17;
	return Matrix3x3::ms_Matrix;
}

inline const Float Det(const Matrix3x3& cr_Matrix)
{
	Matrix3x3::ms_Float =  cr_Matrix.e[0][0]*cr_Matrix.e[1][1]*cr_Matrix.e[2][2]
			-cr_Matrix.e[0][0]*cr_Matrix.e[2][1]*cr_Matrix.e[1][2]
			-cr_Matrix.e[0][1]*cr_Matrix.e[1][0]*cr_Matrix.e[2][2]
			+cr_Matrix.e[0][1]*cr_Matrix.e[2][0]*cr_Matrix.e[1][2]
			+cr_Matrix.e[0][2]*cr_Matrix.e[1][0]*cr_Matrix.e[2][1]
			-cr_Matrix.e[0][2]*cr_Matrix.e[2][0]*cr_Matrix.e[1][1];
	return Matrix3x3::ms_Float;
}

inline const Float Norm(const Matrix3x3 & cr_Matrix)
{
	return sqrt(NormSquare(cr_Matrix));
}

inline const Float NormSquare(const Matrix3x3 & cr_Matrix)
{
	Matrix3x3::ms_Float =  cr_Matrix.e[0][0]*cr_Matrix.e[0][0] + cr_Matrix.e[0][1]*cr_Matrix.e[0][1] + cr_Matrix.e[0][2]*cr_Matrix.e[0][2]
   		 + cr_Matrix.e[1][0]*cr_Matrix.e[1][0] + cr_Matrix.e[1][1]*cr_Matrix.e[1][1] + cr_Matrix.e[1][2]*cr_Matrix.e[1][2]
		 + cr_Matrix.e[2][0]*cr_Matrix.e[2][0] + cr_Matrix.e[2][1]*cr_Matrix.e[2][1] + cr_Matrix.e[2][2]*cr_Matrix.e[2][2];
	return Matrix3x3::ms_Float;
}

inline const Float Trace(const Matrix3x3 & cr_Matrix)
{
	Matrix3x3::ms_Float =  cr_Matrix.e[0][0] + cr_Matrix.e[1][1] + cr_Matrix.e[2][2];
	return Matrix3x3::ms_Float;
}


inline const Matrix3x3 Matrix3x3::operator+ (const Matrix3x3& crMatrix)
{
	ms_Matrix.e[0][0] = e[0][0] + crMatrix.e[0][0];
	ms_Matrix.e[0][1] = e[0][1] + crMatrix.e[0][1];
	ms_Matrix.e[0][2] = e[0][2] + crMatrix.e[0][2];
	ms_Matrix.e[1][0] = e[1][0] + crMatrix.e[1][0];
	ms_Matrix.e[1][1] = e[1][1] + crMatrix.e[1][1];
	ms_Matrix.e[1][2] = e[1][2] + crMatrix.e[1][2];
	ms_Matrix.e[2][0] = e[2][0] + crMatrix.e[2][0];
	ms_Matrix.e[2][1] = e[2][1] + crMatrix.e[2][1];
	ms_Matrix.e[2][2] = e[2][2] + crMatrix.e[2][2];
}

inline const Matrix3x3 Matrix3x3::operator- (const Matrix3x3& crMatrix)
{
	ms_Matrix.e[0][0] = e[0][0] - crMatrix.e[0][0];
	ms_Matrix.e[0][1] = e[0][1] - crMatrix.e[0][1];
	ms_Matrix.e[0][2] = e[0][2] - crMatrix.e[0][2];
	ms_Matrix.e[1][0] = e[1][0] - crMatrix.e[1][0];
	ms_Matrix.e[1][1] = e[1][1] - crMatrix.e[1][1];
	ms_Matrix.e[1][2] = e[1][2] - crMatrix.e[1][2];
	ms_Matrix.e[2][0] = e[2][0] - crMatrix.e[2][0];
	ms_Matrix.e[2][1] = e[2][1] - crMatrix.e[2][1];
	ms_Matrix.e[2][2] = e[2][2] - crMatrix.e[2][2];
}


inline const Matrix3x3 Matrix3x3::operator* (const Matrix3x3& crMatrix)
{
	ms_Matrix.e[0][0] = e[0][0]*crMatrix.e[0][0]+e[1][0]*crMatrix.e[0][1]+e[2][0]*crMatrix.e[0][2];
	ms_Matrix.e[0][1] = e[0][1]*crMatrix.e[0][0]+e[1][1]*crMatrix.e[0][1]+e[2][1]*crMatrix.e[0][2];
	ms_Matrix.e[0][2] = e[0][2]*crMatrix.e[0][0]+e[1][2]*crMatrix.e[0][1]+e[2][2]*crMatrix.e[0][2];
	ms_Matrix.e[1][0] = e[0][0]*crMatrix.e[1][0]+e[1][0]*crMatrix.e[1][1]+e[2][0]*crMatrix.e[1][2];
	ms_Matrix.e[1][1] = e[0][1]*crMatrix.e[1][0]+e[1][1]*crMatrix.e[1][1]+e[2][1]*crMatrix.e[1][2];
	ms_Matrix.e[1][2] = e[0][2]*crMatrix.e[1][0]+e[1][2]*crMatrix.e[1][1]+e[2][2]*crMatrix.e[1][2];
	ms_Matrix.e[2][0] = e[0][0]*crMatrix.e[2][0]+e[1][0]*crMatrix.e[2][1]+e[2][0]*crMatrix.e[2][2];
	ms_Matrix.e[2][1] = e[0][1]*crMatrix.e[2][0]+e[1][1]*crMatrix.e[2][1]+e[2][1]*crMatrix.e[2][2];
	ms_Matrix.e[2][2] = e[0][2]*crMatrix.e[2][0]+e[1][2]*crMatrix.e[2][1]+e[2][2]*crMatrix.e[2][2];
	return ms_Matrix;
}


inline void Matrix3x3::operator=(const Matrix3x3& crMatrix)
{
	memcpy(e,crMatrix.e,9*sizeof(Float));
}

// +---------
// | Unary Operator
// +---------
inline void Matrix3x3::operator-()
{
	e[0][0] = -e[0][0];
	e[0][1] = -e[1][0];
	e[0][2] = -e[2][0];
	e[1][0] = -e[0][1];
	e[1][1] = -e[1][1];
	e[1][2] = -e[2][1];
	e[2][0] = -e[0][2];
	e[2][1] = -e[1][2];
	e[2][2] = -e[2][2];
}

// +---------
// | Inner operators
// +---------
inline void Matrix3x3::operator+=(const Matrix3x3& crMatrix)
{
	e[0][0] += crMatrix.e[0][0];
	e[0][1] += crMatrix.e[1][0];
	e[0][2] += crMatrix.e[2][0];
	e[1][0] += crMatrix.e[0][1];
	e[1][1] += crMatrix.e[1][1];
	e[1][2] += crMatrix.e[2][1];
	e[2][0] += crMatrix.e[0][2];
	e[2][1] += crMatrix.e[1][2];
	e[2][2] += crMatrix.e[2][2];
}


inline void Matrix3x3::operator-=(const Matrix3x3& crMatrix)
{
	e[0][0] -= crMatrix.e[0][0];
	e[0][1] -= crMatrix.e[1][0];
	e[0][2] -= crMatrix.e[2][0];
	e[1][0] -= crMatrix.e[0][1];
	e[1][1] -= crMatrix.e[1][1];
	e[1][2] -= crMatrix.e[2][1];
	e[2][0] -= crMatrix.e[0][2];
	e[2][1] -= crMatrix.e[1][2];
	e[2][2] -= crMatrix.e[2][2];
}

inline void Matrix3x3::operator*=(const Matrix3x3& crMatrix)
{
	ms_Matrix.e[0][0] = e[0][0]*crMatrix.e[0][0]+e[1][0]*crMatrix.e[0][1]+e[2][0]*crMatrix.e[0][2];
	ms_Matrix.e[0][1] = e[0][1]*crMatrix.e[0][0]+e[1][1]*crMatrix.e[0][1]+e[2][1]*crMatrix.e[0][2];
	ms_Matrix.e[0][2] = e[0][2]*crMatrix.e[0][0]+e[1][2]*crMatrix.e[0][1]+e[2][2]*crMatrix.e[0][2];
	ms_Matrix.e[1][0] = e[0][0]*crMatrix.e[1][0]+e[1][0]*crMatrix.e[1][1]+e[2][0]*crMatrix.e[1][2];
	ms_Matrix.e[1][1] = e[0][1]*crMatrix.e[1][0]+e[1][1]*crMatrix.e[1][1]+e[2][1]*crMatrix.e[1][2];
	ms_Matrix.e[1][2] = e[0][2]*crMatrix.e[1][0]+e[1][2]*crMatrix.e[1][1]+e[2][2]*crMatrix.e[1][2];
	ms_Matrix.e[2][0] = e[0][0]*crMatrix.e[2][0]+e[1][0]*crMatrix.e[2][1]+e[2][0]*crMatrix.e[2][2];
	ms_Matrix.e[2][1] = e[0][1]*crMatrix.e[2][0]+e[1][1]*crMatrix.e[2][1]+e[2][1]*crMatrix.e[2][2];
	ms_Matrix.e[2][2] = e[0][2]*crMatrix.e[2][0]+e[1][2]*crMatrix.e[2][1]+e[2][2]*crMatrix.e[2][2];
	memcpy(e,ms_Matrix.e,9*sizeof(Float));
}


// +---------
// | Matrix operators with Vectors
// +---------
inline const Vector3D Matrix3x3::operator*(const Vector3D& crVector) const
{
	return Vector3D( e[0][0]*crVector.x + e[1][0]*crVector.y + e[2][0]*crVector.z,
		e[0][1]*crVector.x + e[1][1]*crVector.y + e[2][1]*crVector.z,
		e[0][2]*crVector.x + e[1][2]*crVector.y + e[2][2]*crVector.z );
}

// +---------
// | Matrix operators with Floats
// +---------
inline const Matrix3x3 Matrix3x3::operator*(const Float& crFloat)
{
	ms_Matrix.e[0][0] *= crFloat;
	ms_Matrix.e[0][1] *= crFloat;
	ms_Matrix.e[0][2] *= crFloat;
	ms_Matrix.e[1][0] *= crFloat;
	ms_Matrix.e[1][1] *= crFloat;
	ms_Matrix.e[1][2] *= crFloat;
	ms_Matrix.e[2][0] *= crFloat;
	ms_Matrix.e[2][1] *= crFloat;
	ms_Matrix.e[2][2] *= crFloat;
	return ms_Matrix;
}

inline const Matrix3x3 operator*(const Matrix3x3& crMatrix, const Float& crFloat)
{
	Matrix3x3::ms_Matrix.e[0][0] = crFloat * crMatrix.e[0][0];
	Matrix3x3::ms_Matrix.e[0][1] = crFloat * crMatrix.e[1][0];
	Matrix3x3::ms_Matrix.e[0][2] = crFloat * crMatrix.e[2][0];
	Matrix3x3::ms_Matrix.e[1][0] = crFloat * crMatrix.e[0][1];
	Matrix3x3::ms_Matrix.e[1][1] = crFloat * crMatrix.e[1][1];
	Matrix3x3::ms_Matrix.e[1][2] = crFloat * crMatrix.e[2][1];
	Matrix3x3::ms_Matrix.e[2][0] = crFloat * crMatrix.e[0][2];
	Matrix3x3::ms_Matrix.e[2][1] = crFloat * crMatrix.e[1][2];
	Matrix3x3::ms_Matrix.e[2][2] = crFloat * crMatrix.e[2][2];
	return Matrix3x3::ms_Matrix;
}

inline void Matrix3x3::operator*=(const Float& crFloat)
{
	e[0][0] *= crFloat;
	e[0][1] *= crFloat;
	e[0][2] *= crFloat;
	e[1][0] *= crFloat;
	e[1][1] *= crFloat;
	e[1][2] *= crFloat;
	e[2][0] *= crFloat;
	e[2][1] *= crFloat;
	e[2][2] *= crFloat;
}

// +---------------------------------------------------
// | Set The Matrix to a Rotation Around X
// |			| 1     0            0	   |
// |			| 0 cos(Angle) -sin(Angle) |
// |			| 0 sin(Angle)  cos(Angle) |
// +---------------------------------------------------
inline void Matrix3x3::SetRotationX(const Float& Angle)
{
	Float COS = cos(Angle);
	Float SIN = sin(Angle);
	e[0][0] = 1.0; e[1][0] = 0.0; e[2][0] = 0.0; 
	e[0][1] = 0.0; e[1][1] = COS; e[2][1] =-SIN; 
	e[0][2] = 0.0; e[1][2] = SIN; e[2][2] = COS; 
}


// +---------------------------------------------------
// | Set The Matrix to a rotation around Y
// |			| cos(Angle)  0 sin(Angle) |
// |			|     0       1     0      |
// |			| -sin(Angle) 0 cos(Angle) |
// +---------------------------------------------------
inline void Matrix3x3::SetRotationY(const Float& Angle)
{
	Float COS = cos(Angle);
	Float SIN = sin(Angle);
	e[0][0] = COS; e[1][0] = 0.0; e[2][0] = SIN; 
	e[0][1] = 0.0; e[1][1] = 1.0; e[2][1] = 0.0; 
	e[0][2] =-SIN; e[1][2] = 0.0; e[2][2] = COS; 
}


// +---------------------------------------------------
// | Set The Matrix to a rotation around Z
// |			| cos(Angle)  -sin(Angle)  0|
// |			| sin(Angle)  cos(Angle)   0|
// |			| 0           0            1|
// +---------------------------------------------------
inline void Matrix3x3::SetRotationZ(const Float& Angle)
{
	Float COS = cos(Angle);
	Float SIN = sin(Angle);
	e[0][0] = COS; e[1][0] =-SIN; e[2][0] = 0.0; 
	e[0][1] = SIN; e[1][1] = COS; e[2][1] = 0.0; 
	e[0][2] = 0.0; e[1][2] = 0.0; e[2][2] = 1.0; 
}


// +---------
// | PreRotation around X    =    (*this) * Matrix_Rotation_Around_X
// +---------
inline void Matrix3x3::PreRotateX(const Float& Angle)
{
	Float COS = cos(Angle);
	Float SIN = sin(Angle);
	Float tmp10 = e[1][0]*COS+e[2][0]*SIN;
	Float tmp11 = e[1][1]*COS+e[2][1]*SIN;
	Float tmp12 = e[1][2]*COS+e[2][2]*SIN;
	e[2][0] = -e[1][0]*SIN+e[2][0]*COS;
	e[2][1] = -e[1][1]*SIN+e[2][1]*COS;
	e[2][2] = -e[1][2]*SIN+e[2][2]*COS;
	e[1][0] = tmp10;
	e[1][1] = tmp11;
	e[1][2] = tmp12;
}


// +---------
// | PreRotation around Y    =    (*this) * Matrix_Rotation_Around_Y
// +---------
inline void Matrix3x3::PreRotateY(const Float& Angle)
{
	Float COS = cos(Angle);
	Float SIN = sin(Angle);
	Float tmp00 = e[0][0]*COS-e[2][0]*SIN;
	Float tmp01 = e[0][1]*COS-e[2][1]*SIN;
	Float tmp02 = e[0][2]*COS-e[2][2]*SIN;
	e[2][0] = e[0][0]*SIN+e[2][0]*COS;
	e[2][1] = e[0][1]*SIN+e[2][1]*COS;
	e[2][2] = e[0][2]*SIN+e[2][2]*COS;
	e[0][0] = tmp00;
	e[0][1] = tmp01;
	e[0][2] = tmp02;
}

// +---------
// | PreRotation around Z    =    (*this) * Matrix_Rotation_Around_Z
// +---------
inline void Matrix3x3::PreRotateZ(const Float& Angle)
{
	Float COS = cos(Angle);
	Float SIN = sin(Angle);
	Float tmp00 = e[0][0]*COS+e[1][0]*SIN;
	Float tmp01 = e[0][1]*COS+e[1][1]*SIN;
	Float tmp02 = e[0][2]*COS+e[1][2]*SIN;
	e[1][0] = -e[0][0]*SIN+e[1][0]*COS;
	e[1][1] = -e[0][1]*SIN+e[1][1]*COS;
	e[1][2] = -e[0][2]*SIN+e[1][2]*COS;
	e[0][0] = tmp00;
	e[0][1] = tmp01;
	e[0][2] = tmp02;
}


// +---------
// | PostRotation around X    =   Matrix_Rotation_Around_X * (*this)
// +---------
inline void Matrix3x3::PostRotateX(const Float& Angle)
{
	Float COS = cos(Angle);
	Float SIN = sin(Angle);
	Float tmp01 = COS*e[0][1]-SIN*e[0][2];
	e[0][2] = SIN*e[0][1]+COS*e[0][2];
	Float tmp11 = COS*e[1][1]-SIN*e[1][2];
	e[1][2] = SIN*e[1][1]+COS*e[1][2];
	Float tmp21 = COS*e[2][1]-SIN*e[2][2];
	e[2][2] = SIN*e[2][1]+COS*e[2][2];
	e[0][1] = tmp01;
	e[1][1] = tmp11;
	e[2][1] = tmp21;
}


// +---------
// | PostRotation around Y    =   Matrix_Rotation_Around_Y * (*this)
// +---------
inline void Matrix3x3::PostRotateY(const Float& Angle)
{
	Float COS = cos(Angle);
	Float SIN = sin(Angle);
	Float tmp00 = COS*e[0][0]+SIN*e[0][2];
	e[0][2] = -SIN*e[0][0]+COS*e[0][2];
	Float tmp10 = COS*e[1][0]+SIN*e[1][2];
	e[1][2] = -SIN*e[1][0]+COS*e[1][2];
	Float tmp20 = COS*e[2][0]+SIN*e[2][2];
	e[2][2] = -SIN*e[2][0]+COS*e[2][2];
	e[0][0] = tmp00;
	e[1][0] = tmp10;
	e[2][0] = tmp20;
}

// +---------
// | PostRotation around Z    =  Matrix_Rotation_Around_Z * (*this)
// +---------
inline void Matrix3x3::PostRotateZ(const Float& Angle)
{
	Float COS = cos(Angle);
	Float SIN = sin(Angle);
	Float tmp00 = COS*e[0][0]-SIN*e[0][1];
	e[0][1] = SIN*e[0][0]+COS*e[0][1];
	Float tmp10 = COS*e[1][0]-SIN*e[1][1];
	e[1][1] = SIN*e[1][0]+COS*e[1][1];
	Float tmp20 = COS*e[2][0]-SIN*e[2][1];
	e[2][1] = SIN*e[2][0]+COS*e[2][1];
	e[0][0] = tmp00;
	e[1][0] = tmp10;
	e[2][0] = tmp20;
}


// +---------
// | Matrix = Rotation_Around_Z * Rotation_Around_Y * Rotation_Around_X
// +---------
inline void Matrix3x3::SetRotationXYZ(const Float& AngleX,const Float& AngleY,const Float& AngleZ)
{
	Float CX = cos(AngleX);
	Float SX = sin(AngleX);
	Float CY = cos(AngleY);
	Float SY = sin(AngleY);
	Float CZ = cos(AngleZ);
	Float SZ = sin(AngleZ);
	Float t2 = CZ*SY;
	Float t10 = SZ*SY;
	e[0][0] = CZ*CY;
	e[0][1] = t2*SX-SZ*CX;
	e[0][2] = t2*CX+SZ*SX;
	e[1][0] = SZ*CY;
	e[1][1] = t10*SX+CZ*CX;
	e[1][2] = t10*CX-CZ*SX;
	e[2][0] = -SY;
	e[2][1] = CY*SX;
	e[2][2] = CY*CX;
}


// +---------
// | Matrix = Rotation_Around_X * Rotation_Around_Y * Rotation_Around_Z
// +---------
inline void Matrix3x3::SetRotationZYX(const Float& AngleX,const Float& AngleY,const Float& AngleZ)
{
	Float CX = cos(AngleX);
	Float SX = sin(AngleX);
	Float CY = cos(AngleY);
	Float SY = sin(AngleY);
	Float CZ = cos(AngleZ);
	Float SZ = sin(AngleZ);
	Float t4 = CZ*SY;
	Float t8 = SZ*SY;
	e[0][0] = CZ*CY;
	e[0][1] = -SZ*CY;
	e[0][2] = SY;
	e[1][0] = SZ*CX+t4*SX;
	e[1][1] = CZ*CX-t8*SX;
	e[1][2] = -CY*SX;
	e[2][0] = SZ*SX-t4*CX;
	e[2][1] = CZ*SX+t8*CX;
	e[2][2] = CY*CX;
}


// +---------
// | PreRotation around Z, then around Y then around X    =    (*this) * Matrix_Rotation_Around_X * Matrix_Rotation_Around_Y * Matrix_Rotation_Z
// +---------
inline void Matrix3x3::PreRotateZYX(const Float& AngleX,const Float& AngleY,const Float& AngleZ)
{
	Float CX = cos(AngleX);
	Float SX = sin(AngleX);
	Float CY = cos(AngleY);
	Float SY = sin(AngleY);
	Float CZ = cos(AngleZ);
	Float SZ = sin(AngleZ);
	Float t4 = CZ*SY;
	Float t6 = SZ*CX+t4*SX;
	Float t10 = SZ*SX-t4*CX;
	Float t26 = SZ*SY;
	Float t28 = CZ*CX-t26*SX;
	Float t32 = CZ*SX+t26*CX;
	Float tmp00 = e[0][0]*CZ*CY+e[1][0]*t6+e[2][0]*t10;
	Float tmp01 = e[0][1]*CZ*CY+e[1][1]*t6+e[2][1]*t10;
	Float tmp02 = e[0][2]*CZ*CY+e[1][2]*t6+e[2][2]*t10;
	Float tmp10 = -e[0][0]*SZ*CY+e[1][0]*t28+e[2][0]*t32;
	Float tmp11 = -e[0][1]*SZ*CY+e[1][1]*t28+e[2][1]*t32;
	Float tmp12 = -e[0][2]*SZ*CY+e[1][2]*t28+e[2][2]*t32;
	e[2][0] = SY*e[0][0]-e[1][0]*CY*SX+e[2][0]*CY*CX;
	e[2][1] = SY*e[0][1]-e[1][1]*CY*SX+e[2][1]*CY*CX;
	e[2][2] = SY*e[0][2]-e[1][2]*CY*SX+e[2][2]*CY*CX;
	e[0][0] = tmp00;
	e[0][1] = tmp01;
	e[0][2] = tmp02;
	e[1][0] = tmp10;
	e[1][1] = tmp11;
	e[1][2] = tmp12;
}


// +---------
// | PreRotation around X, then around Y then around Z    =    (*this) * Matrix_Rotation_Around_Z * Matrix_Rotation_Around_Y * Matrix_Rotation_X
// +---------
inline void Matrix3x3::PreRotateXYZ(const Float& AngleX,const Float& AngleY,const Float& AngleZ)
{
	Float CX = cos(AngleX);
	Float SX = sin(AngleX);
	Float CY = cos(AngleY);
	Float SY = sin(AngleY);
	Float CZ = cos(AngleZ);
	Float SZ = sin(AngleZ);
	Float t19 = CZ*SY;
	Float t22 = t19*SX-SZ*CX;
	Float t24 = SZ*SY;
	Float t27 = t24*SX+CZ*CX;
	Float t29 = e[2][0]*CY;
	Float t34 = e[2][1]*CY;
	Float t39 = e[2][2]*CY;
	Float t44 = t19*CX+SZ*SX;
	Float t48 = t24*CX-CZ*SX;
	Float tmp00 = e[0][0]*CZ*CY+e[1][0]*SZ*CY-e[2][0]*SY;
	Float tmp01 = e[0][1]*CZ*CY+e[1][1]*SZ*CY-e[2][1]*SY;
	Float tmp02 = e[0][2]*CZ*CY+e[1][2]*SZ*CY-e[2][2]*SY;
	Float tmp10 = e[0][0]*t22+e[1][0]*t27+t29*SX;
	Float tmp11 = e[0][1]*t22+e[1][1]*t27+t34*SX;
	Float tmp12 = e[0][2]*t22+e[1][2]*t27+t39*SX;
	e[2][0] = e[0][0]*t44+e[1][0]*t48+t29*CX;
	e[2][1] = e[0][1]*t44+e[1][1]*t48+t34*CX;
	e[2][2] = e[0][2]*t44+e[1][2]*t48+t39*CX;
	e[0][0] = tmp00;
	e[0][1] = tmp01;
	e[0][2] = tmp02;
	e[1][0] = tmp10;
	e[1][1] = tmp11;
	e[1][2] = tmp12;
}



// +---------
// | PostRotation around Z, then around Y then around X    =    Matrix_Rotation_Around_X * Matrix_Rotation_Around_Y * Matrix_Rotation_Z * (*this)
// +---------
inline void Matrix3x3::PostRotateZYX(const Float& AngleX,const Float& AngleY,const Float& AngleZ)
{
	Float CX = cos(AngleX);
	Float SX = sin(AngleX);
	Float CY = cos(AngleY);
	Float SY = sin(AngleY);
	Float CZ = cos(AngleZ);
	Float SZ = sin(AngleZ);
	Float t3 = CZ*e[0][0]-SZ*e[0][1];
	Float t9 = SZ*e[0][0]+CZ*e[0][1];
	Float t13 = -SY*t3+CY*e[0][2];
	Float t21 = CZ*e[1][0]-SZ*e[1][1];
	Float t27 = SZ*e[1][0]+CZ*e[1][1];
	Float t31 = -SY*t21+CY*e[1][2];
	Float t39 = CZ*e[2][0]-SZ*e[2][1];
	Float t45 = SZ*e[2][0]+CZ*e[2][1];
	Float t49 = -SY*t39+e[2][2]*CY;
	e[0][0] = CY*t3+SY*e[0][2];
	e[0][1] = CX*t9-SX*t13;
	e[0][2] = SX*t9+CX*t13;
	e[1][0] = CY*t21+SY*e[1][2];
	e[1][1] = CX*t27-SX*t31;
	e[1][2] = SX*t27+CX*t31;
	e[2][0] = CY*t39+e[2][2]*SY;
	e[2][1] = CX*t45-SX*t49;
	e[2][2] = SX*t45+CX*t49;
}


// +---------
// | PostRotation around X, then around Y then around Z    =  Matrix_Rotation_Around_Z * Matrix_Rotation_Around_Y * Matrix_Rotation_X * (*this)
// +---------
inline void Matrix3x3::PostRotateXYZ(const Float& AngleX,const Float& AngleY,const Float& AngleZ)
{
	Float CX = cos(AngleX);
	Float SX = sin(AngleX);
	Float CY = cos(AngleY);
	Float SY = sin(AngleY);
	Float CZ = cos(AngleZ);
	Float SZ = sin(AngleZ);
	Float t4 = SX*e[0][1]+CX*e[0][2];
	Float t6 = CY*e[0][0]+SY*t4;
	Float t10 = CX*e[0][1]-SX*e[0][2];
	Float t22 = SX*e[1][1]+CX*e[1][2];
	Float t24 = e[1][0]*CY+SY*t22;
	Float t28 = CX*e[1][1]-SX*e[1][2];
	Float t40 = SX*e[2][1]+CX*e[2][2];
	Float t42 = e[2][0]*CY+SY*t40;
	Float t46 = CX*e[2][1]-SX*e[2][2];

	e[0][2] = -SY*e[0][0]+CY*t4;
	e[0][0] = CZ*t6-SZ*t10;
	e[0][1] = SZ*t6+CZ*t10;

	e[1][2] = -e[1][0]*SY+CY*t22;
	e[1][0] = CZ*t24-SZ*t28;
	e[1][1] = SZ*t24+CZ*t28;

	e[2][2] = -e[2][0]*SY+CY*t40;
	e[2][0] = CZ*t42-SZ*t46;
	e[2][1] = SZ*t42+CZ*t46;
}

inline void Matrix3x3::SetScale(const Float& ScaleX, const Float &ScaleY, const Float ScaleZ)
{
	e[0][0] = ScaleX;
	e[1][1] = ScaleY;
	e[2][2] = ScaleZ;
	e[0][1] = e[0][2] = e[1][0] = e[1][2] = e[2][0] = e[2][1] = (static_cast<Float> (0.0));
}


// +---------
// | PreScale   =  (*this) * Scale_Matrix
// +---------
inline void Matrix3x3::PreScale(const Float& ScaleX, const Float &ScaleY, const Float ScaleZ)
{
	e[0][0] = e[0][0]*ScaleX;
	e[0][1] = e[0][1]*ScaleX;
	e[0][2] = e[0][2]*ScaleX;
	e[1][0] = e[1][0]*ScaleY;
	e[1][1] = e[1][1]*ScaleY;
	e[1][2] = e[1][2]*ScaleY;
	e[2][0] = e[2][0]*ScaleZ;
	e[2][1] = e[2][1]*ScaleZ;
	e[2][2] = e[2][2]*ScaleZ;
}


// +---------
// | PostScale   =  Scale_Matrix * (*this)
// +---------
inline void Matrix3x3::PostScale(const Float& ScaleX, const Float &ScaleY, const Float ScaleZ)
{
	e[0][0] = e[0][0]*ScaleX;
	e[0][1] = e[0][1]*ScaleY;
	e[0][2] = ScaleZ*e[0][2];
	e[1][0] = ScaleX*e[1][0];
	e[1][1] = e[1][1]*ScaleY;
	e[1][2] = ScaleZ*e[1][2];
	e[2][0] = ScaleX*e[2][0];
	e[2][1] = e[2][1]*ScaleY;
	e[2][2] = e[2][2]*ScaleZ;
}



// +---------
// | Cast from Quaternion
// +---------
inline Matrix3x3::operator const Quaternion (void)
{
	Quaternion::ms_Quaternion = Quaternion(*this);
	return Quaternion::ms_Quaternion;
}

inline Matrix3x3::operator const Matrix3x4 (void)
{
	Matrix3x4 m;
	memcpy(m.e,e,9*sizeof(Float));
	m.e[3][0] = 0.0;
	m.e[3][1] = 0.0;
	m.e[3][2] = 0.0;
	return m;
}

inline Matrix3x3::operator const Matrix4x4 (void)
{
	Matrix4x4::ms_Matrix.e[0][0] = e[0][0];
	Matrix4x4::ms_Matrix.e[0][1] = e[0][1];
	Matrix4x4::ms_Matrix.e[0][2] = e[0][2];
	Matrix4x4::ms_Matrix.e[0][3] = 0.0;
	Matrix4x4::ms_Matrix.e[1][0] = e[1][0];
	Matrix4x4::ms_Matrix.e[1][1] = e[1][1];
	Matrix4x4::ms_Matrix.e[1][2] = e[1][2];
	Matrix4x4::ms_Matrix.e[1][3] = 0.0;
	Matrix4x4::ms_Matrix.e[2][0] = e[2][0];
	Matrix4x4::ms_Matrix.e[2][1] = e[2][1];
	Matrix4x4::ms_Matrix.e[2][2] = e[2][2];
	Matrix4x4::ms_Matrix.e[2][3] = 0.0;
	Matrix4x4::ms_Matrix.e[3][0] = 0.0;
	Matrix4x4::ms_Matrix.e[3][1] = 0.0;
	Matrix4x4::ms_Matrix.e[3][2] = 0.0;
	Matrix4x4::ms_Matrix.e[3][3] = 1.0;
	return Matrix4x4::ms_Matrix;
}




