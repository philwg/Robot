#include <GL/gl.h>
#include <GL/glut.h>
// #include <alloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Teclibs/src/Tec3D.h"
#include "Robot.h"
#include "Ground.h"
#include "Forest.h"
#include "Cadeau.h"

#undef PI
#define PI 3.14159265359f

#define RAYON_ROBOT 0.35f

extern Ground *gGround;

/** Constructeur ******************************************************/
Robot::Robot()
{
	VertexCount = 46;
	VertexArray = new Point3D[VertexCount];

	VertexArray[0].Set(0.1f, 0.45f, -0.05f);
	VertexArray[1].Set(0.1f, 0.45f,  0.05f);
	VertexArray[2].Set(0.1f, 0.55f,  0.05f);
	VertexArray[3].Set(0.1f, 0.55f, -0.05f);
	VertexArray[4].Set(0.1f, 0.40f, -0.15f);
	VertexArray[5].Set(0.1f, 0.40f,  0.15f);
	VertexArray[6].Set(0.1f, 0.70f,  0.15f);
	VertexArray[7].Set(0.1f, 0.70f, -0.15f);
	VertexArray[8].Set(0.1f, 0.56f,  0.05f);
	VertexArray[9].Set(0.1f, 0.56f, -0.05f);

	VertexArray[10].Set(-0.1f, 0.45f, -0.05f);
	VertexArray[11].Set(-0.1f, 0.45f,  0.05f);
	VertexArray[12].Set(-0.1f, 0.55f,  0.05f);
	VertexArray[13].Set(-0.1f, 0.55f, -0.05f);
	VertexArray[14].Set(-0.1f, 0.40f, -0.15f);
	VertexArray[15].Set(-0.1f, 0.40f,  0.15f);
	VertexArray[16].Set(-0.1f, 0.70f,  0.15f);
	VertexArray[17].Set(-0.1f, 0.70f, -0.15f);
	VertexArray[18].Set(-0.1f, 0.56f,  0.05f);
	VertexArray[19].Set(-0.1f, 0.56f, -0.05f);

	for(int i=0; i<4; i++) VertexArray[20+i] = VertexArray[i] + Point3D(0.24f, 0.0f, 0.0f);
	for(int i=0; i<4; i++) VertexArray[24+i] = VertexArray[i] + Point3D(0.25f, 0.0f, 0.0f);
	for(int i=0; i<4; i++) VertexArray[28+i] = VertexArray[i] + Point3D(0.26f, 0.0f, 0.0f);
	for(int i=0; i<4; i++) VertexArray[32+i] = VertexArray[i+10] - Point3D(0.24f, 0.0f, 0.0f);
	for(int i=0; i<4; i++) VertexArray[36+i] = VertexArray[i+10] - Point3D(0.25f, 0.0f, 0.0f);
	for(int i=0; i<4; i++) VertexArray[40+i] = VertexArray[i+10] - Point3D(0.26f, 0.0f, 0.0f);
	VertexArray[44].Set( 0.7f, 0.5f, 0.0f);
	VertexArray[45].Set(-0.7f, 0.5f, 0.0f);

	AttachArray = new Attach[VertexCount];

	for(int i=0; i<VertexCount; i++) AttachArray[i].Set(0.0f, -1.0f, 1.0f, 0.0f);

	AttachArray[0].Set( 1,  4, 0.5f, 0.5f);
	AttachArray[1].Set( 1,  4, 0.5f, 0.5f);
	AttachArray[2].Set( 1,  4, 0.5f, 0.5f);
	AttachArray[3].Set( 1,  4, 0.5f, 0.5f);
	AttachArray[4].Set( 1, -1, 1.0f, 0.0f);
	AttachArray[5].Set( 1, -1, 1.0f, 0.0f);
	AttachArray[6].Set( 1, -1, 1.0f, 0.0f);
	AttachArray[7].Set( 1, -1, 1.0f, 0.0f);
	AttachArray[8].Set( 1, -1, 1.0f, 0.0f);
	AttachArray[9].Set( 1, -1, 1.0f, 0.0f);
	AttachArray[10].Set(1,  2, 0.5f, 0.5f);
	AttachArray[11].Set(1,  2, 0.5f, 0.5f);
	AttachArray[12].Set(1,  2, 0.5f, 0.5f);
	AttachArray[13].Set(1,  2, 0.5f, 0.5f);
	AttachArray[14].Set(1, -1, 1.0f, 0.0f);
	AttachArray[15].Set(1, -1, 1.0f, 0.0f);
	AttachArray[16].Set(1, -1, 1.0f, 0.0f);
	AttachArray[17].Set(1, -1, 1.0f, 0.0f);
	AttachArray[18].Set(1, -1, 1.0f, 0.0f);
	AttachArray[19].Set(1, -1, 1.0f, 0.0f);

	for(int i=0; i<4; i++) AttachArray[20+i].Set(4, 5, 0.7f, 0.3f);
	for(int i=0; i<4; i++) AttachArray[24+i].Set(4, 5, 0.5f, 0.5f);
	for(int i=0; i<4; i++) AttachArray[28+i].Set(4, 5, 0.3f, 0.7f);
	for(int i=0; i<4; i++) AttachArray[32+i].Set(2, 3, 0.7f, 0.3f);
	for(int i=0; i<4; i++) AttachArray[36+i].Set(2, 3, 0.5f, 0.5f);
	for(int i=0; i<4; i++) AttachArray[40+i].Set(2, 3, 0.3f, 0.7f);
	AttachArray[44].Set(5, -1, 1.0f, 0.0f);
	AttachArray[45].Set(3, -1, 1.0f, 0.0f);

	NormalCount = 6+8;
	NormalArray = new Vector3D[NormalCount];
	NormalArray[0].Set( 1,  0,  0);
	NormalArray[1].Set(-1,  0,  0);
	NormalArray[2].Set( 0,  0,  1);
	NormalArray[3].Set( 0,  0, -1);
	NormalArray[4].Set( 0,  1,  0);
	NormalArray[5].Set( 0, -1,  0);

	TriangleCount = 88;
	TriangleArray = new Triangle[TriangleCount];
	Set( 0, 5, 4, 1, 0, 0, 0);
	Set( 1, 4, 0, 1, 0, 0, 0);
	Set( 2, 3, 8, 2, 0, 0, 0);
	Set( 3, 8, 3, 9, 0, 0, 0);
	Set( 4, 8, 9, 6, 0, 0, 0);
	Set( 5, 9, 7, 6, 0, 0, 0);
	Set( 6, 1, 2, 5, 0, 0, 0);
	Set( 7, 5, 2, 8, 0, 0, 0);
	Set( 8, 5, 8, 6, 0, 0, 0);
	Set( 9, 3, 0, 4, 0, 0, 0);
	Set(10, 3, 4, 9, 0, 0, 0);
	Set(11, 9, 4, 7, 0, 0, 0);
	
	Set(12, 15, 11, 14, 1, 1, 1);
	Set(13, 14, 11, 10, 1, 1, 1);
	Set(14, 13, 12, 18, 1, 1, 1);
	Set(15, 18, 19, 13, 1, 1, 1);
	Set(16, 18, 16, 19, 1, 1, 1);
	Set(17, 19, 16, 17, 1, 1, 1);
	Set(18, 11, 15, 12, 1, 1, 1);
	Set(19, 15, 18, 12, 1, 1, 1);
	Set(20, 15, 16, 18, 1, 1, 1);
	Set(21, 13, 14, 10, 1, 1, 1);
	Set(22, 13, 19, 14, 1, 1, 1);
	Set(23, 19, 17, 14, 1, 1, 1);

	Set(24,  5, 6, 15, 2, 2, 2);
	Set(25, 15, 6, 16, 2, 2, 2);
	
	Set(26, 7,  4, 14, 3, 3, 3);
	Set(27, 7, 14, 17, 3, 3, 3);

	Set(28, 6,  7, 17, 4, 4, 4);
	Set(29, 6, 17, 16, 4, 4, 4);

	Set(30, 4,  5, 15, 5, 5, 5);
	Set(31, 4, 15, 14, 5, 5, 5);

	int n[4] = {5, 2, 4, 3};
	
	for(int i=0; i<4; i++) {
		Set(  32+i*2,    i,	      i+20,	(i+1)%4+20,	n[i], n[i], n[i]);
		Set(32+i*2+1,    i, (i+1)%4+20,	   (i+1)%4,	n[i], n[i], n[i]);
		Set(  40+i*2, i+20,       i+24, (i+1)%4+24, n[i], n[i], n[i]);
		Set(40+i*2+1, i+20, (i+1)%4+24, (i+1)%4+20, n[i], n[i], n[i]);
		Set(  48+i*2, i+24,       i+28, (i+1)%4+28, n[i], n[i], n[i]);
		Set(48+i*2+1, i+24, (i+1)%4+28, (i+1)%4+24, n[i], n[i], n[i]);
		Set(    56+i, i+28,         44, (i+1)%4+28,  6+i,  6+i,  6+i);
		NormalArray[6+i] = TriangleArray[56+i].Normal(VertexArray);
	}

	for(int i=0; i<4; i++)	{
		Set(  60+i*2, i+10, (i+1)%4+32,       i+32, n[i], n[i], n[i]);
		Set(60+i*2+1, i+10, (i+1)%4+10, (i+1)%4+32, n[i], n[i], n[i]);
		Set(  68+i*2, i+32, (i+1)%4+36,       i+36, n[i], n[i], n[i]);
		Set(68+i*2+1, i+32, (i+1)%4+32, (i+1)%4+36, n[i], n[i], n[i]);
		Set(  76+i*2, i+36, (i+1)%4+40,       i+40, n[i], n[i], n[i]);
		Set(76+i*2+1, i+36, (i+1)%4+36, (i+1)%4+40, n[i], n[i], n[i]);
		Set(    84+i, i+40, (i+1)%4+40,         45, 10+i, 10+i, 10+i);
		NormalArray[10+i] = TriangleArray[84+i].Normal(VertexArray);
	}

	Vector3D *N;
	N = new Vector3D[VertexCount];
	for(int i=0; i<VertexCount; i++) N[i].Set(0);
	for(int i=0; i<TriangleCount; i++)
	for(int j=0; j<3; j++) {
		int p = TriangleArray[i].Vertex_Index[j];
		N[p] += NormalArray[TriangleArray[i].Normal_Index[j]];
	}
	for(int i=0; i<VertexCount; i++) N[i].Normalize();

	delete [] NormalArray;
	NormalArray = N;
	NormalCount = VertexCount;
	for(int i=0; i<TriangleCount; i++) {
		for(int j=0; j<3; j++) {
			TriangleArray[i].Normal_Index[j] = TriangleArray[i].Vertex_Index[j];
		}
	}

	this->m_bIsWalking = false;
	this->m_Turning = 0;

	this->MainRoot = new Bone();
	this->MainRoot->Ref.Set(Point3D( 0.0f, 0.0f, 0.0f),
							Vector3D(1.0f, 0.0f, 0.0f),
							Vector3D(0.0f, 1.0f, 0.0f),
							Vector3D(0.0f, 0.0f, 1.0f));
	this->MainRoot->Id = 0;

	Bone *B0;
	B0 = new Bone();
	B0->Id = 128;
	B0->Ref.Set(Point3D( 0.0f, 0.0f, 0.0f),
				Vector3D(1.0f, 0.0f, 0.0f),
				Vector3D(0.0f, 1.0f, 0.0f),
				Vector3D(0.0f, 0.0f, 1.0f));

	Bone *B1;
	B1 = new Bone();
	B1->Id = 1;
	B1->Ref.Set(Point3D( 0.0f, 0.5f, 0.0f),
				Vector3D(1.0f, 0.0f, 0.0f),
				Vector3D(0.0f, 1.0f, 0.0f),
				Vector3D(0.0f, 0.0f, 1.0f));
	
	Bone *B2;			
	B2 = new Bone();
	B2->Id = 2;
	B2->Ref.Set(Point3D(-0.1f, 0.0f, 0.0f),
				Vector3D(1.0f, 0.0f, 0.0f),
				Vector3D(0.0f, 1.0f, 0.0f),
				Vector3D(0.0f, 0.0f, 1.0f));
	
	Bone *B3;			
	B3 = new Bone();
	B3->Id = 3;
	B3->Ref.Set(Point3D(-0.25f, 0.0f, 0.0f),
				Vector3D(1.00f, 0.0f, 0.0f),
				Vector3D(0.00f, 1.0f, 0.0f),
				Vector3D(0.00f, 0.0f, 1.0f));
	
	Bone *B4;			
	B4 = new Bone();
	B4->Id = 4;
	B4->Ref.Set(Point3D( 0.1f, 0.0f, 0.0f),
				Vector3D(1.0f, 0.0f, 0.0f),
				Vector3D(0.0f, 1.0f, 0.0f),
				Vector3D(0.0f, 0.0f, 1.0f));
	
	Bone *B5;			
	B5 = new Bone();
	B5->Id = 5;
	B5->Ref.Set(Point3D( 0.25f, 0.0f, 0.0f),
				Vector3D(1.00f, 0.0f, 0.0f),
				Vector3D(0.00f, 1.0f, 0.0f),
				Vector3D(0.00f, 0.0f, 1.0f));

	this->MainRoot->Sons = (Bone**)malloc(sizeof(Bone*));
	this->MainRoot->Sons[0] = B0;
	this->MainRoot->SonCount = 1;

	B0->Sons = (Bone**)malloc(sizeof(Bone*));
	B0->Sons[0] = B1;
	B0->SonCount = 1;
		
	B1->Sons = (Bone**)malloc(2*sizeof(Bone*));
	B1->Sons[0] = B2;
	B1->Sons[1] = B4;
	B1->SonCount = 2;

	B2->Sons = (Bone**)malloc(sizeof(Bone*));
	B2->Sons[0] = B3;
	B2->SonCount = 1;
	
	B4->Sons = (Bone**)malloc(sizeof(Bone*));
	B4->Sons[0] = B5;
	B4->SonCount = 1;

	Bone *B6;
	B6 = new Bone();
	B6->Id = 6;
	B6->Ref.Set(Point3D(-0.35f, 0.0f, 0.0f),
				Vector3D(1.00f, 0.0f, 0.0f),
				Vector3D(0.00f, 1.0f, 0.0f),
				Vector3D(0.00f, 0.0f, 1.0f));
				
	B3->Sons = (Bone**)malloc(sizeof(Bone*));
	B3->Sons[0] = B6;
	B3->SonCount = 1;
	
	Bone *B7;
	B7 = new Bone();
	B7->Id = 7;
	B7->Ref.Set(Point3D( 0.35f, 0.0f, 0.0f),
				Vector3D(1.00f, 0.0f, 0.0f),
				Vector3D(0.00f, 1.0f, 0.0f),
				Vector3D(0.00f, 0.0f, 1.0f));
				
	B5->Sons = (Bone**)malloc(sizeof(Bone*));
	B5->Sons[0] = B7;
	B5->SonCount = 1;

	this->AttachToBone();
}

