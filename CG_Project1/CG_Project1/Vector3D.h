
#ifndef VECTOR3D_H
#define VECTOR3D_H

#define NORMAL_LFACTOR 0.1

class Vector3D
{

public:
	//constructors
	Vector3D();
	Vector3D(double ,double , double );

	//methods
	double getX();
	double getY();
	double getZ();
	
	void setCoord(double , double , double);
	void addCordValue(double , double  , double );

private:
	//attributes
	double cordX,cordY,cordZ;

	//methods




};

#endif