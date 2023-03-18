// **********************************************************************
// * FILE  : Quaternion.h
// * GROUP : TecLibs/3D
// *---------------------------------------------------------------------
// * PURPOSE : Quaternion Class 
//       #     #    #    ######  #     #   ###   #     #  #####               
//       #  #  #   # #   #     # ##    #    #    #     # #     #              
//       #  #  #  #   #  #     # # #   #    #    # #   # #                    
//       #  #  # #     # ######  #  #  #    #    #  #  # #  ####              
//       #  #  # ####### #   #   #   # #    #    #   # # #     #              
//       #  #  # #     # #    #  #    ##    #    #    #  #     #              
//        ## ##  #     # #     # #     #   ###   #     #  #####               
// THIS CLASS SUPPOSES THAT THE QUATERNION ARE USED TO REPRESENT ROTATION
// SO THEY ARE CONSIDERED TO BE NORMALIZED USING THIS WITH NOT NORMALIZED QUATERNION
// IS AT YOUR OWN RISK, WE CANNOT BE HELD RESPONSIBLE FOR THE DAMAGE CAUSED
// BY THE USE OF THIS CLASS. 
// good luck
// *---------------------------------------------------------------------
// * DATES     : 23/06/2000
// * AUTHORS   : Antoine Leclercq (aleclercq@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************

#ifndef _Quaternion_h_
#define _Quaternion_h_


class Quaternion
{
	friend class Matrix3x3;
    friend class Matrix3x4;
public:
	Vector3D V;
	Float w;

// +---------
// | Life-Cycle
// +---------
	inline Quaternion();
	inline Quaternion(const Quaternion& q);
	inline Quaternion(const Vector3D& V, const Float& w) : V(V), w(w) {;};
	inline Quaternion(const Float& x, const Float& y, const Float& z, const Float& w);
	inline Quaternion(const Matrix3x3& crMatrix); 
	inline Quaternion(const Matrix3x4& crMatrix); 

// +---------
// | operators
// +---------
	inline void operator=(const Quaternion& q);
	// Cast To Matrix3x3
	inline operator const Matrix3x3 (void);
	inline operator const Matrix3x4 (void);

// +---------
// | Utilities
// +---------
	inline void SetIdentity();
	inline void Normalize();
	inline friend const Float Norm(const Quaternion& cr_Quaternion);
	inline friend const Float NormSquare(const Quaternion& cr_Quaternion);

// +---------
// | Setting The quaternion to Rotation around axis X,Y,Z or Vector U
// +---------
	inline void SetRotationX(const Float& cr_Angle);
	inline void SetRotationY(const Float& cr_Angle);
	inline void SetRotationZ(const Float& cr_Angle);
	inline void SetRotationU(const Vector3D& cr_Vector, const Float& cr_Angle);

// +---------
// | Unary Operator
// +---------
	inline const Quaternion operator-();

// +---------
// | Operators
// +---------
	inline const Quaternion operator* (const Quaternion& cr_Quaternion) const;
	inline const Quaternion operator+ (const Quaternion& cr_Quaternion) const;
	inline const Quaternion operator- (const Quaternion& cr_Quaternion) const;
	inline const Quaternion& operator*= (const Quaternion& cr_Quaternion);
	inline const Quaternion& operator+= (const Quaternion& cr_Quaternion);
	inline const Quaternion& operator-= (const Quaternion& cr_Quaternion);
	inline friend const Quaternion Inv(const Quaternion& cr_Quaternion);

	inline const Quaternion operator* (const Float& cr_Float) const;
	inline friend const Quaternion operator*(const Quaternion& cr_Quaternion, const Float& cr_Float);
	inline const Quaternion operator/ (const Float& cr_Float) const;
	inline const Quaternion& operator*= (const Float& cr_Float);
	inline const Quaternion& operator/= (const Float& cr_Float);


// +---------
// | External operators
// +---------
	inline friend Float Dot(const Quaternion& cr_Quaternion1, const Quaternion& cr_Quaternion2);

// +---------
// | Spherical interpolation Result = (1-cr_weight)*cr_Quaternion1 + cr_weight*cr_Quaternion2
// +---------
	inline friend const Quaternion& Slerp(const Quaternion& cr_Quaternion1, const Quaternion& cr_Quaternion2, const Float& cr_weight);

private:
	static Quaternion ms_Quaternion;
	static Float ms_Float;
};

#endif