/** Destructeur *******************************************************/

Robot::~Robot()
{
	delete this->LocalArray;
	delete this->AttachArray;
	delete this->MainRoot;
}


void Robot::Walk(bool bOn)
{
	if (!bOn) this->SetStand();
	this->m_bIsWalking = bOn;
}

void Robot::TurnLeft(bool bOn)
{
	if (bOn) this->m_Turning = 1;
	else if (this->m_Turning==1) this->m_Turning = 0;
}

void Robot::TurnRight(bool bOn)
{
	if (bOn) this->m_Turning = -1;
	else if (this->m_Turning==-1) this->m_Turning = 0;
}

void Robot::StartAnimation(unsigned Time)
{
	this->m_uOldTime = Time;
	this->SetStand();
	this->tAnim = 0.0f;
	this->MainRoot->Ref.O.y = gGround->Elevation(this->MainRoot->Ref.O.x, this->MainRoot->Ref.O.z);
}

void Robot::SetStand()
{
	Bone *B;
	Matrix3x4 M;
	Vector3D T;

	M.SetIdentity(); 					// initialisation sans transformation
	B = this->MainRoot->FindBone(1);	// Position de parcours du robot B0 pour le sol et la caméra
	T = B->Ref.O;						// On enregistre la translation vers l'origine du repère de l'os
	M.PostTranslate(T);					// On applique cette translation
	B->Ref.Set(M);
	
	B = this->MainRoot->FindBone(2);	// jambe droite
	M.SetRotationZ(0.24*PI);
	T = B->Ref.O;
	M.PostTranslate(T);
	B->Ref.Set(M);

	B = this->MainRoot->FindBone(3);	// pied droit
	M.SetRotationZ(0.36*PI);
	T = B->Ref.O;
	M.PostTranslate(T);
	B->Ref.Set(M);
	
	B = this->MainRoot->FindBone(4);	// jambe gauche
	M.SetRotationZ(-0.24*PI);
	T = B->Ref.O;
	M.PostTranslate(T);
	B->Ref.Set(M);

	B = this->MainRoot->FindBone(5);	// pied gauche
	M.SetRotationZ(-0.36*PI);
	T = B->Ref.O;
	M.PostTranslate(T);
	B->Ref.Set(M);

	M.SetIdentity();					// Mise à jour
	this->MainRoot->ComputeMatrix(M);
	UpdateMesh();
}

