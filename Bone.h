#ifndef _BONE_H_
#define _BONE_H_

#include "Teclibs/src/Tec3D.h"

// --------------------------------------------------
// **************************************************
// * Bone
// *-------------------------------------------------
// * - Defines a class for a Bone from a Animation
// * - Skeleton
// **************************************************

class Bone
{
	public:
	
		Matrix3x4 Matrix;	// global Matrice for this Bone
		Reference3D Ref;	// Reference expressed in the parent world
		int SonCount;		// Son Count
		Bone **Sons;		// Array of pointers to sons
		unsigned Id;		// A unique Id used to Identify the Bone
	
		Bone();
		~Bone();
		
		void Draw(Matrix3x4 M);				// Draws the Bone (The Reference + line from Center to Sons center)
		void ComputeMatrix(Matrix3x4 M);	// Computes the global Matrice based on M being the parent global Matrix
		Bone *FindBone(unsigned v);			// return a pointer to the bone whose Is==v
		
};

#endif
