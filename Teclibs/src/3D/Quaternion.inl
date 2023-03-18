// **********************************************************************
// * FILE  : Quaternion.inl
// * GROUP : Teclib/3D
// *---------------------------------------------------------------------
// * PURPOSE : Implementation of the inline methods found in the the quaternion class definition
// * COMMENT : Supposed to be included in the Quaternion.h file... Not to be use as this
// *---------------------------------------------------------------------
// * DATES     : 10/07/2000
// * AUTHORS   : Antoine Leclercq aleclercq@fr.infogrames.com
// * COPYRIGHT : (c) Infogrames/Teclab 2000
// **********************************************************************

inline Quaternion::Quaternion()
{
    NULL;
}

// +---------
// | Copy constructor
// +---------
inline Quaternion::Quaternion(const Quaternion& q)
{
	V = q.V;
	w = q.w;
}

// +---------
// | Constructor
// +---------
inline Quaternion::Quaternion(const Float& x, const Float& y, const Float& z, const Float& w)
{
	V.x = x;
	V.y = y;
	V.z = z;
	this->w = w;
}


// +---------
// | Constructor from a Matrix
// +---------
inline Quaternion::Quaternion(const Matrix3x3& crMatrix)
{
	// Calculate the trace of the matrix T from the equation:
	Float T = crMatrix.e[0][0] + crMatrix.e[1][1] + crMatrix.e[2][2] + 1;    // +1 from a 4x4 matrix


	if (T>=0.0f)
	{
		// The trace of the matrix is greater than 0
		Float S = 0.5f / sqrt(T);
		w = 0.25f / S;
		V.x = ( crMatrix.e[1][2] - crMatrix.e[2][1] ) * S;
		V.y = ( crMatrix.e[2][0] - crMatrix.e[0][2] ) * S;
		V.z = ( crMatrix.e[0][1] - crMatrix.e[1][0] ) * S;
	}
	else
	{
		// the trace of the matrix is less or equal to 0
		// so the result depends of which of the major diagonal has the greatest value
		if (crMatrix.e[0][0]>=crMatrix.e[1][1])
		{
			if (crMatrix.e[0][0]>=crMatrix.e[2][2])
			{
				// crMatrix.e[0][0] is the greatest				
				Float S  = sqrt( 1.0f + crMatrix.e[0][0] - crMatrix.e[1][1] - crMatrix.e[2][2] ) * 2.0f;
				V.x = 0.5f / S;
				V.y = (crMatrix.e[1][0] + crMatrix.e[0][1] ) / S;
				V.z = (crMatrix.e[2][0] + crMatrix.e[0][2] ) / S;
				w = (crMatrix.e[2][1] + crMatrix.e[1][2] ) / S;
			}
			else
			{
				// crMatrix.e[2][2] is the greatest
				Float S = sqrt( 1.0f + crMatrix.e[2][2] - crMatrix.e[0][0] - crMatrix.e[1][1] ) * 2.0f;
				V.x = (crMatrix.e[2][0] + crMatrix.e[0][2] ) / S;
				V.y = (crMatrix.e[2][1] + crMatrix.e[1][2] ) / S;
				V.z = 0.5f / S;
				w = (crMatrix.e[1][0] + crMatrix.e[0][1] ) / S;
			}
		}
		else
		{
			if (crMatrix.e[1][1]>=crMatrix.e[2][2])
			{
				// crMatrix.e[1][1] is the greatest
				Float S  = sqrt( 1.0f + crMatrix.e[1][1] - crMatrix.e[0][0] - crMatrix.e[2][2] ) * 2.0f;
				V.x = (crMatrix.e[1][0] + crMatrix.e[0][1] ) / S;
				V.y = 0.5f / S;
				V.z = (crMatrix.e[2][1] + crMatrix.e[1][2] ) / S;
				w = (crMatrix.e[2][0] + crMatrix.e[0][2] ) / S;
			}
			else
			{
				// crMatrix.e[2][2] is the greatest
				Float S = sqrt( 1.0f + crMatrix.e[2][2] - crMatrix.e[0][0] - crMatrix.e[1][1] ) * 2.0f;
				V.x = (crMatrix.e[2][0] + crMatrix.e[0][2] ) / S;
				V.y = (crMatrix.e[2][1] + crMatrix.e[1][2] ) / S;
				V.z = 0.5f / S;
				w = (crMatrix.e[1][0] + crMatrix.e[0][1] ) / S;
			}
		}
	}		// the trace is lower or equal to zero
}

