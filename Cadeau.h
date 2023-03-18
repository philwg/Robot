#ifndef _CADEAU_H_
#define _CADEAU_H_

#include "Ground.h"
#include "Forest.h"

class Cadeau
{
	public:
		
		Point3D *Position;
		int MaxCount;
		bool *Alive;
		int StillAlive;
		unsigned TextureId;
		
		Cadeau(int MaxCount, Ground *pGround, Forest *pForest);
		~Cadeau();
		
		void Draw();
		int update_At(Point3D P);
		
};

#endif
