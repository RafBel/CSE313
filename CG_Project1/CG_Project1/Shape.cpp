#include "Shape.h"

 
 
//Resembles the Shape.cpp given in the skeleton
Shape::Shape()
{
	
	tx = 0.0;
	ty = 0.0;
	tz = -0.5;
	rx = 0.0;
	ry = 0.0;
	rz = 0.0;
	scale = 1.0;
	smooth = false;  // true    // smooth shading or not
	normals = false;  // true   // draw normal or not
	wire =  true;	
	//wire = false;
	
	
	mesh = new Mesh(this);
	//mesh->makeSurfaceMesh();  // read in a mesh, make a tesselated mesh, etc.
}


Shape::~Shape(){

	delete mesh;
}

Shape& Shape::operator=(const Shape& rhs)
{
	tx = rhs.tx;
	ty = rhs.ty;
	tz = rhs.tz;
	rx = rhs.rx;
	ry = rhs.ry;
	rz = rhs.rz;
	scale = rhs.scale;
	smooth = rhs.smooth;
	normals = rhs.normals;
	wire = rhs.wire;
	return * this;
}


void Shape::draw()
{
	mesh->drawMesh();

	
}

void Shape::drawCone()
{
	if (coneFlag == true)
	{
		glColor3f(1,1,1);
		if (wire == true)
		{
				glTranslated(3.0,3,-6);
				glutWireCone(3.0, 3.0, 3, 4);
		}
		else
		{
				glEnable(GL_LIGHTING);
				glTranslated(3,3,-6);
				glutSolidCone(3.0, 3.0, 3, 4);
		}
	}
}

void Shape::drawSphere()
{
	if (sphereFlag == true)
	{
		glColor3f(1,1,1);
		if (wire == true)
		{
			glTranslated(-5.0,-3,-6);
			glutWireSphere(2.5,50, 40);
		}
		else
		{
			glEnable(GL_LIGHTING);
			glTranslated(-5.0,-3,-6);
			glutSolidSphere(2.5,50, 40);
		}
	}
}


void Shape::readfile(string filename)
{
	mesh->readFile(filename);
}

void Shape::writeFile(string filename)
{
	mesh->writeFile(filename);
}

void Shape::makeSurfaceMesh() { mesh->makeSurfaceMesh(); }