// +---------
// | Constructor from a Matrix
// +---------
inline Quaternion::Quaternion(const Matrix3x4& crMatrix)
{
	// Calculate the trace of the matrix T from the equation:
	Float T = crMatrix.e[0][0] + crMatrix.e[1][1] + crMatrix.e[2][2] + 1;    // +1 from a 4x4 matrix


	if (T>=0.0f)
	{
		// The trace of the matrix is greater than 0
		Float S = 0.5f / sqrt(T);
		w = 0.25f / S;
		V.x = ( crMatrix.e[1][2] - crMatrix.e[2][1] ) * S;
		V.y = ( crMatrix.e[2][0] - crMatrix.e[0][2] ) * S;
		V.z = ( crMatrix.e[0][1] - crMatrix.e[1][0] ) * S;
	}
	else
	{
		// the trace of the matrix is less or equal to 0
		// so the result depends of which of the major diagonal has the greatest value
		if (crMatrix.e[0][0]>=crMatrix.e[1][1])
		{
			if (crMatrix.e[0][0]>=crMatrix.e[2][2])
			{
				// crMatrix.e[0][0] is the greatest				
				Float S  = sqrt( 1.0f + crMatrix.e[0][0] - crMatrix.e[1][1] - crMatrix.e[2][2] ) * 2.0f;
				V.x = 0.5f / S;
				V.y = (crMatrix.e[1][0] + crMatrix.e[0][1] ) / S;
				V.z = (crMatrix.e[2][0] + crMatrix.e[0][2] ) / S;
				w = (crMatrix.e[2][1] + crMatrix.e[1][2] ) / S;
			}
			else
			{
				// crMatrix.e[2][2] is the greatest
				Float S = sqrt( 1.0f + crMatrix.e[2][2] - crMatrix.e[0][0] - crMatrix.e[1][1] ) * 2.0f;
				V.x = (crMatrix.e[2][0] + crMatrix.e[0][2] ) / S;
				V.y = (crMatrix.e[2][1] + crMatrix.e[1][2] ) / S;
				V.z = 0.5f / S;
				w = (crMatrix.e[1][0] + crMatrix.e[0][1] ) / S;
			}
		}
		else
		{
			if (crMatrix.e[1][1]>=crMatrix.e[2][2])
			{
				// crMatrix.e[1][1] is the greatest
				Float S  = sqrt( 1.0f + crMatrix.e[1][1] - crMatrix.e[0][0] - crMatrix.e[2][2] ) * 2.0f;
				V.x = (crMatrix.e[1][0] + crMatrix.e[0][1] ) / S;
				V.y = 0.5f / S;
				V.z = (crMatrix.e[2][1] + crMatrix.e[1][2] ) / S;
				w = (crMatrix.e[2][0] + crMatrix.e[0][2] ) / S;
			}
			else
			{
				// crMatrix.e[2][2] is the greatest
				Float S = sqrt( 1.0f + crMatrix.e[2][2] - crMatrix.e[0][0] - crMatrix.e[1][1] ) * 2.0f;
				V.x = (crMatrix.e[2][0] + crMatrix.e[0][2] ) / S;
				V.y = (crMatrix.e[2][1] + crMatrix.e[1][2] ) / S;
				V.z = 0.5f / S;
				w = (crMatrix.e[1][0] + crMatrix.e[0][1] ) / S;
			}
		}
	}		// the trace is lower or equal to zero
}


// +---------
// | Copy
// +---------
inline void Quaternion::operator=(const Quaternion& q)
{
	V = q.V;
	w = q.w;
}

// +---------
// | Cast From a matrix 3x3
// +---------
inline Quaternion::operator const Matrix3x3 (void)
{
		// convert to a 3x3 matrix
	if (w==1.0f&&V.x==0.0f&&V.y==0.0f&&V.z==0.0f)
	{
		Matrix3x3::ms_Matrix.SetIdentity();
		return Matrix3x3::ms_Matrix;
	}

	Float xx = V.x * V.x;
	Float xy = V.x * V.y;
	Float xz = V.x * V.z;
	Float xw = V.x * w;

	Float yy = V.y * V.y;
	Float yz = V.y * V.z;
	Float yw = V.y * w;

	Float zz = V.z * V.z;
	Float zw = V.z * w;

	Matrix3x3::ms_Matrix.e[0][0]  = 1 - 2 * ( yy + zz );
	Matrix3x3::ms_Matrix.e[1][0]  =     2 * ( xy - zw );
	Matrix3x3::ms_Matrix.e[2][0]  =     2 * ( xz + yw );

	Matrix3x3::ms_Matrix.e[0][1]  =     2 * ( xy + zw );
	Matrix3x3::ms_Matrix.e[1][1]  = 1 - 2 * ( xx + zz );
	Matrix3x3::ms_Matrix.e[2][1]  =     2 * ( yz - xw );

	Matrix3x3::ms_Matrix.e[0][2]  =     2 * ( xz - yw );
	Matrix3x3::ms_Matrix.e[1][2]  =     2 * ( yz + xw );
	Matrix3x3::ms_Matrix.e[2][2]  = 1 - 2 * ( xx + yy );	

	return Matrix3x3::ms_Matrix;
}

