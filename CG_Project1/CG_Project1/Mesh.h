#ifndef MESH_H
#define MESH_H

#define PI 3.1415

#include <string>
#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Vector3D.h"
#include "Face.h"
#include "IDVert.h"
#include <math.h>
#include <iomanip>


#include "Shape.h"

class Shape;

using namespace std;

class Mesh {

public:
	Mesh();
	Mesh(Shape *shape2);

	~Mesh();

	//methods 
	void readFile(string);
	void drawMesh();
	void writeFile(string);
	void makeSurfaceMesh();

private:
	//attributes
	vector <Vector3D> vVector; //stores all vertexes in a list
	vector <Face> fVector; //stores all faces in a list
	vector <Vector3D> nVector; //stores all normals
	Shape *shape;

	//methods
	void Gourand();
	void Newell();



};

#endif