inline Matrix3x4::Matrix3x4(const Float& e00, const Float& e01, const Float& e02,
				 const Float& e10, const Float& e11, const Float& e12,
				 const Float& e20, const Float& e21, const Float& e22,
				 const Float& e30, const Float& e31, const Float& e32)
{
	e[0][0] = e00; e[0][1] = e01; e[0][2] = e02;
	e[1][0] = e10; e[1][1] = e11; e[1][2] = e12;
	e[2][0] = e20; e[2][1] = e21; e[2][2] = e22;
	e[3][0] = e30; e[3][1] = e31; e[3][2] = e32;
}


// ******************************
// * Copy constructor
// *-----------------------------
// ******************************

inline Matrix3x4::Matrix3x4(const Matrix3x4& crMatrix)
{
    memcpy(e,crMatrix.e,sizeof(Matrix3x4));
};

// ******************************
// * Constructor with a Quaternion and a Vector3D
// ******************************

inline Matrix3x4::Matrix3x4(const Quaternion& q, const Vector3D& p)
{
    Set(q, p);
};

inline Matrix3x4::Matrix3x4(const Vector3D& vx, const Vector3D& vy, const Vector3D& vz, const Point3D& pos)
{
	e[0][0] = vx.x; e[0][1] = vx.y; e[0][2] = vx.z;
	e[1][0] = vy.x; e[1][1] = vy.y; e[1][2] = vy.z;
	e[2][0] = vz.x; e[2][1] = vz.y; e[2][2] = vz.z;
	e[3][0] = pos.x; e[3][1] = pos.y; e[3][2] = pos.z;
	
}

inline void Matrix3x4::Set(const Quaternion& q)
{
	Float dx = 2 * q.V.x;
	Float dy = 2 * q.V.y;
	Float dz = 2 * q.V.z;
    Float xx = dx * q.V.x;
	Float xy = dx * q.V.y;
	Float xz = dx * q.V.z;
	Float xw = dx * q.w;
	Float yy = dy * q.V.y;
	Float yz = dy * q.V.z;
	Float yw = dy * q.w;
	Float zz = dz * q.V.z;
	Float zw = dz * q.w;
	
	e[0][0]  = 1 - ( yy + zz );
	e[1][0]  =     ( xy - zw );
	e[2][0]  =     ( xz + yw );
	
	e[0][1]  =     ( xy + zw );
	e[1][1]  = 1 - ( xx + zz );
	e[2][1]  =     ( yz - xw );
	
	e[0][2]  =     ( xz - yw );
	e[1][2]  =     ( yz + xw );
	e[2][2]  = 1 - ( xx + yy );	
	
	e[3][0]  = 0;
	e[3][1]  = 0;
	e[3][2]  = 0;
};

inline void Matrix3x4::Set(const Quaternion& q, const Point3D& p)
{
	Float dx = 2 * q.V.x;
	Float dy = 2 * q.V.y;
	Float dz = 2 * q.V.z;
    Float xx = dx * q.V.x;
	Float xy = dx * q.V.y;
	Float xz = dx * q.V.z;
	Float xw = dx * q.w;
	Float yy = dy * q.V.y;
	Float yz = dy * q.V.z;
	Float yw = dy * q.w;
	Float zz = dz * q.V.z;
	Float zw = dz * q.w;
	
	e[0][0]  = 1 - ( yy + zz );
	e[1][0]  =     ( xy - zw );
	e[2][0]  =     ( xz + yw );
	
	e[0][1]  =     ( xy + zw );
	e[1][1]  = 1 - ( xx + zz );
	e[2][1]  =     ( yz - xw );
	
	e[0][2]  =     ( xz - yw );
	e[1][2]  =     ( yz + xw );
	e[2][2]  = 1 - ( xx + yy );	
	
	e[3][0]  = p.x;
	e[3][1]  = p.y;
	e[3][2]  = p.z;
};

// ******************************
// * SetIdentity
// ******************************
inline void Matrix3x4::SetIdentity()
{
    e[0][0] = e[1][1] = e[2][2] = 1.0;
	e[1][0] = e[2][0] = e[3][0] = e[0][1] = e[2][1] =e[3][1] = e[0][2] = e[1][2] = e[3][2] = 0.0;
};

