#ifndef FACE_H
#define FACE_H

#include <vector>

#include "Vector3D.h"
#include "IDVert.h"

using namespace std;

class Face 
{
	friend class Mesh;

public:
	Face();
	~Face();

	//methods
	void addVertex(IDVert);
	void clear();
	unsigned getSize();
	void setNormal(double, double , double);
	int getVectorID(unsigned);

private:
	//attributes
	Vector3D faceNormal; //normal of this face
	Vector3D faceCenter;
	vector <IDVert> vectID; //this vector serves as a list to save all the vertex and their normals for this face

	//methods


};

#endif