// +---------
// | Cast From a matrix 3x4
// +---------
inline Quaternion::operator const Matrix3x4 (void)
{
	Matrix3x4 m; 

	if (w==1.0f&&V.x==0.0f&&V.y==0.0f&&V.z==0.0f)
	{
		m.SetIdentity();
		return m;
	}

    Float xs,ys,zs,wx,wy,wz,xx,xy,xz,yy,yz,zz;
	// optimised for unit quaternion STEPH
	
	xs = V.x + V.x;
    ys = V.y + V.y;
    zs = V.z + V.z;

	wx = w * xs;
    wy = w * ys;
    wz = w * zs;

	xx = V.x * xs;
    xy = V.x * ys;
    xz = V.x * zs;
	yy = V.y * ys;
    yz = V.y * zs;
    zz = V.z * zs;
	
	m.e[0][0] = 1.0f - (yy + zz);
	m.e[0][1] = xy - wz;
	m.e[0][2] = xz + wy;
	
	m.e[1][0] = xy + wz;
	m.e[1][1] = 1.0f - (xx + zz);
	m.e[1][2] = yz - wx;
	
	m.e[2][0] = xz - wy;
	m.e[2][1] = yz + wx;
	m.e[2][2] = 1.0f - (xx + yy);
	
	m.e[3][0] = 0.0f;
	m.e[3][1] = 0.0f;
	m.e[3][2] = 0.0f;

	return m;
}

// +---------
// | Set Identity
// +---------
inline void Quaternion::SetIdentity()
{
	w = 1;
	V.x = V.y = V.z = 0;

}

// +---------
// | Normalize the quaternion
// +---------
inline void Quaternion::Normalize()
{
	Float InvNorm = (static_cast<Float> (1.0))/Norm(*this);
	V*=InvNorm;
	w*=InvNorm;
}

// +---------
// | returns the norme of the quaternion
// +---------
inline const Float Norm(const Quaternion & cr_Quaternion)
{
	return sqrt(NormSquare(cr_Quaternion));
}


// +---------
// | returns the squarred Norm q.conjugate(q)  (((  conjugate(q) = (w,-v)   )))
// +---------
inline const Float NormSquare(const Quaternion & cr_Quaternion)
{
	Quaternion::ms_Float  = NormSquare(cr_Quaternion.V) + cr_Quaternion.w*cr_Quaternion.w;
	return Quaternion::ms_Float;
}


// +---------
// | Sets the quaternion for a rotation around X of an angle of cr_Angle
// +---------
inline void Quaternion::SetRotationX(const Float& cr_Angle)
{
	Quaternion q;
	w = cos(cr_Angle*0.5f);
	V.x = sin(cr_Angle*0.5f);
	V.y = V.z = 0;
}


// +---------
// | Sets the quaternion for a rotation around Y of an angle of cr_Angle
// +---------
inline void Quaternion::SetRotationY(const Float& cr_Angle)
{
	w = cos(cr_Angle*0.5f);
	V.y = sin(cr_Angle*0.5f);
	V.x = V.z = 0;
}

// +---------
// | Sets the quaternion for a rotation around Z of an angle of cr_Angle
// +---------
inline void Quaternion::SetRotationZ(const Float& cr_Angle)
{
	w = cos(cr_Angle*0.5f);
	V.z = sin(cr_Angle*0.5f);
	V.x = V.y = 0;
}


// +---------
// | Sets the quaternion for a rotation around a direction cr_Vector of an angle of cr_Angle
// +---------
inline void Quaternion::SetRotationU(const Vector3D& cr_Vector, const Float& cr_Angle)
{
	Float sin_a, cos_a;
	sin_a = sin( cr_Angle / 2 );
	cos_a = cos( cr_Angle / 2 );
    V.x	= cr_Vector.x * sin_a;
	V.y	= cr_Vector.y * sin_a;
	V.z	= cr_Vector.z * sin_a;
	w		= cos_a;
}


// +---------
// | unary -
// +---------
inline const Quaternion Quaternion::operator-()
{
	ms_Quaternion.V = -V;
	ms_Quaternion.w = -w;
	return ms_Quaternion;
}

