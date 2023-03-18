#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "glext.h"
#include "Ground.h"
#include "Forest.h"

/** Constructeur ******************************************************/
Forest::Forest(Ground *pGround, int NbTree) : NbTree(NbTree)
{
	bool OK;
	Vector3D u;
	Point3D RayOrigin;
	Vector3D RayDirection(0,-1,0);
	this->Position = new Point3D[this->NbTree];
	this->Size = new float[this->NbTree];
	for(int i=0; i<this->NbTree; i++) {
		do {
			OK = true;
			this->Position[i].x = pGround->Size*((float)rand()/(float)RAND_MAX-0.5f);
			this->Position[i].z = pGround->Size*((float)rand()/(float)RAND_MAX-0.5f);
			this->Position[i].y = pGround->Elevation(this->Position[i].x, this->Position[i].z);
			this->Size[i] = 1.0f + 2.0f*(float)rand()/(float)RAND_MAX;
			for(int j=0; j<i; j++) {
				u = Vector3D((Point3D)this->Position[i] , (Point3D)this->Position[j]);
				u.y = 0.0f;
				if ((Norm(u)<(this->Size[i]+this->Size[j])) || (Norm(this->Position[i])<2.0f)) OK = false;
			}
		} while(!OK);
	}
	Point3D P[9];
	float e = 0.01f;
	int Tr[7*3] = {	0,1,2,
					2,1,3,
					7,2,4,
					4,2,3,
					4,3,5,
					6,8,4,
					6,4,5 };
	int T2[3*3] = {	0,2,1,
					7,4,2,
					8,6,4 };
	P[0] = Point3D (-1.0f, 0.0f, -e);
	P[1] = Point3D (   -e, 0.0f, -e);
	P[2] = Point3D (-0.3f, 1.0f, -e);
	P[3] = Point3D (   -e, 1.0f, -e);
	P[4] = Point3D (-0.2f, 2.0f, -e);
	P[5] = Point3D (   -e, 2.0f, -e);
	P[6] = Point3D (   -e, 3.0f, -e);
	P[7] = Point3D (-0.8f, 1.0f, -e);
	P[8] = Point3D (-0.5f, 2.0f, -e);
	for(int i=0; i<9; i++) P[i] *= 0.5f;
	this->ListId = glGenLists(1);
	glNewList(ListId, GL_COMPILE);
	glPushMatrix();
		for(int n=0; n<9; n++)	{
			glBegin(GL_TRIANGLES);
				for(int i=0; i<7*3; i++) {
					glNormal3f(0.0f, 0.0f, -1.0f);
					glVertex3fv(&P[Tr[i]].x);
				}
				for(int i=0; i<7; i++) {
					Point3D Pt;
					Pt = P[Tr[i*3]];
					Pt.z = Pt.z+2.0f*e;
					glNormal3f(0.0f, 0.0f, 1.0f);
					glVertex3fv(&Pt.x);
					Pt = P[Tr[i*3+2]];
					Pt.z = Pt.z+2.0f*e;
					glNormal3f(0.0f, 0.0f, 1.0f);
					glVertex3fv(&Pt.x);
					Pt = P[Tr[i*3+1]];
					Pt.z = Pt.z+2.0f*e;
					glNormal3f(0.0f, 0.0f, 1.0f);
					glVertex3fv(&Pt.x);
				}
			glEnd();
			for(int i=0; i<3; i++) {
				Point3D A,B,C,D,E,F;
				Vector3D N;
				A = P[T2[i*3]];
				B = P[T2[i*3+1]];
				C = P[T2[i*3+2]];
				D = A + Point3D(0.0f, 0.0f, 2.0f*e);
				E = B + Point3D(0.0f, 0.0f, 2.0f*e);
				F = C + Point3D(0.0f, 0.0f, 2.0f*e);
				N.y = B.x-A.x;
				N.x = A.y-B.y;
				N.z = 0.0f;
				N.Normalize();
				glBegin(GL_QUADS);
					// Quad 1
					glNormal3fv(&N.x);	glVertex3fv(&A.x);
					glNormal3fv(&N.x);	glVertex3fv(&B.x);
					glNormal3fv(&N.x);	glVertex3fv(&E.x);
					glNormal3fv(&N.x);	glVertex3fv(&D.x);
					//Quad 2
					glNormal3f(0.0f, -1.0f, 0.0f);	glVertex3fv(&A.x);
					glNormal3f(0.0f, -1.0f, 0.0f);	glVertex3fv(&D.x);
					glNormal3f(0.0f, -1.0f, 0.0f);	glVertex3fv(&F.x);
					glNormal3f(0.0f, -1.0f, 0.0f);	glVertex3fv(&C.x);
					
				glEnd();
			}	
			glRotatef(360.0f/9.0f, 0.0f, 1.0f, 0.0f);
		}
	glPopMatrix();
	glEndList();
}

/** Destructeur *******************************************************/
Forest::~Forest()
{
	delete this->Position;
	delete this->Size;
}

/** Dessin de la fôret ************************************************/
void Forest::Draw()
{
	float AmbDiff[4] = {0.0f, 0.7f, 0.0f, 1.0f};
	float SpecCol[4] = {0.3f, 0.9f, 0.3f, 1.0f};
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_BLEND);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	glMaterialfv(GL_FRONT, GL_SPECULAR,SpecCol);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, AmbDiff);	
	for(int i=0; i<this->NbTree; i++) {
		glPushMatrix();
			glTranslatef(this->Position[i].x, this->Position[i].y, this->Position[i].z);
			glScalef(this->Size[i], this->Size[i], this->Size[i]);
			glCallList(this->ListId);
		glPopMatrix();	
	}	
}

bool Forest::noTree_inFront(Reference3D R)
{
	// On fixe une valeur abhérante pour un minimum
	float dmin = 144000.0f;
	float size = 0.0f;
	Vector3D toTree;
	Point3D flatRob(R.O.x, 0.0f, R.O.z);
	// On caratcérise l'arbre le plus proche par sa distance au robot et la translation 2D Robot-->Arbre
	for(int i=0; i<this->NbTree; i++) {
		Point3D flatTree(this->Position[i].x, 0.0f, this->Position[i].z);
		Vector3D u(flatRob, flatTree);
		if (NormSquare(u) < dmin) {
			dmin = NormSquare(u);		// Actualisation du minimum
			size = this->Size[i];		// Actualisation de la taille associée
			toTree = u;					// Actualisation de la translation associée
		}
	}
	// On récupère le vecteur 2D d'orientation K du Robot dans son repère local (direction droit devant)
	Vector3D flatK(R.K.x, 0.0f, R.K.z);
	// On calcule le p.scal. avec la translation vers l'arbre
	float dir = Dot(flatK, toTree);
	// si il est négatif, l'arbre le plus proche est "derrière", on peut avancer.
	if (dir < 0.0f) return true;
	// sinon (l'arbre le plus proche est devant (0° --> 180°) ...
	else {
		// On récupère l'orientation 2D I du robot dans son reprère local (direction à droite)
		Vector3D flatI(R.I.x, 0.0f, R.I.z);
		// On calcule l'angle de I avec la translation vers l'arbre
		float alpha = (std::acos(Dot(flatI, toTree)/(NormSquare(toTree)*NormSquare(flatI))))/PI*180.0f;
		// Si on n'est pas trop près taille de l'arbre à 20% près, on peut avancer ...
		if (dmin>1.2f*size) return true;
		// Sinon ça dépend de l'angle à 20° près ...
		else return (std::abs(alpha-90.0f)>20.0f);
	}
}
