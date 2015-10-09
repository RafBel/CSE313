

#include "Mesh.h"

Mesh::Mesh()
{
	shape = new Shape();

}


Mesh::Mesh(Shape *shape2)
{
	shape = shape2;
}

Mesh::~Mesh()
{
	//empties vector
	vVector.clear();
	fVector.clear();
}

//Calculates face normals
void Mesh::Newell()
{
	unsigned fCounter, vCounter;
	double nx = 0; double ny = 0; double nz = 0; //normal coordinates
	double length; double centerX = 0; double centerY = 0; double centerZ = 0;

	//for every face
	for (fCounter = 0; fCounter < fVector.size(); fCounter++)
	{
		//for loop for nx, ny, and nz
		for (vCounter = 0; vCounter < (fVector.at(fCounter).vectID.size() - 1) ; vCounter++)
		{
			//nx = sum (yi - ynext)(zi + znext)
			nx += ( vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getY() - vVector.at(fVector.at(fCounter).getVectorID(vCounter + 1)).getY() )
				* (vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getZ() + vVector.at(fVector.at(fCounter).getVectorID(vCounter + 1)).getZ() );

			//ny = sum (zi - znext)(xi + xnext)
			ny += ( vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getZ() - vVector.at(fVector.at(fCounter).getVectorID(vCounter + 1)).getZ() )
				* (vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getX() + vVector.at(fVector.at(fCounter).getVectorID(vCounter + 1)).getX() );


			//nz = sum (xi - xnext)(yi + ynext)
			nz += ( vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getX() - vVector.at(fVector.at(fCounter).getVectorID(vCounter + 1)).getX() )
				* (vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getY() + vVector.at(fVector.at(fCounter).getVectorID(vCounter + 1)).getY() );

			//updates center of face coords 
			centerX += vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getX()/fVector.at(fCounter).vectID.size() ;
			centerY += vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getY()/ fVector.at(fCounter).vectID.size();
			centerZ += vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getZ() / fVector.at(fCounter).vectID.size();

		}
		//For last position (since next position is the 0 position in the vector)
		nx += ( vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getY() - vVector.at(fVector.at(fCounter).getVectorID(0)).getY() )
				* (vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getZ() + vVector.at(fVector.at(fCounter).getVectorID(0)).getZ() );

		ny += ( vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getZ() - vVector.at(fVector.at(fCounter).getVectorID(0)).getZ() )
				* (vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getX() + vVector.at(fVector.at(fCounter).getVectorID(0)).getX() );

		nz += ( vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getX() - vVector.at(fVector.at(fCounter).getVectorID(0)).getX() )
				* (vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getY() + vVector.at(fVector.at(fCounter).getVectorID(0)).getY() );

		//updates center of face coords 
		centerX += vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getX() / fVector.at(fCounter).vectID.size();
		centerY += vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getY() / fVector.at(fCounter).vectID.size();
		centerZ += vVector.at(fVector.at(fCounter).getVectorID(vCounter)).getZ() / fVector.at(fCounter).vectID.size();

		//Normalizes normal value 
		length = sqrt( pow(nx, 2) + pow(ny, 2) + pow(nz,2) );
		nx = nx/length;
		ny = ny/length;
		nz = nz/length;

		fVector.at(fCounter).setNormal(nx,ny,nz); //records the coord values for the normal vector for this face

		//Stores the face center coords
		fVector.at(fCounter).faceCenter.setCoord(centerX,centerY,centerZ);

		//resets the values
		nx = 0;
		ny = 0;
		nz = 0;

		centerX = centerY = centerZ = 0;
	}

}

//Calculates vertex normals
void Mesh::Gourand()
{
	unsigned searchCounter = 0; unsigned faceCounter = 0; unsigned normalCounter;
	double length;

	//initializes all normals
	for (vector <Vector3D>::iterator it = vVector.begin() ; it != vVector.end(); ++it) { nVector.push_back( Vector3D(0,0,0) ) ; }

	//for each face
	for (vector <Face>:: iterator fIt = fVector.begin() ; fIt != fVector.end(); ++fIt)
	{
		//updates normal value if that vertex belongs to that face being analyzed
		for (vector <IDVert>::iterator vIt = fVector.at(faceCounter).vectID.begin(); vIt != fVector.at(faceCounter).vectID.end(); ++vIt)
		{

			//adds the normal value
			nVector.at( fVector.at(faceCounter).vectID.at(searchCounter).getnID() ).addCordValue( fVector.at(faceCounter).faceNormal.getX(),
				fVector.at(faceCounter).faceNormal.getY(), fVector.at(faceCounter).faceNormal.getZ());

			searchCounter++;
		}

		searchCounter = 0;
		faceCounter++;
	}

	//normalizes normals for every vertex
	for (normalCounter = 0; normalCounter < nVector.size(); ++normalCounter )
	{
		//calculates the denominator
		length = sqrt( pow( nVector.at(normalCounter).getX(), 2) + pow( nVector.at(normalCounter).getY(), 2) + pow( nVector.at(normalCounter).getZ(), 2 ) );
		
		//normalizes the value for that specific vertex
		nVector.at(normalCounter).setCoord( nVector.at(normalCounter).getX()/length , 
			nVector.at(normalCounter).getY()/length, nVector.at(normalCounter).getZ() /length);
	}


}