inline const Matrix3x4 Inv(const Matrix3x4& cr_Matrix)
{
	Matrix3x4 m;
    Float t4 = cr_Matrix.e[0][0]*cr_Matrix.e[1][1];
    Float t6 = cr_Matrix.e[0][0]*cr_Matrix.e[1][2];
    Float t8 = cr_Matrix.e[0][1]*cr_Matrix.e[1][0];
    Float t10 = cr_Matrix.e[0][1]*cr_Matrix.e[1][2];
    Float t12 = cr_Matrix.e[0][2]*cr_Matrix.e[1][0];
    Float t14 = cr_Matrix.e[0][2]*cr_Matrix.e[1][1];
    Float t17 = 1/( t4*cr_Matrix.e[2][2]-t6*cr_Matrix.e[2][1]-t8*cr_Matrix.e[2][2]+
                    t10*cr_Matrix.e[2][0]+t12*cr_Matrix.e[2][1]-t14*cr_Matrix.e[2][0]);
    Float t20 = cr_Matrix.e[1][2]*cr_Matrix.e[2][0];
    Float t23 = cr_Matrix.e[1][0]*cr_Matrix.e[2][1];
    Float t24 = cr_Matrix.e[1][1]*cr_Matrix.e[2][0];
    Float t43 = cr_Matrix.e[0][2]*cr_Matrix.e[2][0];
    Float t46 = cr_Matrix.e[0][0]*cr_Matrix.e[2][1];
    Float t47 = cr_Matrix.e[0][1]*cr_Matrix.e[2][0];
    Float t51 = cr_Matrix.e[0][0]*cr_Matrix.e[3][1];
    Float t54 = cr_Matrix.e[0][1]*cr_Matrix.e[3][0];
    Float t57 = cr_Matrix.e[0][2]*cr_Matrix.e[3][0];

    m.e[0][0] = (cr_Matrix.e[1][1]*cr_Matrix.e[2][2]-cr_Matrix.e[1][2]*cr_Matrix.e[2][1])*t17;
    m.e[1][0] = -(cr_Matrix.e[1][0]*cr_Matrix.e[2][2]-t20)*t17;
    m.e[2][0] = (t23-t24)*t17;
    m.e[3][0] = -(t23*cr_Matrix.e[3][2]-cr_Matrix.e[1][0]*cr_Matrix.e[3][1]*cr_Matrix.e[2][2]
                         -t24*cr_Matrix.e[3][2]+cr_Matrix.e[1][1]*cr_Matrix.e[3][0]*cr_Matrix.e[2][2]
                         +t20*cr_Matrix.e[3][1]-cr_Matrix.e[1][2]*cr_Matrix.e[3][0]*cr_Matrix.e[2][1])*t17;
    m.e[0][1] = -(cr_Matrix.e[0][1]*cr_Matrix.e[2][2]-cr_Matrix.e[0][2]*cr_Matrix.e[2][1])*t17;
    m.e[1][1] = (cr_Matrix.e[0][0]*cr_Matrix.e[2][2]-t43)*t17;
    m.e[2][1] = -(t46-t47)*t17;
    m.e[3][1] = (t46*cr_Matrix.e[3][2]-t51*cr_Matrix.e[2][2]-t47*cr_Matrix.e[3][2]
                        +t54*cr_Matrix.e[2][2]+t43*cr_Matrix.e[3][1]-t57*cr_Matrix.e[2][1])*t17;
    m.e[0][2] = (t10-t14)*t17;
    m.e[1][2] = -(t6-t12)*t17;
    m.e[2][2] = (t4-t8)*t17;
    m.e[3][2] = -(t4*cr_Matrix.e[3][2]-t51*cr_Matrix.e[1][2]-t8*cr_Matrix.e[3][2]
                         +t54*cr_Matrix.e[1][2]+t12*cr_Matrix.e[3][1]-t57*cr_Matrix.e[1][1])*t17;

    return m;
};