// +---------
// | Multiplication of 2 quaternion (if they repesent a rotation, then this product
// | represents the composition of those 2 rotations)
// +---------
inline const Quaternion Quaternion::operator* (const Quaternion& cr_Quaternion) const
{
/*		Float a, b, c, d, e, f, g, h;
		a = (w   + V.x)*(cr_Quaternion.w   + cr_Quaternion.V.x);
		b = (V.z - V.y)*(cr_Quaternion.V.y - cr_Quaternion.V.z);
		c = (V.x - w  )*(cr_Quaternion.V.y - cr_Quaternion.V.z);
		d = (V.y + V.z)*(cr_Quaternion.V.x - cr_Quaternion.w  );
		e = (V.x + V.z)*(cr_Quaternion.V.x + cr_Quaternion.V.y);
		f = (V.x - V.z)*(cr_Quaternion.V.x - cr_Quaternion.V.y);
		g = (w   + V.y)*(cr_Quaternion.w   - cr_Quaternion.V.z);
		h = (w   - V.y)*(cr_Quaternion.w   + cr_Quaternion.V.z);
		ms_Quaternion.w = b + 0.5f*(- e - f + g + h);
		ms_Quaternion.V.x = a - 0.5f*(  e + f + g + h);
		ms_Quaternion.V.y = -c + 0.5f*(  e - f + g - h);
		ms_Quaternion.V.z = d + 0.5f*(  e - f- g+ h);
*/
	    ms_Quaternion.w     =   w   *   cr_Quaternion.w     -   V.x *   cr_Quaternion.V.x 
                            -   V.y *   cr_Quaternion.V.y   -   V.z *   cr_Quaternion.V.z;

	    ms_Quaternion.V.x   =   w   *   cr_Quaternion.V.x   +   V.x *   cr_Quaternion.w 
                            +   V.y *   cr_Quaternion.V.z   -   V.z *   cr_Quaternion.V.y;

	    ms_Quaternion.V.y   =   w   *   cr_Quaternion.V.y   +   V.y *   cr_Quaternion.w
                            +   V.z *   cr_Quaternion.V.x   -   V.x *   cr_Quaternion.V.z;

	    ms_Quaternion.V.z   =   w   *   cr_Quaternion.V.z   +   V.z *   cr_Quaternion.w 
                            +   V.x *   cr_Quaternion.V.y   -   V.y *   cr_Quaternion.V.x;
        
        return ms_Quaternion;
}

// +---------
// | Addition
// +---------
inline const Quaternion Quaternion::operator+ (const Quaternion& cr_Quaternion) const
{
	ms_Quaternion.w = w + cr_Quaternion.w;
	ms_Quaternion.V = V + cr_Quaternion.V;
	return ms_Quaternion;
}

// +---------
// | Substraction
// +---------
inline const Quaternion Quaternion::operator- (const Quaternion& cr_Quaternion) const
{
	ms_Quaternion.w = w - cr_Quaternion.w;
	ms_Quaternion.V = V - cr_Quaternion.V;
	return ms_Quaternion;
}


// +---------
// | multiply himself with ce_Quaternion
// +---------
inline const Quaternion& Quaternion::operator*= (const Quaternion& cr_Quaternion)
{

    (*this) = (*this) * cr_Quaternion;
	return (*this);
}

// +---------
// | Adds a quaternion to himself
// +---------
inline const Quaternion& Quaternion::operator+= (const Quaternion& cr_Quaternion)
{
	*this = (*this) + cr_Quaternion;
	return (*this);
}

// +---------
// | Substract a quaternion to Himself
// +---------
inline const Quaternion& Quaternion::operator-= (const Quaternion& cr_Quaternion)
{
	*this = (*this) - cr_Quaternion;
	return (*this);
}


// +---------
// | returns the inverse quaternion of cr_Quaternion ~~~~equilvalent to the conjugate of the quaternion
// +---------
inline const Quaternion Inv(const Quaternion& cr_Quaternion)
{
#ifdef _DEBUG
	if (abs(Norm(cr_Quaternion)-1.0f)>1e-6)
	{
		// The quaternion is supposed to be Normalized (i.e. Represents a Rotation) so
		// if its norm!=1.0 this quaternion does not represent a rotation....
		assert(0);
	}

#endif
	Quaternion::ms_Quaternion.V = -cr_Quaternion.V;
	Quaternion::ms_Quaternion.w = cr_Quaternion.w;
	return Quaternion::ms_Quaternion;
}