void Robot::Animate(unsigned Time)
{
	Bone *B;
	Matrix3x4 M;
	Vector3D T;
	float t;
	float dt = 0.05f;		// le pas temporel
		
	if (this->m_bIsWalking) {
		
		this->tAnim += dt;
		while (this->tAnim > 1.0f) this->tAnim -= 1.0f;
		float alphAnim = this->tAnim*2.0f*PI;
		// tAnim est systématiquement multiplié par 2*PI ensuite pour occasionner
		// une cohérence de fréquence dans les différents mouvements de rotation
		// On le remplace par l'angle d'animation des rotations : alphAnim
	
		// Animation Buste
		B = this->MainRoot->FindBone(1);
		T = B->Ref.O;
		M.SetIdentity();
		// La rotation X est en frequence double pour piquer du nez pied droit ET pied gauche en avant
		M.SetRotationX(cos(alphAnim*2.0f)*0.03f*PI);	// le facteur 0.03 attenue la rotation en X
		M.PostRotateY(-sin(alphAnim)*0.09f*PI);			// le facteur 0.09 limite l'amplitude du balancement en Y
		M.PostRotateZ(cos(alphAnim)*0.09f*PI);			// ... idem en Z ... usage de sin/cos pour déphaser les deux rotations
		M.PostTranslate(T);
		B->Ref.Set(M);		
									
		// Animation Jambe droite			
		B = this->MainRoot->FindBone(2);
		T = B->Ref.O;
		M.SetIdentity();
		M.SetRotationX(-sin(alphAnim)*0.24f*PI);	// le facteur 0.24 donne une amplitude suffisante à cette rotation en X
		M.PostRotateY(-sin(alphAnim)*0.24f*PI);		// ... idem en Y ... Les deux ont le même signe pour le coté droit
		M.PostRotateZ((cos(alphAnim)*0.24f*PI>0.12f*PI) ? cos(alphAnim)*0.24f*PI : 0.12f*PI);
		// On a bloqué l'effet en Z pour que le membre ne dépasse pas une certaine hauteur (--> + naturel)
		// Rem : usage de cos pour déphaser cette rotation / autres
		M.PostTranslate(T);
		B->Ref.Set(M);			

		// Animation Jambe gauche
		B = this->MainRoot->FindBone(4);
		T = B->Ref.O;
		M.SetIdentity();
		M.SetRotationX(sin(alphAnim)*0.24f*PI);		// le facteur 0.24 donne une amplitude suffisante à cette rotation en X
		M.PostRotateY(-sin(alphAnim)*0.24f*PI);		// ... idem en Y ... le changement de signe garde la cohérence du mvt à gauche
		M.PostRotateZ((cos(alphAnim)*0.24f*PI<-0.12f*PI) ? cos(alphAnim)*0.24f*PI : -0.12f*PI);				
		// On bloque l'effet en Z pour que le membre ne dépasse pas une certaine hauteur (--> + naturel)
		// Rem : usage de cos pour déphaser cette rotation / autres
		M.PostTranslate(T);
		B->Ref.Set(M);			

		// Animation Pied droit
		B = this->MainRoot->FindBone(3);
		M.SetRotationX(sin(alphAnim)*0.18f*PI);	
		M.PostRotateY(-sin(alphAnim)*0.18f*PI);
		M.PostRotateZ(cos(-alphAnim)*0.18f*PI);						
		T = B->Ref.O;
		M.PostTranslate(T);
		B->Ref.Set(M);
		
		// Animation Pied gauche
		B = this->MainRoot->FindBone(5);
		M.SetRotationX(-sin(alphAnim)*0.18f*PI);
		M.PostRotateY(-sin(alphAnim)*0.18f*PI);
		M.PostRotateZ(cos(-alphAnim)*0.18f*PI);						
		T = B->Ref.O;
		M.PostTranslate(T);
		B->Ref.Set(M);
		
		MoveFromTo(this->MainRoot->Ref.O, this->MainRoot->Ref.O + 1.5f*dt*(Point3D)(this->MainRoot->Ref.K));
	}

	switch (this->m_Turning) {
		
		case 1:
			M = this->MainRoot->Ref;
			M.PostRotateY(1.0f*dt);
			this->MainRoot->Ref.Set(M);
			break;
			
		case -1:
			M = this->MainRoot->Ref;
			M.PostRotateY(-1.0f*dt);
			this->MainRoot->Ref.Set(M);
			break;
			
		default :
			break;
	}

	this->UpdateMesh();
	this->m_uOldTime = Time;
}