//reads mesh from a OBJ file
void Mesh::readFile(string filename)
{
	ifstream in(filename.c_str());

	string key;
	double cordX,cordY,cordZ;
	int vertexIndex;
	IDVert vertID;
	Face face;
	Vector3D coord;

	//empties the vertex, face and normal vector before reading another file
	vVector.clear();
	fVector.clear();
	nVector.clear();

	//reading the obj file like its a text file
	in >> key;
	while (1) //loop goes on until break
	{
		//vertex
		if (key == "v")
		{
			in >> cordX >> cordY >> cordZ;
			coord.setCoord(cordX,cordY,cordZ);
			vVector.push_back(coord);
			if(!(in >> key))
				break;
		}
		
		//face
		else if( key == "f")
		{
			while((in >> key) && key[0]>='0' && key[0]<='9')
			{
	
				vertexIndex = atoi(key.c_str());
				
				
				vertID.setID(vertexIndex - 1, vertexIndex - 1);
				face.addVertex(vertID);

			}
			//adds the face to the face list
			fVector.push_back(face);
			//wipes the vertex list on the face clean
			face.clear();
		}

		//other info not needed on the file
		else
		{
			getline(in,key);
			if(!(in>>key))
				break;
		}
	}

	//Newell Method call
	Newell();

	//Gourand Method call
	Gourand();

	//terminates file reading
	in.close(); 

}

void Mesh::drawMesh()
{
	unsigned vCounter;
	int vID;


	//glColor3f(1,1,1); //drawing color set to white
	//for every face
	for (unsigned faceCounter = 0; faceCounter < fVector.size(); ++faceCounter)
	{
		glColor3f(1,1,1);
		if (!shape->getWire() )
		{
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glBegin(GL_POLYGON);
		}

		else 
		{
			glDisable(GL_LIGHTING);
			glBegin(GL_LINE_LOOP);
		}

		//for every vertex in that face
		for (vCounter = 0; vCounter < fVector.at(faceCounter).vectID.size(); vCounter++)
		{
			vID = fVector.at(faceCounter).vectID.at(vCounter).getvID() ;
			if(shape->getSmooth())
				glNormal3f( nVector.at( fVector.at(faceCounter).vectID.at(vCounter).getnID() ).getX(),
				nVector.at(fVector.at(faceCounter).vectID.at(vCounter).getnID() ).getY(), nVector.at(fVector.at(faceCounter).vectID.at(vCounter).getnID()).getZ() );
			else
				glNormal3f(fVector.at(faceCounter).faceNormal.getX(), fVector.at(faceCounter).faceNormal.getY(), fVector.at(faceCounter).faceNormal.getZ());

			glVertex3f(vVector.at(vID).getX(), vVector.at(vID).getY(), vVector.at(vID).getZ());
		}

		glEnd();

	}


	//draws normals if mode is toggled on
	if(shape->getNormals()) 
	{
		glDisable(GL_LIGHTING);
		glColor3f(0, 1, 0);
		glBegin(GL_LINES);

		//If smooth shading mode is active -> draw normal coming from each vertex
		if ( shape->getSmooth() )
		{	

			for ( unsigned vCounter = 0; vCounter < vVector.size() ; vCounter++) 
			{
				//draws normal using vertex position
				glVertex3d(vVector.at(vCounter).getX() , vVector.at(vCounter).getY() , vVector.at(vCounter).getZ() );
				glVertex3d(vVector.at(vCounter).getX() + nVector.at(vCounter).getX()*NORMAL_LFACTOR/shape->getScale() , 
					vVector.at(vCounter).getY() + nVector.at(vCounter).getY()*NORMAL_LFACTOR/shape->getScale() ,
					vVector.at(vCounter).getZ() + nVector.at(vCounter).getZ()*NORMAL_LFACTOR/shape->getScale()  );
			}

		}

		//If flat shading mode is active -> draws normal coming from the center of the face	
		else
		{
			for (unsigned fCounter = 0; fCounter < fVector.size(); fCounter++)
			{
				//draws normal using face center positions

				glVertex3d(fVector.at(fCounter).faceCenter.getX(), fVector.at(fCounter).faceCenter.getY(), fVector.at(fCounter).faceCenter.getZ() );
					glVertex3d(fVector.at(fCounter).faceCenter.getX() + fVector.at(fCounter).faceNormal.getX()*NORMAL_LFACTOR/shape->getScale(),
					fVector.at(fCounter).faceCenter.getY() + fVector.at(fCounter).faceNormal.getY()*NORMAL_LFACTOR/shape->getScale() , 
					fVector.at(fCounter).faceCenter.getZ() + fVector.at(fCounter).faceNormal.getZ()*NORMAL_LFACTOR/shape->getScale()  );
			}
		}

		glEnd();

	}
	
	/*Note: 
			Division by the scaling factor was used so if scaled too much, the normal vectors wouldn't be really big meaning the user wouldn't be able
			to see the model properly.
	*/

}

