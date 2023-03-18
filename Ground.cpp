#include <GL/gl.h>
#include "glext.h"
#include "Ground.h"
#include "Texture.h"

/** Constructeur ******************************************************/

Ground::Ground(float Size, int Nb) : Size(Size)
{
	this->NbSide = Nb;
	this->VertexCount = Nb * Nb;
	this->VertexArray = new Point3D[this->VertexCount];
	this->NormalArray = new Vector3D[this->VertexCount];
	for(int i=0; i<Nb; i++) {
		for(int j=0; j<Nb; j++) {
			this->VertexArray[i+j*Nb].x = this->Size*(float)i/(float)(Nb-1) - this->Size*0.5f;
			this->VertexArray[i+j*Nb].z = this->Size*(float)j/(float)(Nb-1) - this->Size*0.5f;
			this->VertexArray[i+j*Nb].y = this->Elevation(this->VertexArray[i+j*Nb].x, this->VertexArray[i+j*Nb].z);
			this->NormalArray[i+j*Nb] = Normal(this->VertexArray[i+j*Nb].x, this->VertexArray[i+j*Nb].z);
		}
	}
	char Tex_Path[] = "./Neige.tga";
	this->TexId = LoadTexture(Tex_Path, GL_MIRRORED_REPEAT);
}

/** Destructeur *******************************************************/

Ground::~Ground()
{
	delete this->NormalArray;
	delete this->VertexArray;
}

/** Méthode de calcul de l'élévation en y *****************************/

float Ground::Elevation(float x, float z)
{
	return 1.0f * cosf(x/5.0f) * cosf(z/3.0f);
}

/** Méthode de calcul des normales ************************************/

Vector3D Ground::Normal(float x, float z)
{
	Vector3D u;
	Vector3D v;
	u.x = 1e-4f;
	u.y = this->Elevation(x+1e-4f, z) - this->Elevation(x, z);
	u.z = 0.0f;
	v.x = 0.0f;
	v.y = this->Elevation(x, z+1e-4f) - this->Elevation(x, z);
	v.z = 1e-4f;
	Vector3D N;
	N.CrossProduct(v, u);
	N.Normalize();
	return N;
}

/** Méthode d'affichage ***********************************************/

void Ground::Draw()
{
/*	glDisable(GL_LIGHTING);
	glPointSize(4.0f);
	glColor3f(1,1,1);
	glBegin(GL_POINTS);
	for (i=0;i<VertexCount;i++) glVertex3fv(&VertexArray[i].x);
	glEnd();
	glPointSize(1.0f);

	glColor3f(0,1,1);
	glBegin(GL_LINES);
		for (i=0;i<VertexCount;i++) 
		{
			Point3D P = VertexArray[i];
			glVertex3fv(&P.x);
			P+=NormalArray[i];
			glVertex3fv(&P.x);
		}
	glEnd();*/

	float AmbDiff[4] = {0.9f, 0.9f, 0.9f, 1.0f};
	float SpecCol[4] = {0.5f, 0.5f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecCol);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, AmbDiff);	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TexId);
	for(int j=0; j< this->NbSide-1; j++) {
		glBegin(GL_TRIANGLE_STRIP);
			for(int i=0; i<this->NbSide-1; i++) {
				glTexCoord2f(this->VertexArray[i+this->NbSide*j].x/10.0f, this->VertexArray[i+this->NbSide*j].z/10.0f);
				glNormal3fv(&(this->NormalArray[i+this->NbSide*j].x));
				glVertex3fv(&(this->VertexArray[i+this->NbSide*j].x));
				glTexCoord2f(this->VertexArray[i+this->NbSide*(j+1)].x/10.0f, this->VertexArray[i+this->NbSide*(j+1)].z/10.0f);
				glNormal3fv(&(this->NormalArray[i+this->NbSide*(j+1)].x));
				glVertex3fv(&(this->VertexArray[i+this->NbSide*(j+1)].x));
			}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}