// +---------
// | Calc the determinant 
// +---------
inline const Float Det(const Matrix3x4& cr_Matrix)
{
	return (cr_Matrix.e[0][0]*(cr_Matrix.e[1][1]*cr_Matrix.e[2][2]-cr_Matrix.e[1][2]*cr_Matrix.e[2][1])
			+cr_Matrix.e[0][1]*(cr_Matrix.e[1][2]*cr_Matrix.e[2][0]-cr_Matrix.e[1][0]*cr_Matrix.e[2][2])
			+cr_Matrix.e[0][2]*(cr_Matrix.e[1][0]*cr_Matrix.e[2][1]-cr_Matrix.e[1][1]*cr_Matrix.e[2][0]));
}

inline const Float Norm(const Matrix3x4 & cr_Matrix)
{
	return sqrt(NormSquare(cr_Matrix));
}

inline const Float NormSquare(const Matrix3x4 & cr_Matrix)
{
	return (cr_Matrix.e[0][0]*cr_Matrix.e[0][0] + cr_Matrix.e[0][1]*cr_Matrix.e[0][1] + cr_Matrix.e[0][2]*cr_Matrix.e[0][2]
   		                + cr_Matrix.e[1][0]*cr_Matrix.e[1][0] + cr_Matrix.e[1][1]*cr_Matrix.e[1][1] + cr_Matrix.e[1][2]*cr_Matrix.e[1][2]
		                + cr_Matrix.e[2][0]*cr_Matrix.e[2][0] + cr_Matrix.e[2][1]*cr_Matrix.e[2][1] + cr_Matrix.e[2][2]*cr_Matrix.e[2][2]
		                + cr_Matrix.e[3][0]*cr_Matrix.e[3][0] + cr_Matrix.e[3][1]*cr_Matrix.e[3][1] + cr_Matrix.e[3][2]*cr_Matrix.e[3][2]
                        + (static_cast<Float>(1.0)));
}

inline const Float Trace(const Matrix3x4 & cr_Matrix)
{
	return (cr_Matrix.e[0][0] + cr_Matrix.e[1][1] + cr_Matrix.e[2][2] + (static_cast<Float>(1.0)));
}	

inline const Matrix3x4 Matrix3x4::operator+ (const Matrix3x4& crMatrix) const
{
	Matrix3x4 m;
	m.e[0][0] = e[0][0] + crMatrix.e[0][0];
	m.e[0][1] = e[0][1] + crMatrix.e[0][1];
	m.e[0][2] = e[0][2] + crMatrix.e[0][2];
	m.e[1][0] = e[1][0] + crMatrix.e[1][0];
	m.e[1][1] = e[1][1] + crMatrix.e[1][1];
	m.e[1][2] = e[1][2] + crMatrix.e[1][2];
	m.e[2][0] = e[2][0] + crMatrix.e[2][0];
	m.e[2][1] = e[2][1] + crMatrix.e[2][1];
	m.e[2][2] = e[2][2] + crMatrix.e[2][2];
	m.e[3][0] = e[3][0] + crMatrix.e[3][0];
	m.e[3][1] = e[3][1] + crMatrix.e[3][1];
	m.e[3][2] = e[3][2] + crMatrix.e[3][2];
	return m;
};

inline const Matrix3x4 Matrix3x4::operator- (const Matrix3x4& crMatrix) const
{
	Matrix3x4 m;
    m.e[0][0] = e[0][0] - crMatrix.e[0][0];
	m.e[0][1] = e[0][1] - crMatrix.e[0][1];
	m.e[0][2] = e[0][2] - crMatrix.e[0][2];
	m.e[1][0] = e[1][0] - crMatrix.e[1][0];
	m.e[1][1] = e[1][1] - crMatrix.e[1][1];
	m.e[1][2] = e[1][2] - crMatrix.e[1][2];
	m.e[2][0] = e[2][0] - crMatrix.e[2][0];
	m.e[2][1] = e[2][1] - crMatrix.e[2][1];
	m.e[2][2] = e[2][2] - crMatrix.e[2][2];
	m.e[3][0] = e[3][0] - crMatrix.e[3][0];
	m.e[3][1] = e[3][1] - crMatrix.e[3][1];
	m.e[3][2] = e[3][2] - crMatrix.e[3][2];
	return m;
};