void Mesh::writeFile(string fileName)
{
	ofstream out(fileName.c_str());

	out << setprecision(6) << fixed; //precision

	//writing vertex first 
	for (vector<Vector3D>:: iterator vertIt = vVector.begin(); vertIt != vVector.end(); ++vertIt)
	{
		//writes v first for vertex and then the coords
		out << "v " << vertIt->getX() << " " << vertIt->getY() << " " << vertIt->getZ() << endl;
	}

	//now writes faces
	for (vector <Face>:: iterator faceIt = fVector.begin(); faceIt != fVector.end() ; ++faceIt)
	{
		out << "f";
		for (int IDcounter = 0; IDcounter < faceIt->vectID.size() ; ++IDcounter)
		{
			out << " " << faceIt->vectID.at(IDcounter).getvID() + 1;
		}
		out << endl;
	}

	out.close(); //closes the ofstream

}

void Mesh::makeSurfaceMesh()
{
	//For cylinder:
	float const radius = 1.0;
	float const height = 3.0;



	//clears the vectors so the new data can be loaded
	vVector.clear();
	fVector.clear();
	nVector.clear();

	//Using the skeleton code on the slides as reference
	int i,j,numValsU = 40; int numValsV = 40;
	double u, v; 
	//double uMin = -10.0, vMin = -10.0, uMax = 10.0, vMax = 10.0;
	double uMin = 0, vMin = 0, uMax = 2*PI, vMax = 1;

	double delU = (uMax - uMin)/(numValsU - 1);
	double delV = (vMax - vMin)/(numValsV - 1);
	IDVert idvert;
	Vector3D vect;
	Face face;

	//vVector.resize(numValsU* numValsV + numValsV);
	//nVector.resize(numValsU* numValsV + numValsV);
	//fVector.resize( (numValsU - 1)* (numValsV - 1) + (numValsV - 1) );


	for (i = 0, u = uMin; i < numValsU; i++, u += delU)
		for (j=0,v=vMin; j < numValsV;  j++, v += delV)
		{
			int whichVert = i * numValsV + j; //index for vertex and normal

			//vVector.at(whichVert).setCoord(radius * cos(u) ,radius * sin(u) ,height * v);
			vect.setCoord(radius * cos(u) ,radius * sin(u) ,height * v);
			vVector.push_back(vect);


			if (i>0 && j>0)
			{
				int whichFace = (i - 1) * (numValsV - 1) + (j -1 );
				idvert.setID(whichVert,whichVert);
				face.vectID.push_back(idvert);
				//fVector.at(whichFace).vectID.push_back(idvert);

				idvert.setID(whichVert - 1,whichVert - 1);
				//fVector.at(whichFace).vectID.push_back(idvert);
				face.vectID.push_back(idvert);

				idvert.setID(whichVert - numValsV - 1,whichVert - numValsV - 1);
				//fVector.at(whichFace).vectID.push_back(idvert);
				face.vectID.push_back(idvert);

				idvert.setID(whichVert - numValsV,whichVert - numValsV);
				//fVector.at(whichFace).vectID.push_back(idvert);
				face.vectID.push_back(idvert);

				fVector.push_back(face);

				face.clear();
			}

		}	

	//Newell Method call
	Newell();

	//Gourand Method call
	Gourand();




}