void Robot::DrawSkeleton()
{
	Matrix3x4 M;
	M.SetIdentity();
	this->MainRoot->Draw(M);
}

void Robot::set_CadeauNbr(int n)
{
	this->CadeauNbr = n;
}

void Robot::renderBitmapString(float x, float y, float z, void *font, const char *string) const
{
	const char *c;
	glRasterPos3f(x, y, z);
	for (c=string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void Robot::Draw()
{
	float AmbDiff[4] = {0.9f, 0.7f, 0.1f};
	float SpecCol[4] = {1.0f, 0.9f, 0.9f, 1.0f};
	glMaterialf( GL_FRONT, GL_SHININESS, 10.0f);
	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecCol);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, AmbDiff);	
	glBegin(GL_TRIANGLES);
		for(int i=0; i<TriangleCount; i++) {
			for(int j=0; j<3; j++) {
				glNormal3fv(&NormalArray[TriangleArray[i].Vertex_Index[j]].x);
				glVertex3fv(&VertexArray[TriangleArray[i].Normal_Index[j]].x);
			}
		}
	glEnd();
	char writeBuffer[16] = {'\0'};
	if (this->CadeauNbr>0) sprintf(writeBuffer, "%d", this->CadeauNbr);
	else sprintf(writeBuffer, "YOU HAVE WON !!!");
	glColor3f(1.0f, 0.0f, 0.0f);
	this->renderBitmapString(this->MainRoot->Ref.O.x, this->MainRoot->Ref.O.y+1.0f, this->MainRoot->Ref.O.z, GLUT_BITMAP_HELVETICA_18, writeBuffer);
}