inline void Matrix3x4::operator=(const Matrix3x4& crMatrix)
{
    e[0][0] = crMatrix.e[0][0];
    e[0][1] = crMatrix.e[0][1];
    e[0][2] = crMatrix.e[0][2];

    e[1][0] = crMatrix.e[1][0];
    e[1][1] = crMatrix.e[1][1];
    e[1][2] = crMatrix.e[1][2];

    e[2][0] = crMatrix.e[2][0];
    e[2][1] = crMatrix.e[2][1];
    e[2][2] = crMatrix.e[2][2];

    e[3][0] = crMatrix.e[3][0];
    e[3][1] = crMatrix.e[3][1];
    e[3][2] = crMatrix.e[3][2];
};


// +---------
// | Inner operators
// +---------
inline void Matrix3x4::operator+=(const Matrix3x4& crMatrix)
{
    e[0][0] += crMatrix.e[0][0];
    e[0][1] += crMatrix.e[0][1];
    e[0][2] += crMatrix.e[0][2];

    e[1][0] += crMatrix.e[1][0];
    e[1][1] += crMatrix.e[1][1];
    e[1][2] += crMatrix.e[1][2];

    e[2][0] += crMatrix.e[2][0];
    e[2][1] += crMatrix.e[2][1];
    e[2][2] += crMatrix.e[2][2];

    e[3][0] += crMatrix.e[3][0];
    e[3][1] += crMatrix.e[3][1];
    e[3][2] += crMatrix.e[3][2];
};

inline void Matrix3x4::operator-=(const Matrix3x4& crMatrix)
{
    e[0][0] -= crMatrix.e[0][0];
    e[0][1] -= crMatrix.e[0][1];
    e[0][2] -= crMatrix.e[0][2];

    e[1][0] -= crMatrix.e[1][0];
    e[1][1] -= crMatrix.e[1][1];
    e[1][2] -= crMatrix.e[1][2];

    e[2][0] -= crMatrix.e[2][0];
    e[2][1] -= crMatrix.e[2][1];
    e[2][2] -= crMatrix.e[2][2];

    e[3][0] -= crMatrix.e[3][0];
    e[3][1] -= crMatrix.e[3][1];
    e[3][2] -= crMatrix.e[3][2];
};

inline const Matrix3x4 Matrix3x4::operator* (const Matrix3x4& m) const
{
	Matrix3x4 tmat;
    tmat.e[0][0] = e[0][0]*m.e[0][0] + e[1][0]*m.e[0][1] + e[2][0]*m.e[0][2];
    tmat.e[1][0] = e[0][0]*m.e[1][0] + e[1][0]*m.e[1][1] + e[2][0]*m.e[1][2];
    tmat.e[2][0] = e[0][0]*m.e[2][0] + e[1][0]*m.e[2][1] + e[2][0]*m.e[2][2];
    tmat.e[3][0] = e[0][0]*m.e[3][0] + e[1][0]*m.e[3][1] + e[2][0]*m.e[3][2] + e[3][0];
    tmat.e[0][1] = e[0][1]*m.e[0][0] + e[1][1]*m.e[0][1] + e[2][1]*m.e[0][2];
    tmat.e[1][1] = e[0][1]*m.e[1][0] + e[1][1]*m.e[1][1] + e[2][1]*m.e[1][2];
    tmat.e[2][1] = e[0][1]*m.e[2][0] + e[1][1]*m.e[2][1] + e[2][1]*m.e[2][2];
    tmat.e[3][1] = e[0][1]*m.e[3][0] + e[1][1]*m.e[3][1] + e[2][1]*m.e[3][2] + e[3][1];
    tmat.e[0][2] = e[0][2]*m.e[0][0] + e[1][2]*m.e[0][1] + e[2][2]*m.e[0][2];
    tmat.e[1][2] = e[0][2]*m.e[1][0] + e[1][2]*m.e[1][1] + e[2][2]*m.e[1][2];
    tmat.e[2][2] = e[0][2]*m.e[2][0] + e[1][2]*m.e[2][1] + e[2][2]*m.e[2][2];
    tmat.e[3][2] = e[0][2]*m.e[3][0] + e[1][2]*m.e[3][1] + e[2][2]*m.e[3][2] + e[3][2];
    return tmat;
};

