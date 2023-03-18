// **********************************************************************
// * FILE  : Tec3D.cpp
// * GROUP : TecLibs/3D
// *---------------------------------------------------------------------
// * PURPOSE : 3D classes
// * COMMENT : ...
// *---------------------------------------------------------------------
// * DATES     : 07/07/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************
#include "Tec3D.h"



// ----------------------------------------------------------------------
// +---------
// | Statics variables
// +---------

Vector4D    Vector4D::ms_Vector = Vector4D();

Quaternion  Quaternion::ms_Quaternion = Quaternion();
Float       Quaternion::ms_Float      = Float();

Matrix3x3   Matrix3x3::ms_Matrix = Matrix3x3();
Float       Matrix3x3::ms_Float  = Float();

Basis3D     Basis3D::ms_Basis = Basis3D();

Reference3D Reference3D::ms_Reference = Reference3D();