// +---------
// | Multiply a quaternion with  a Float
// +---------
inline const Quaternion Quaternion::operator* (const Float& cr_Float) const
{
	ms_Quaternion.V = cr_Float*V;
	ms_Quaternion.w = cr_Float*w;
	return ms_Quaternion;
}

// +---------
// | Multiply a Float with a Quaternion
// +---------
inline const Quaternion operator*(const Quaternion& cr_Quaternion, const Float& cr_Float)
{
	Quaternion::ms_Quaternion.V = cr_Float*cr_Quaternion.V;
	Quaternion::ms_Quaternion.w = cr_Float*cr_Quaternion.w;
	return Quaternion::ms_Quaternion;
}


// +---------
// | divise a Quaternion by a Float
// +---------
inline const Quaternion Quaternion::operator/ (const Float& cr_Float) const
{
	ms_Quaternion.V = V/cr_Float;
	ms_Quaternion.w = w/cr_Float;
	return ms_Quaternion;
}


// +---------
// | multiply himself with a Float
// +---------
inline const Quaternion& Quaternion::operator*= (const Float& cr_Float)
{
	V*=cr_Float;
	w*=cr_Float;
	return *this;
}


// +---------
// | divide himself by a Float
// +---------
inline const Quaternion& Quaternion::operator/= (const Float& cr_Float)
{
	V/=cr_Float;
	w/=cr_Float;
	return *this;
}


// +---------
// | Dot Product
// +---------
inline Float Dot(const Quaternion& cr_Quaternion1, const Quaternion& cr_Quaternion2)
{
	return Dot(cr_Quaternion1.V,cr_Quaternion2.V) + cr_Quaternion1.w*cr_Quaternion2.w;
}


// +---------
// | Spherical Interpolation ~ (1-cr_weight)*cr_Quaternion1 + cr_weight*cr_Quaternion2
// +---------
inline const Quaternion& Slerp(const Quaternion& cr_Quaternion1, const Quaternion& cr_Quaternion2, const Float& cr_weight)
{
/*		Float w = acos(Dot(cr_Quaternion1,cr_Quaternion2));
		float s_inv = (static_cast<Float>(1.0))/sin(w);
		Quaternion QuatTmp;
		QuatTmp = cr_Quaternion1*s_inv*sin((1-cr_weight)*w);
		Quaternion::ms_Quaternion = cr_Quaternion2;
		Quaternion::ms_Quaternion *= s_inv*sin(cr_weight*w);
		Quaternion::ms_Quaternion += QuatTmp;
		return Quaternion::ms_Quaternion;

*/
	Float omega,cosom,sinom,sclp,sclq;
	IntU32 i;

	Quaternion& result=Quaternion::ms_Quaternion;

    const Quaternion& p=cr_Quaternion1;
    const Quaternion& q=cr_Quaternion2;
    const Float& t=cr_weight;
	
    cosom = Dot(p,q);

	if (  cosom > (0.000001f-1.0f) )
	{
		// usual case 
		if (  cosom < (1.0f-0.000001f) )
		{ 
			//usual case 
			omega = (float)acos(cosom);
            // as cosom > -0.999999 ans cosom < 0.999999 sinom != 0 
            // so we can invert it without test
			sinom = 1.0f/(float)sin(omega);			
			sclp = (float)sin((1.0f - t)*omega) * sinom;
			sclq = (float)sin(t*omega) * sinom;
		}
		else
		{	// ends very close -- just lerp 
			sclp = 1.0f - t;
			sclq = t;
		}
		result.V.x = sclp*p.V.x + sclq*q.V.x;
        result.V.y = sclp*p.V.y + sclq*q.V.y;
        result.V.z = sclp*p.V.z + sclq*q.V.z;
        result.w = sclp*p.w + sclq*q.w;
	}
	else
	{
	    /* p and q nearly opposite on sphere-- this is a 360 degree
	    rotation, but the axis of rotation is undefined, so
	    slerp really is undefined too.  So this apparently picks 
	    an arbitrary plane of rotation. However, I think this 
	    code is incorrect.*/ 

        // this case should not happen and is not optimised

		result.V.x = -p.V.y;
        result.V.y = p.V.x;  // qt is orthogonal to p 
		result.V.z = -p.w;
        result.w = p.V.z;

		sclp = sin((Float)(((Float)1.0 - t) * PI_2));
		sclq = (Float)sin( (Float)(t * (Float)PI_2));
		for (i = 0; i<3; i++) (&result.V.x)[i] = sclp*(&p.V.x)[i] + sclq*(&result.V.x)[i];
	}

	return result;

}

