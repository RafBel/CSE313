#ifndef IDVERT_H
#define IDVERT_H

//this class separates the two types of IDs: vertex and normal
class IDVert
{

public:
	IDVert();

	//methods
	void setID(int, int);
	int getvID();
	int getnID();

private:
	//attributes
	int vertexID;
	int normalID;

};


#endif