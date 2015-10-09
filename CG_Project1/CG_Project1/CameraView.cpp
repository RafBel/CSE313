
#include "CameraView.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCameraView::CCameraView(int w, int h)
{

	width = w;
	height = h;

	cam.init();

}


CCameraView::~CCameraView()
{
	delete shape;
}

void CCameraView::projection()
{

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glFrustum(cam.getLeft(), cam.getRight(), cam.getBottom(), cam.getTop(), cam.getNear(), cam.getFar());

}

void CCameraView::draw()  
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// viewing transformations
	cameraTransformation();

	glPushMatrix();
		// modeling transformations
		shapeTransformation();
		shape->draw();
		shape->drawCone();
		shape->drawSphere();
	glPopMatrix();

}


void CCameraView::cameraTransformation()
{
	//Translation:
	glTranslated(cam.getTx(), cam.getTy(), cam.getTz() ); //Translates the camera

	//Rotation:
	glRotated(cam.getXRoll(), 1 , 0, 0); //rotates about x-axis
	glRotated(cam.getYRoll(), 0 , 1, 0); //rotates about y-axis
	glRotated(cam.getZRoll(), 0 , 0, 1); //rotates about z-axis
}


void CCameraView::shapeTransformation()
{
	//Translates the shape
	glTranslated(shape->getTx(), shape->getTy(), shape->getTz() );

	//Scaling
	glScaled(shape->getScale(), shape->getScale(), shape->getScale() );

	//Rotation:
	glRotated(shape->getRx(), 1 , 0 , 0); //rotates about x-axis
	glRotated(shape->getRy(), 0 , 1 , 0); //rotates about y-axis
	glRotated(shape->getRz(), 0 , 0 , 1 );//rotates about z-axis

}

