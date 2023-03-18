#ifndef _FOREST_H_
#define _FOREST_H_

#include "Ground.h"

class Forest
{
	public:

		Point3D *Position;
		float *Size;
		int NbTree;
		unsigned ListId;	
		
		Forest(Ground *pGround, int NbTree);
		~Forest();
		void Draw();
		bool noTree_inFront(Reference3D R);

};

#endif
