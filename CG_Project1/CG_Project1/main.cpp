#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <string>

#include "Shape.h"
#include "CameraView.h"

using namespace std;

//CONSTANTS AND MACROS
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 480

//Windows
int window1, window2;


//Rotation axis
char w1_axisRot = 'z'; //default set to z axis for window1

//Mouse interaction mode
bool interactionMode = true; //translate if true, false-> rotate

//Mouse coordinates
int window1_x, window1_y;

//Camera
CCameraView viewWindow(SCREEN_WIDTH, SCREEN_HEIGHT);

//Creates the shape object to be used
Shape *shape = new Shape();

void display()
{
	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	// Define material and light
     float lt_posit[4] = {  5.0f,  5.0f,  30.0f, 0.0f };
     float lt_ambi[4]  = {   0.5f,   0.5f,   0.5f, 1.0f };
     float lt_diff[4]  = {   1.0f,   1.0f,   1.0f, 1.0f };
     float mat_ambi[4] = {   0.1f,   0.3f,   0.3f, 1.0f };
     float mat_diff[4] = {   0.4f,   0.6f,   0.6f, 1.0f };
     float mat_spec[4] = {   0.3f,   0.3f,   0.3f, 1.0f };

     glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambi);
     glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diff);
     glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_diff);
     glMaterialf( GL_FRONT, GL_SHININESS, 10);

     glLightfv(GL_LIGHT0, GL_AMBIENT, lt_ambi);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, lt_diff);
     glEnable(GL_LIGHT0);

     glLightfv(GL_LIGHT0, GL_POSITION, lt_posit);

	  // Call functions to perform OpenGL projection, viewing, modeling and object drawing
	 viewWindow.setShape(*shape);
	 viewWindow.projection();
	 viewWindow.draw();



	glFlush();
	glutSwapBuffers();

}

void mouseInput(int button, int state, int x, int y)
{
	if (button = GLUT_LEFT_BUTTON)
	{
		window1_x = x;
		window1_y = y;
	}
}

void mouseMotion(int x,int y)
{

	// this will change object parameters

	double dx = (double)x-window1_x; 
	double dy = (double)y-window1_y;


	if(interactionMode) //translates
	{	
		
		shape->setTx(shape->getTx()+dx/50);
		shape->setTy(shape->getTy()-dy/50);
	
	}
	else //rotates using dx only
	{ 

		switch(w1_axisRot){
			case 'x':
				shape->setRx(shape->getRx()+dx/5);
				break;
			case 'y':
				shape->setRy(shape->getRy()+dx/5);
				break;
			case 'z':
				shape->setRz(shape->getRz()+dx/5);
				break;
			default:
				break;
		}

	}

	window1_x=x;
	window1_y=y;
	
	// update camera view
	display();

}

void keyboardInput(unsigned char key, int x, int y)
{
	string fileName;

	switch (key)
	{
		//key is not case sensitive

		case 'q': //quits the program
		case 'Q':
			exit(0);
		break;
		
		case 'o': //reads new file
		case 'O':
			cout << "Please type the filename:" << endl;
			cin >> fileName;
			shape->readfile(fileName);
			break;

		case 'c'://reads default .obj file -> "cube.obj"
		case 'C':
			shape->readfile("cube.obj");
			break;
		
		case '+':	// scaling up object
			shape->setScale(shape->getScale()+0.1);
			cout << "Scaled up object" << endl;
			break;
		case '-': //scaling down object
			shape->setScale(shape->getScale()-0.1);
			cout << "Scaled down object" << endl;
			break;

		case 'p': //enables polygon mode
		case 'P':
			shape->setWire(false);
			cout << "Polygon Mode Enabled.\n";
			break;

		case 'w': //enables wireframe mode
		case 'W':
			shape->setWire(true);
			printf("Wireframe Mode Enabled.\n");
			break;

		case 'x':		// change rotation axis to x
		case 'X':
			w1_axisRot = 'x';
			cout << "Rotation axis set to X" << endl;
			break;
		case 'y':		// change rotation axis to y
		case 'Y':
			w1_axisRot = 'y';
	        cout << "Rotation axis set to Y" << endl;
			break;
		case 'z':		// change rotation axis to z
		case 'Z':
			w1_axisRot = 'z';
			cout << "Rotation axis set to Z" << endl;
			break;

		//turns on rotation
		case 'r':
		case 'R':
			interactionMode=false; 
			cout << "Rotation enable" << endl;
			break;

		//turns on translation
		case 't':
		case 'T':
			interactionMode =true;
			cout << "Translation Enabled" << endl;
			break;

		case 's': //smooth shading mode enabled
		case 'S':
			glShadeModel(GL_SMOOTH);
			shape->setSmooth(true);
			cout << "Smooth Shading Enabled.\n";
			break;

		case 'f': //flat shading mode enabled
		case 'F':
			glShadeModel(GL_FLAT);
			shape->setSmooth(false);
			cout << "Flat Shading Enabled.\n";
			break;

		case 'n'://turns drawing normal mode on/off
		case 'N': 
			shape->setNormals(!shape->getNormals());
			cout << "Normal drawing mode toggled" << endl;
			break;

		case 'h':
		case 'H':
				cout << "Enter file name to write object to: ";
				cin >> fileName;
				shape->writeFile(fileName);	
			break;

		case 'k':
		case 'K':
				cout << "Making surface mesh(cylinder)" << endl;
				shape->makeSurfaceMesh();
			break;

		case 'd':
		case 'D':
				cout << "Added/removed cone to view" << endl;;
				shape->setSphereFlag(false); //deactives the other object
				shape->setConeFlag(!shape->getConeFlag());
				break;
		case 'l':
		case 'L':
				cout << "Added/removed sphere to view" << endl;
				shape->setConeFlag(false); //deactives the other object
				shape->setSphereFlag(!shape->getSphereFlag());
				break;

		default: //invalid option
			break;
	}

	//updates display
	display();

}

void init(int window_id)
{
	glutSetWindow(window_id);
	glClearColor(0.0f,0.0f,0.0f,0.0f); //color set to black
	glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	//shading model specs
	glShadeModel(GL_SMOOTH);

	glEnable(GL_NORMALIZE);

	// Polygon mode is set to fill
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//read .obj file
	shape->readfile("cube.obj");

	//Sets them off by default(cone and sphere)
	shape->setConeFlag(false);
	shape->setSphereFlag(false);
}

void main(int argc, char **argv)
{
	glutInit(&argc,argv); //initializes glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);

	//creates the first window
	window1 = glutCreateWindow("Camera View");

	init(window1);

	glutDisplayFunc(display);
	glutMouseFunc(mouseInput);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboardInput);

	//window 2
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
	glutInitWindowPosition(300, 300);
	window2 = glutCreateWindow("Second Camera View");

	init(window2);

	glutDisplayFunc(display);
	glutMouseFunc(mouseInput);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboardInput);

	glutMainLoop();

}