#ifndef _GROUND_H_
#define _GROUND_H_

#include "Teclibs/src/Tec3D.h"
#include "Texture.h"

class Ground
{
	public:
	
		Point3D *VertexArray;
		Vector3D *NormalArray;
		int VertexCount;
		int NbSide;
		unsigned TexId;
		float Size;
		
		Ground(float Size, int Nb);
		~Ground();
		
		float Elevation(float x, float z);
		Vector3D Normal(float x, float z);
		void Draw();

};

#endif
