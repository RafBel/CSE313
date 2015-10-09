#ifndef SHAPE_H
#define SHAPE_H

#include "Mesh.h"

//Most of this class resembles the Shape class used in the skeleton given
class Shape 
{
	public:
		Shape();
		virtual	~Shape();
		void draw();
		void drawCone();
		void drawSphere();

		//Reads the file
		void readfile(string);

		//Writes the file
		void writeFile(string);

		void makeSurfaceMesh();
		
		//Returning values
		double getTx() {return tx;}
		double getTy() {return ty;}
		double getTz() {return tz;}
		double getRx() {return rx;}
		double getRy() {return ry;}
		double getRz() {return rz;}
		double getScale()  {return scale;}

		//Setting
		void setTx(double x) {tx=x;}
		void setTy(double y) {ty=y;}
		void setTz(double z) {tz=z;}
		void setRx(double x) {rx=x;}
		void setRy(double y) {ry=y;}
		void setRz(double z) {rz=z;}
		void setScale(double s)  {scale=s;}
		void setConeFlag(bool flag) {coneFlag = flag;}
		void setSphereFlag(bool flag) {sphereFlag = flag;}

		//Smooth shading
		void setSmooth(bool s){smooth = s;}
		bool getSmooth(){return smooth;}
		void setNormals(bool n){normals = n;}
		bool getNormals(){return normals;}
		bool getConeFlag(){return coneFlag;}
		bool getSphereFlag(){return sphereFlag;}

		void setWire(bool w){wire = w;}
		bool getWire(){return wire;}
		Shape& operator=(const Shape& rhs);
		
	protected:
		double tx, ty, tz, rx, ry, rz, scale;
		bool smooth, normals, wire;
		bool coneFlag;
		bool sphereFlag;

	private:
		Mesh* mesh;
};



#endif