void Robot::AttachToBone()
{
	Bone *B;
	Matrix3x4 M;
	LocalArray = new LocalVert[VertexCount];
	M.SetIdentity();
	this->MainRoot->ComputeMatrix(M);
	for(int i=0; i<VertexCount; i++) {
		B = this->MainRoot->FindBone(this->AttachArray[i].Bone1);
		M = Inv(B->Matrix);
		this->LocalArray[i].B1 = B;
		this->LocalArray[i].Vertex1 = M * VertexArray[i];
		this->LocalArray[i].Normal1 = M * NormalArray[i];
		this->LocalArray[i].weight1 = this->AttachArray[i].Weight1;
		if (this->AttachArray[i].Bone2!=-1) {
			B = this->MainRoot->FindBone(this->AttachArray[i].Bone2);
			M = Inv(B->Matrix);
			this->LocalArray[i].B2 = B;
			this->LocalArray[i].Vertex2 = M * VertexArray[i];
			this->LocalArray[i].Normal2 = M * NormalArray[i];
			this->LocalArray[i].weight2 = this->AttachArray[i].Weight2;
		}
		else this->LocalArray[i].B2 = NULL;		
	}
}

void Robot::UpdateMesh()
{
	Matrix3x4 M;
	M.SetIdentity();
	this->MainRoot->ComputeMatrix(M);
	for(int i=0; i<VertexCount; i++) {
		VertexArray[i] = this->LocalArray[i].weight1 * (this->LocalArray[i].B1->Matrix * this->LocalArray[i].Vertex1);
		NormalArray[i] = this->LocalArray[i].weight1 * (this->LocalArray[i].B1->Matrix * this->LocalArray[i].Normal1);
		if (this->LocalArray[i].B2) {
			VertexArray[i] += this->LocalArray[i].weight2 * (this->LocalArray[i].B2->Matrix * this->LocalArray[i].Vertex2);
			NormalArray[i] += this->LocalArray[i].weight2 * (this->LocalArray[i].B2->Matrix * this->LocalArray[i].Normal2);
			NormalArray[i].Normalize();
		}
	}
}

void Robot::MoveFromTo(const Point3D &Origin, const Point3D &Dest)
{
	this->MainRoot->Ref.O = Dest;
	this->MainRoot->Ref.O.y = gGround->Elevation(this->MainRoot->Ref.O.x, this->MainRoot->Ref.O.z);	
}
