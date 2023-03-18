#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "Bone.h"
#include "Mesh.h"

/** Classe interne ****************************************************/
class Attach
{
	public:
	
		int Bone1;
		int Bone2;
		float Weight1;
		float Weight2;
		
		Attach() {}
		~Attach() {}
		
		void Set(int B1, int B2, float w1, float w2) {
			this->Bone1 = B1;
			this->Bone2 = B2;
			this->Weight1 = w1;
			this->Weight2 = w2;
		}
		
};

/** Classe interne ****************************************************/
class LocalVert
{
	public:
	
		Point3D Vertex1;
		Point3D Vertex2;
		Vector3D Normal1;
		Vector3D Normal2;
		Bone *B1;
		Bone *B2;
		float weight1;
		float weight2;
		
		LocalVert() {}
		~LocalVert() {
			delete B1;
			delete B2;
		}
		
};

/** Classe Robot ******************************************************/
class Robot : public Mesh
{
	private:
	
		int CadeauNbr;
		bool m_bIsWalking;
		int m_Turning;
		unsigned m_uOldTime;
		Bone *MainRoot;
		float tAnim;
		Attach *AttachArray;
		LocalVert *LocalArray;
		
		void SetStand();	
		
	public:
	
		Robot();
		~Robot();
		
		void AttachToBone();
		void Walk(bool bOn);
		void TurnLeft(bool bOn);
		void TurnRight(bool bOn);
		void StartAnimation(unsigned Time);
		void Animate(unsigned Time);
		void UpdateMesh();
		void DrawSkeleton();
		void Draw();
		void MoveFromTo(const Point3D &Origin, const Point3D &Destination);
		void renderBitmapString(float x, float y, float z, void *font, const char *string) const;
		void set_CadeauNbr(int n);
		
		const Reference3D& GetRef() {
			return this->MainRoot->Ref;
		}
};

#endif