inline void Matrix3x4::operator*=(const Matrix3x4& m)
{
	Float t1, t2;
                  e[3][0] = e[0][0]*m.e[3][0] + e[1][0]*m.e[3][1] + e[2][0]*m.e[3][2] + e[3][0];
    t1 = e[0][0]; e[0][0] =      t1*m.e[0][0] + e[1][0]*m.e[0][1] + e[2][0]*m.e[0][2];
    t2 = e[1][0]; e[1][0] =      t1*m.e[1][0] +      t2*m.e[1][1] + e[2][0]*m.e[1][2];
                  e[2][0] =      t1*m.e[2][0] +      t2*m.e[2][1] + e[2][0]*m.e[2][2];
    
                  e[3][1] = e[0][1]*m.e[3][0] + e[1][1]*m.e[3][1] + e[2][1]*m.e[3][2] + e[3][1];
    t1 = e[0][1]; e[0][1] =      t1*m.e[0][0] + e[1][1]*m.e[0][1] + e[2][1]*m.e[0][2];
    t2 = e[1][1]; e[1][1] =      t1*m.e[1][0] +      t2*m.e[1][1] + e[2][1]*m.e[1][2];
                  e[2][1] =      t1*m.e[2][0] +      t2*m.e[2][1] + e[2][1]*m.e[2][2];
    
                  e[3][2] = e[0][2]*m.e[3][0] + e[1][2]*m.e[3][1] + e[2][2]*m.e[3][2] + e[3][2];
    t1 = e[0][2]; e[0][2] =      t1*m.e[0][0] + e[1][2]*m.e[0][1] + e[2][2]*m.e[0][2];
    t2 = e[1][2]; e[1][2] =      t1*m.e[1][0] +      t2*m.e[1][1] + e[2][2]*m.e[1][2];
                  e[2][2] =      t1*m.e[2][0] +      t2*m.e[2][1] + e[2][2]*m.e[2][2];
};

void Matrix3x4::PostMultiply(const Matrix3x4& m)
{
	Float a, b;
	a = e[0][0]; b = e[0][1];
	e[0][0] = m.e[0][0] * a + m.e[1][0] * b + m.e[2][0] * e[0][2];
	e[0][1] = m.e[0][1] * a + m.e[1][1] * b + m.e[2][1] * e[0][2];
	e[0][2] = m.e[0][2] * a + m.e[1][2] * b + m.e[2][2] * e[0][2];
	a = e[1][0]; b = e[1][1];
	e[1][0] = m.e[0][0] * a + m.e[1][0] * b + m.e[2][0] * e[1][2];
	e[1][1] = m.e[0][1] * a + m.e[1][1] * b + m.e[2][1] * e[1][2];
	e[1][2] = m.e[0][2] * a + m.e[1][2] * b + m.e[2][2] * e[1][2];
	a = e[2][0]; b = e[2][1];
	e[2][0] = m.e[0][0] * a + m.e[1][0] * b + m.e[2][0] * e[2][2];
	e[2][1] = m.e[0][1] * a + m.e[1][1] * b + m.e[2][1] * e[2][2];
	e[2][2] = m.e[0][2] * a + m.e[1][2] * b + m.e[2][2] * e[2][2];
	a = e[3][0]; b = e[3][1];
	e[3][0] = m.e[0][0] * a + m.e[1][0] * b + m.e[2][0] * e[3][2] + m.e[3][0];
	e[3][1] = m.e[0][1] * a + m.e[1][1] * b + m.e[2][1] * e[3][2] + m.e[3][1];
	e[3][2] = m.e[0][2] * a + m.e[1][2] * b + m.e[2][2] * e[3][2] + m.e[3][2];
}

