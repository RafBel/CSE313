#include "Face.h"

Face::Face( ){ } // constructor
	
Face::~Face( ){vectID.clear();} // destructor


void Face::addVertex(IDVert vertID)
{
	vectID.push_back(vertID);
}

void Face::clear() {vectID.clear();}

unsigned Face::getSize() { return ( vectID.size() ) ; }


void Face::setNormal(double x, double y , double z) { faceNormal.setCoord(x,y,z); }

int Face::getVectorID(unsigned position)
{
	return vectID.at(position).getvID();
}

