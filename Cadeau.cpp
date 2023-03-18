#include <GL/gl.h>
#include <stdlib.h>
#include "glext.h"
#include "Cadeau.h"

/** Constructeur ******************************************************/
Cadeau::Cadeau(int MaxCount,  Ground *pGround, Forest *pForest) : MaxCount(MaxCount)
{
	this->Alive = new bool[this->MaxCount];
	this->Position = new Point3D[this->MaxCount];
	for (int i=0; i<this->MaxCount; i++) {
		this->Position[i] = Point3D(0.0f, 500.0f, 0.0f);
		this->Alive[i] = true;
	}
	char Texture_path[] = "./kdo.tga";
	this->TextureId = LoadTexture(Texture_path); 
	bool Intersect;
	for (int i=0; i<MaxCount; i++) {
		do {
			this->Position[i].x = pGround->Size*((float)rand()/(float)RAND_MAX-0.5f);
			this->Position[i].z = pGround->Size*((float)rand()/(float)RAND_MAX-0.5f);
			this->Position[i].y = pGround->Elevation(this->Position[i].x, this->Position[i].z);
			Intersect = false;
			for (int j=0; j<pForest->NbTree; j++) {
				Vector3D u(this->Position[i], pForest->Position[j]);
				float r = pForest->Size[j] + 0.5f;
				if (NormSquare(u)<r*r) {
					Intersect = true;
					break;
				}
			}
		} while(Intersect);
		this->Alive[i] = true;
	}
	this->StillAlive = this->MaxCount;
}

/** Destructeur *******************************************************/
Cadeau::~Cadeau()
{
	delete this->Alive;
	delete this->Position;
}

/** Méthode de dessin du Cadeau ***************************************/
void Cadeau::Draw()
{
	float AmbDiff[4] = {1.0f, 1.0f, 1.0f, 1};
	float SpecCol[4] = {0.9f, 0.9f, 0.9f, 1};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_BLEND);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecCol);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, AmbDiff);	
	glBindTexture(GL_TEXTURE_2D, this->TextureId);

	for(int i=0; i<this->MaxCount; i++) {
		if (this->Alive[i]) {
			glPushMatrix();
				glTranslatef(this->Position[i].x, this->Position[i].y, this->Position[i].z);
				glScalef(0.3f,0.3f,0.3f);
				glBegin(GL_QUADS);
				
					glNormal3f(0.0f, 0.0f, -1.0f);	// face 1
					glTexCoord2f(  0.0f, 0.0f);		glVertex3f(-1.0f, 0.0f, -1.0f);
					glTexCoord2f(0.495f, 0.0f);		glVertex3f( 1.0f, 0.0f, -1.0f);
					glTexCoord2f(0.495f, 0.495f);	glVertex3f( 1.0f, 2.0f, -1.0f);
					glTexCoord2f(  0.0f, 0.495f);	glVertex3f(-1.0f, 2.0f, -1.0f);
					
					glNormal3f(1.0f, 0.0f, 0.0f);	// face 2
					glTexCoord2f(  0.0f, 0.0f);		glVertex3f(1.0f, 0.0f, -1.0f);
					glTexCoord2f(0.495f, 0.0f);		glVertex3f(1.0f, 0.0f,  1.0f);
					glTexCoord2f(0.495f, 0.495f);	glVertex3f(1.0f, 2.0f,  1.0f);
					glTexCoord2f(  0.0f, 0.495f);	glVertex3f(1.0f, 2.0f, -1.0f);	
			
					glNormal3f(0.0f, 0.0f, 1.0f);	// face 3
					glTexCoord2f(  0.0f, 0.0f);		glVertex3f( 1.0f, 0.0f, 1.0f);
					glTexCoord2f(0.495f, 0.0f);		glVertex3f(-1.0f, 0.0f, 1.0f);
					glTexCoord2f(0.495f, 0.495f);	glVertex3f(-1.0f, 2.0f, 1.0f);
					glTexCoord2f(  0.0f, 0.495f);	glVertex3f( 1.0f, 2.0f, 1.0f);
					
					glNormal3f(-1.0f, 0.0f, 0.0f);	// face 4
					glTexCoord2f(  0.0f, 0.0f);		glVertex3f(-1.0f, 0.0f, -1.0f);
					glTexCoord2f(0.495f, 0.0f);		glVertex3f(-1.0f, 0.0f,  1.0f);
					glTexCoord2f(0.495f, 0.495f);	glVertex3f(-1.0f, 2.0f,  1.0f);
					glTexCoord2f(  0.0f, 0.495f);	glVertex3f(-1.0f, 2.0f, -1.0f);
				
					glNormal3f(0.0f, 1.0f, 0.0f);	// face 5
					glTexCoord2f(0.0f, 0.5f);		glVertex3f(-1.0f, 2.0f, -1.0f);
					glTexCoord2f(0.5f, 0.5f);		glVertex3f( 1.0f, 2.0f, -1.0f);
					glTexCoord2f(0.5f, 1.0f);		glVertex3f( 1.0f, 2.0f,  1.0f);
					glTexCoord2f(0.0f, 1.0f);		glVertex3f(-1.0f, 2.0f,  1.0f);
					
				glEnd();
			glPopMatrix();
		}
	}
	glDisable(GL_TEXTURE_2D);
}

int Cadeau::update_At(Point3D P)
{
	int nb = 0;
	for (int i=0; i<MaxCount; i++) {
		Vector3D u(this->Position[i], P);
		if (NormSquare(u)<2.0f) this->Alive[i] = false;
		if (this->Alive[i]) nb++;
	}
	return nb;
}