void Matrix3x4::PreMultiply(const Matrix3x4& m)
{
	Float a, b;
	a = e[0][0]; b = e[1][0];
	e[3][0] = a * m.e[3][0] + b * m.e[3][1] + e[2][0] * m.e[3][2] + e[3][0];
	e[0][0] = a * m.e[0][0] + b * m.e[0][1] + e[2][0] * m.e[0][2];
	e[1][0] = a * m.e[1][0] + b * m.e[1][1] + e[2][0] * m.e[1][2];
	e[2][0] = a * m.e[2][0] + b * m.e[2][1] + e[2][0] * m.e[2][2];
	a = e[0][1]; b = e[1][1];
	e[3][1] = a * m.e[3][0] + b * m.e[3][1] + e[2][1] * m.e[3][2] + e[3][1];
	e[0][1] = a * m.e[0][0] + b * m.e[0][1] + e[2][1] * m.e[0][2];
	e[1][1] = a * m.e[1][0] + b * m.e[1][1] + e[2][1] * m.e[1][2];
	e[2][1] = a * m.e[2][0] + b * m.e[2][1] + e[2][1] * m.e[2][2];
	a = e[0][2]; b = e[1][2];
	e[3][2] = a * m.e[3][0] + b * m.e[3][1] + e[2][2] * m.e[3][2] + e[3][2];
	e[0][2] = a * m.e[0][0] + b * m.e[0][1] + e[2][2] * m.e[0][2];
	e[1][2] = a * m.e[1][0] + b * m.e[1][1] + e[2][2] * m.e[1][2];
	e[2][2] = a * m.e[2][0] + b * m.e[2][1] + e[2][2] * m.e[2][2];
}


// +---------
// | Matrix operators with Vectors
// +---------
const Vector3D Matrix3x4::operator*(const Vector3D& cr_Vector) const
{
    return Vector3D( e[0][0]*cr_Vector.x + e[1][0]*cr_Vector.y + e[2][0]*cr_Vector.z,
		e[0][1]*cr_Vector.x + e[1][1]*cr_Vector.y + e[2][1]*cr_Vector.z,
		e[0][2]*cr_Vector.x + e[1][2]*cr_Vector.y + e[2][2]*cr_Vector.z );
}; 

const Point3D Matrix3x4::operator*(const Point3D& cr_Point) const
{
    return Point3D( e[0][0]*cr_Point.x + e[1][0]*cr_Point.y + e[2][0]*cr_Point.z + e[3][0],
				    e[0][1]*cr_Point.x + e[1][1]*cr_Point.y + e[2][1]*cr_Point.z + e[3][1],
					e[0][2]*cr_Point.x + e[1][2]*cr_Point.y + e[2][2]*cr_Point.z + e[3][2] );
};

inline void Matrix3x4::TransformPoints(Point3D* tab, int count) const
{
	assert(tab);
	Float a, b;
	Point3D* endtab = tab + count;
	for (; tab < endtab; tab++)
	{
		a = tab->x; b = tab->y;
		tab->x = a * e[0][0] + b * e[1][0] + tab->z * e[2][0] + e[3][0];
		tab->y = a * e[0][1] + b * e[1][1] + tab->z * e[2][1] + e[3][1];
		tab->z = a * e[0][2] + b * e[1][2] + tab->z * e[2][2] + e[3][2];
	}
}

inline void Matrix3x4::TransformVectors(Vector3D* tab, int count) const
{
	assert(tab);
	Float a, b;
	Vector3D* endtab = tab + count;
	for (; tab < endtab; tab++)
	{
		a = tab->x; b = tab->y;
		tab->x = a * e[0][0] + b * e[1][0] + tab->z * e[2][0];
		tab->y = a * e[0][1] + b * e[1][1] + tab->z * e[2][1];
		tab->z = a * e[0][2] + b * e[1][2] + tab->z * e[2][2];
	}
}



// +---------
// | Matrix operators with Floats
// +---------
inline const Matrix3x4 Matrix3x4::operator*(const Float& crFloat)
{
	return Matrix3x4(e[0][0]*crFloat, e[0][1]*crFloat, e[0][2]*crFloat, e[1][0]*crFloat,
		e[1][1]*crFloat, e[1][2]*crFloat, e[2][0]*crFloat, e[2][1]*crFloat, e[2][2]*crFloat
		, e[3][0]*crFloat, e[3][1]*crFloat, e[3][2]*crFloat);
}; 

