#ifndef _MESH_H_
#define _MESH_H_

class Triangle
{
public:
	
	int Vertex_Index[3];
	int Normal_Index[3];

	Vector3D Normal(Point3D *PArray) {
		Vector3D u(PArray[Vertex_Index[0]],PArray[Vertex_Index[1]]);
		Vector3D v(PArray[Vertex_Index[0]],PArray[Vertex_Index[2]]);
		Vector3D N;
		N.CrossProduct(u,v);
		N.Normalize();
		return N;
	}
};

class Mesh
{
public:

	int VertexCount;
	int NormalCount;
	int TriangleCount;
	Point3D *VertexArray;
	Vector3D *NormalArray;
	Triangle *TriangleArray;

	Mesh() {
		VertexCount = NormalCount = TriangleCount = 0;
		VertexArray = NULL;
		NormalArray = NULL;
		TriangleArray = NULL;
	}

	~Mesh() {
		delete [] VertexArray;
		delete [] NormalArray;
		delete [] TriangleArray;
	}

	void Set(int index, int a, int b ,int c, int na, int nb, int nc) {
		TriangleArray[index].Vertex_Index[0] = a;
		TriangleArray[index].Vertex_Index[1] = b;
		TriangleArray[index].Vertex_Index[2] = c;
		TriangleArray[index].Normal_Index[0] = na;
		TriangleArray[index].Normal_Index[1] = nb;
		TriangleArray[index].Normal_Index[2] = nc;
	}
};

#endif
