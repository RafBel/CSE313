
#include "Vector3D.h"

Vector3D::Vector3D() {}

Vector3D::Vector3D(double x,double y,double z)
{
	cordX = x; cordY = y; cordZ = z;
}

double Vector3D::getX() {return cordX; }

double Vector3D::getY() {return cordY; }

double Vector3D::getZ() {return cordZ; }

void Vector3D::setCoord(double x, double y, double z)
{
	cordX = x; cordY = y; cordZ = z;
}

void Vector3D::addCordValue(double x, double y , double z)
{
	cordX += x; cordY += y; cordZ += z;
}