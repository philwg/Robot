// **********************************************************************
// * FILE  : 3D.h
// * GROUP : TecLibs/3D
// *---------------------------------------------------------------------
// * PURPOSE : 3D classes
// * COMMENT : ...
// *---------------------------------------------------------------------
// * DATES     : 07/07/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************
#ifndef _3D_h_
#define _3D_h_



// ----------------------------------------------------------------------
// +---------
// | 3D section
// +---------

// General includes
#include "TecLibs.h"                // To be Tec
#include "TecMath.h"                // To use sqrt, cos, etc.

#ifdef TEC_USE_NAMESPACES
	namespace Tec3D {
#endif

// Forward declarations
class Vector3D;
class Point3D;
class Vector4D;
class Quaternion;
class Matrix3x3;
class Matrix3x4;
class Matrix4x4;
class Basis3D;
class Reference3D;

// Classes definitions
#include "3D/Vector3D.h"            // To use 3D vector
#include "3D/Point3D.h"             // To use 3D point
#include "3D/Vector4D.h"            // To use 4D vector (projective geometry)
#include "3D/Quaternion.h"          // To use quaternion
#include "3D/Matrix3x3.h"           // To use 3x3 matrix
#include "3D/Matrix3x4.h"           // To use 3x4 matrix
#include "3D/Matrix4x4.h"           // To use 4x4 matrix
#include "3D/Basis3D.h"             // To use 3D basis
#include "3D/Reference3D.h"         // To use 3D reference

// Classes implementations
#include "3D/Vector3D.inl"
#include "3D/Point3D.inl"
#include "3D/Vector4D.inl"
#include "3D/Quaternion.inl"
#include "3D/Matrix3x3.inl"
#include "3D/Matrix3x4.inl"
//#include "3D/Matrix4x4.inl"
#include "3D/Basis3D.inl"
#include "3D/Reference3D.inl"

#ifdef TEC_USE_NAMESPACES
	}

	typedef Tec3D::Vector3D		TecVector3D;
	typedef Tec3D::Point3D		TecPoint3D;
	typedef Tec3D::Vector4D		TecVector4D;
	typedef Tec3D::Quaternion	TecQuaternion;
	typedef Tec3D::Matrix3x3	TecMatrix3x3;
	typedef Tec3D::Matrix3x4	TecMatrix3x4;
	typedef Tec3D::Matrix4x4	TecMatrix4x4;
	typedef Tec3D::Basis3D		TecBasis3D;
	typedef Tec3D::Reference3D	TecReference3D;
	
	using namespace Tec3D;
#else
	typedef Vector3D	TecVector3D;
	typedef Point3D		TecPoint3D;
	typedef Vector4D	TecVector4D;
	typedef Quaternion	TecQuaternion;
	typedef Matrix3x3	TecMatrix3x3;
	typedef Matrix3x4	TecMatrix3x4;
	typedef Matrix4x4	TecMatrix4x4;
	typedef Basis3D		TecBasis3D;
	typedef Reference3D	TecReference3D;
#endif


#endif//_3D_h_
