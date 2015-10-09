
#include "IDVert.h"

IDVert::IDVert() {
	vertexID = 0; normalID = 0; 
}

void IDVert::setID(int vID, int nID) { vertexID = vID; normalID = nID; }

int IDVert::getnID() {return normalID; }

int IDVert::getvID() {return vertexID;}