inline const Matrix3x4 operator*(const Matrix3x4& crMatrix,const Float& crFloat)
{
	Matrix3x4 m;
    m.e[0][0] = crMatrix.e[0][0]*crFloat;
    m.e[0][1] = crMatrix.e[0][1]*crFloat;
    m.e[0][2] = crMatrix.e[0][2]*crFloat;

    m.e[1][0] = crMatrix.e[1][0]*crFloat;
    m.e[1][1] = crMatrix.e[1][1]*crFloat;
    m.e[1][2] = crMatrix.e[1][2]*crFloat;

    m.e[2][0] = crMatrix.e[2][0]*crFloat;
    m.e[2][1] = crMatrix.e[2][1]*crFloat;
    m.e[2][2] = crMatrix.e[2][2]*crFloat;

    m.e[3][0] = crMatrix.e[3][0]*crFloat;
    m.e[3][1] = crMatrix.e[3][1]*crFloat;
    m.e[3][2] = crMatrix.e[3][2]*crFloat;
    return m;
}; 

inline void Matrix3x4::operator*=(const Float& crFloat)
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

    e[3][0] *= crFloat;
    e[3][1] *= crFloat;
    e[3][2] *= crFloat;
};

// +---------
// | Operators specific to transformation matrices
// +---------
inline void Matrix3x4::SetRotationX(const Float& Angle)
{
/*
                            [1    0    0     0]
                            [                 ]
                            [0    c    -s    0]
                      Rx := [                 ]
                            [0    s    c     0]
                            [                 ]
                            [0    0    0     1]


*/

	Float COS = cos(Angle);
	Float SIN = sin(Angle);
	e[0][0] = 1.0; e[1][0] = 0.0; e[2][0] = 0.0; e[3][0] = 0.0;
	e[0][1] = 0.0; e[1][1] = COS; e[2][1] =-SIN; e[3][1] = 0.0;
	e[0][2] = 0.0; e[1][2] = SIN; e[2][2] = COS; e[3][2] = 0.0;
};

inline void Matrix3x4::SetRotationY(const Float& Angle)
{
/*
                            [c     0    s    0]
                            [                 ]
                            [0     1    0    0]
                      Ry := [                 ]
                            [-s    0    c    0]
                            [                 ]
                            [0     0    0    1]
*/

	Float COS = cos(Angle);
	Float SIN = sin(Angle);
	e[0][0] = COS; e[1][0] = 0.0; e[2][0] = SIN; e[3][0] = 0.0;
	e[0][1] = 0.0; e[1][1] = 1.0; e[2][1] = 0.0; e[3][1] = 0.0;
	e[0][2] =-SIN; e[1][2] = 0.0; e[2][2] = COS; e[3][2] = 0.0;
};

inline void Matrix3x4::SetRotationZ(const Float& Angle)
{
/*

                            [c    -s    0    0]
                            [                 ]
                            [s    c     0    0]
                      Rz := [                 ]
                            [0    0     1    0]
                            [                 ]
                            [0    0     0    1]
*/

	Float COS = cos(Angle);
	Float SIN = sin(Angle);
	e[0][0] = COS; e[1][0] =-SIN; e[2][0] = 0.0; e[3][0] = 0.0;
	e[0][1] = SIN; e[1][1] = COS; e[2][1] = 0.0; e[3][1] = 0.0;
	e[0][2] = 0.0; e[1][2] = 0.0; e[2][2] = 1.0; e[3][2] = 0.0;
};


