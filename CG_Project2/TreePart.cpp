// TreePart.cpp: implementation of the CTreePart class.
//
//////////////////////////////////////////////////////////////////////

#include "TreePart.h"
 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// recursively construct a treepart of a particular depth, with specified branching factor, etc.
CTreePart::CTreePart(CRand rgen, int depth, int numBranch, double partLen, double partWid, double partTz, double partRx, double partRz)
{
	glPushMatrix();

	Tz = partTz;
	Rx = partRx;
	Rz = partRz;

	if (depth<=0)
	{  // leaf level, depth==0
		this->leaf = true;
		this->length=partLen;
		this->width=partLen*0.5;
	}else{
		//branch

		
		this->leaf=false;
		this->length = (double) (rgen.randg()) * partLen/4 + partLen/1.5;
		this->width = (double) (rgen.randg()) * partWid/4 + partWid/1.5;

		double Rx;
		double Rz;
		double ZOffSet = (rgen.randu())*360;

		//Adds a new branch to the part vector depending on the number of branches there is:
		for (int counter = 0; counter < numBranch; counter++)
		{
			//Rx = (double) (counter + 1) * rgen.randg() *360.0/numBranch;
			Rx = (double) (RX_MIN + rgen.randg() * (RX_MAX - RX_MIN) );
			Rz = (double) counter * 360.0/numBranch + (rgen.randu()) * Z_ROT + ZOffSet;
			parts.push_back(new CTreePart(rgen, depth - 1, numBranch, this->length, this->width, this->length, Rx, Rz));
		}
		
		
		
	}
	glPopMatrix();
}


CTreePart::~CTreePart()
{

	for (unsigned int i=0; i< this->parts.size(); i++){
		delete this->parts[i];
	}

}

// recursively draw a tree component
// first, place the component using transformation for this subtree
// second, draw leaf (if this is a leaf)
// third, draw subtree (if this is an interirior node): draw this node, then recursively all its children
void CTreePart::draw(int cylDisplayList, bool setColor)
{
	glPushMatrix();

	// place this component
	glTranslated(0, 0, Tz);
	glRotated(Rz, 0, 0, 1);
	glRotated(Rx, 1, 0, 0);

	if (leaf) {
		if (setColor)
			glColor3d(0.2, 1.0, 0.1);

		glNormal3d(0, 0, 1);

		// rectangular leaf
		glBegin(GL_POLYGON);
		glVertex3d(0, 0, 0);
		glVertex3d(width/2.0, 0, length/2.0);
		glVertex3d(0, 0, length);
		glVertex3d(-width/2.0, 0, length/2.0);
		glEnd();
	}else{
		if(setColor)
			glColor3d(0.6, 0.6, 0.1);

		glPushMatrix();
		glScaled(width, width, length);
		glCallList(cylDisplayList);
		glPopMatrix();

		// recursively draw the children
		for (unsigned int i=0; i< this->parts.size(); i++){
			this->parts[i]->draw(cylDisplayList, setColor);
		}
	}
	glPopMatrix();
}

