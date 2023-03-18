#include <GL/gl.h>
#include "Bone.h"

/** Constructeur ******************************************************/
Bone::Bone()
{
	this->SonCount = 0;
	this->Sons = NULL;
}

/** Destructeur *******************************************************/
Bone::~Bone()
{
	delete this->Sons;
}

// Draws the Bone (The Reference + line from Center to Sons center)
void Bone::Draw(Matrix3x4 M)
{
	Point3D O;
	Point3D R;
	M = M * this->Ref;
	O = M * Point3D(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	
		glColor3f(0.6f, 0.6f, 0.0f);
		for(int i=0; i<this->SonCount; i++) {
			glVertex3f(O.x, O.y, O.z);
			R = M * this->Sons[i]->Ref.O;
			glVertex3f(R.x, R.y, R.z);
		}
		
		glColor4f(0.8f, 0.0f, 0.0f ,1.0f);
		glVertex3f(O.x, O.y, O.z);
		R = M * Point3D(0.1f, 0.0f, 0.0f);
		glVertex3f(R.x, R.y, R.z);;

		glColor4f(0.0f, 0.8f, 0.0f, 1.0f);
		glVertex3f(O.x, O.y, O.z);
		R = M * Point3D(0.0f, 0.1f, 0.0f);
		glVertex3f(R.x, R.y, R.z);
	
		glColor4f(0.0f, 0.0f, 0.8f, 1.0f);
		glVertex3f(O.x, O.y, O.z);
		R = M * Point3D(0.0f, 0.0f, 0.1f);
		glVertex3f(R.x, R.y, R.z);
		
	glEnd();
	for (int i=0; i<SonCount; i++) this->Sons[i]->Draw(M);
}

// Computes the global Matrice based on M being the parent World Matrix
void Bone::ComputeMatrix(Matrix3x4 M)
{
	this->Matrix = M * this->Ref;
	for(int i=0; i<SonCount; i++) this->Sons[i]->ComputeMatrix(Matrix);
}

// return a pointer to the bone whose Is==v
Bone* Bone::FindBone(unsigned v)
{
	Bone *B;
	if (Id==v) return this;
	for(int i=0; i<SonCount; i++) {
		B = this->Sons[i]->FindBone(v);
		if (B) return B;
	}
	return NULL;
}