// +---------
// | PreRotation around X    =    (*this) * Matrix_Rotation_Around_X
// +---------
inline void Matrix3x4::PreRotateX(const Float& Angle)
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
inline void Matrix3x4::PreRotateY(const Float& Angle)
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
inline void Matrix3x4::PreRotateZ(const Float& Angle)
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
inline void Matrix3x4::PostRotateX(const Float& Angle)
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
inline void Matrix3x4::PostRotateY(const Float& Angle)
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
inline void Matrix3x4::PostRotateZ(const Float& Angle)
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
// | Do not Touche The translation Vector
// +---------
inline void Matrix3x4::SetRotationXYZ(const Float& AngleX,const Float& AngleY,const Float& AngleZ)
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
// | Do not Touche The Translation Vector
// +---------
inline void Matrix3x4::SetRotationZYX(const Float& AngleX,const Float& AngleY,const Float& AngleZ)
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
inline void Matrix3x4::PreRotateZYX(const Float& AngleX,const Float& AngleY,const Float& AngleZ)
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
inline void Matrix3x4::PreRotateXYZ(const Float& AngleX,const Float& AngleY,const Float& AngleZ)
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
inline void Matrix3x4::PostRotateZYX(const Float& AngleX,const Float& AngleY,const Float& AngleZ)
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
inline void Matrix3x4::PostRotateXYZ(const Float& AngleX,const Float& AngleY,const Float& AngleZ)
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


// +---------
// | Sets The Scale to Sx,Sy,Sz
// | Do not change the translation part of the matrix
// +---------
inline void Matrix3x4::SetScale(const Float& ScaleX, const Float &ScaleY, const Float &ScaleZ)
{
	e[0][0] = ScaleX;
	e[1][1] = ScaleY;
	e[2][2] = ScaleZ;
	e[0][1] = e[0][2] = e[1][0] = e[1][2] = e[2][0] = e[2][1] = (static_cast<Float> (0.0));
}


// +---------
// | PreScale   =  (*this) * Scale_Matrix
// +---------
inline void Matrix3x4::PreScale(const Float& ScaleX, const Float &ScaleY, const Float &ScaleZ)
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
inline void Matrix3x4::PostScale(const Float& ScaleX, const Float &ScaleY, const Float &ScaleZ)
{
	e[0][0] = ScaleX * e[0][0];
	e[0][1] = ScaleY * e[0][1];
	e[0][2] = ScaleZ * e[0][2];
	e[1][0] = ScaleX * e[1][0];
	e[1][1] = ScaleY * e[1][1];
	e[1][2] = ScaleZ * e[1][2];
	e[2][0] = ScaleX * e[2][0];
	e[2][1] = ScaleY * e[2][1];
	e[2][2] = ScaleZ * e[2][2];
	e[3][0] = ScaleX * e[3][0];
	e[3][1] = ScaleY * e[3][1];
	e[3][2] = ScaleZ * e[3][2];
}


inline void Matrix3x4::SetTranslation(const Vector3D& Translation)
{
    e[3][0] = Translation.x;
    e[3][1] = Translation.y;
    e[3][2] = Translation.z;
};

// +---------
// | PreRotation around X    =   (*this) * Matrix_Rotation_Around_X
// +---------
inline void Matrix3x4::PreTranslate(const Vector3D& Translation)
{
	e[3][0] += e[0][0]*Translation.x+e[1][0]*Translation.y+e[2][0]*Translation.z;
	e[3][1] += e[0][1]*Translation.x+e[1][1]*Translation.y+e[2][1]*Translation.z;
	e[3][2] += e[0][2]*Translation.x+e[1][2]*Translation.y+e[2][2]*Translation.z;
};


// +---------
// | PostRotation around X    =   Matrix_Rotation_Around_X * (*this)
// +---------
inline void Matrix3x4::PostTranslate(const Vector3D& Translation)
{
    e[3][0] += Translation.x;
    e[3][1] += Translation.y;
    e[3][2] += Translation.z;
};

inline Matrix3x4::operator const Quaternion (void)
{
	Quaternion::ms_Quaternion = Quaternion(*this);

    return(Quaternion::ms_Quaternion);
}

inline const Vector3D Matrix3x4::GetTranslation() const
{
	return (Vector3D&) (*(Vector3D*)(&(e[3][0])));
}

inline Matrix3x4::operator const Matrix3x3& (void)
{
	return (Matrix3x3&) (*reinterpret_cast<Matrix3x3*> (this));
}
