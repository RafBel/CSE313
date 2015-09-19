/*Computer Graphics - Homework 01 
Code written by Rafael C. B. de Oliveira*/

#include <iostream>
#include <Windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "hw1_header.h"


//global variables:
//Screen specs:
int spiralWidth = 0; int spiralHeight = 0;

//Spiral specs:
double maxK = DEFAULT_MAXK_VALUE; double A = DEFAULT_A_VALUE; //sets the default values

//Swing attributes
bool swingInc; bool swingDec = false;

//Flipping attributes
int left = -WIDTH_DEFAULT/2; int right = WIDTH_DEFAULT/2; int bottom = -HEIGHT_DEFAULT/2; int top = HEIGHT_DEFAULT/2; //default values
int tempFlip; //holds a temporary value for a flipping axis


//Rotation attribute
double rotation = 0;

//Changing spiral color (hue)
float hue;
bool colorSpiral = false; //default is off

//determines if Fading is on or off
bool fadingMode = false; //default is off (false)

float fadingColor(double currentTheta, double maxTheta) {return ((float) (1.0 - 1.0*currentTheta/maxTheta)); }

//generates a random color ID using the rand operator
double randomColor() { return (double) (rand()%255)/255; }

//Convertion from HSV to RGB
void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
	int i;
	float f, p, q, t;
	if( s == 0 ) {
		// achromatic (grey)
		*r = *g = *b = v;
		return;
	}
	h = h/60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}
}

//enables swing mode when 'w' is pressed on the keyboard
void swingMode(int value)
{
	//increases or decreases the value of A depending on what it is supposed to do
	if (swingInc == true) {A = A + 0.1; }
	if (swingDec == true) {A = A - 0.1; }

	glutPostRedisplay();

	if (A >= MAX_A_VALUE) //checks if A should start decreasing
	{
		swingInc = false;
		swingDec = true;
	}

	if( (A - 0.1) <= MIN_A_VALUE) {swingDec = false; } //checks if swing mode should stop

	//keeps running until both arguments are false
	if ((swingInc != false) || (swingDec != false)) { glutTimerFunc(200,swingMode,0); } //sets a delay of 200 between animations
}

void reshape(int x, int y) //responsible for keeping the aspect ratio the same
{
	float ratio = (float) WIDTH_DEFAULT/HEIGHT_DEFAULT;
	float currentRatio = (float) x/y;

	if (ratio > currentRatio )
		glViewport(0, 0, (float) x, x/ratio);
	else if (ratio < currentRatio)
	{
		glViewport(0, 0, y*ratio,(float) y);
	}

	else
		glViewport(0, 0, x, y); // no need to change, since already have same aspect ratio
}


void myInit(void)
{
	glClearColor(0.0,0.0,0.0,0.0); //sets default background color to black
	glPointSize(1.0); 
	glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
	gluOrtho2D (-WIDTH_DEFAULT/2, WIDTH_DEFAULT/2, -HEIGHT_DEFAULT/2, HEIGHT_DEFAULT/2);
}

void myDisplay(void)
{
	double radius;
	float red, green, blue; 


	glClear(GL_COLOR_BUFFER_BIT); //clears the screen
	glColor3f(1.0f,1.0f,1.0f); //sets default drawing -> white
	glBegin(GL_LINE_STRIP); //draws the spiral based on the specifications the user demanded 
		for ( double theta = 0; theta < maxK * PI_TWO; theta = theta + THETA_VARIATION) //connects at intervals of theta
		{
			radius = A*theta; 
			if (fadingMode == true) //if fading mode is on, will draw the spiral with the fading settings
				glColor3f(fadingColor(theta, maxK*PI_TWO), fadingColor(theta, maxK*PI_TWO), fadingColor(theta, maxK*PI_TWO));

			if (colorSpiral == true) //if spiral coloring mode is on, will draw spiral that changes color smoothly with the theta variation
			{
				hue = theta*360/(PI_TWO*maxK);
				HSVtoRGB(&red,&green,&blue,hue,theta/(PI_TWO*maxK),theta/(PI_TWO*maxK));
				glColor3f(red, green, blue);
			}
			glVertex2d( spiralWidth + radius*cos(theta + rotation), spiralHeight + radius*sin(theta + rotation));

		}
	glEnd();
   glutSwapBuffers();
}

void myKeyboard(unsigned char key, int mouseX, int mouseY)
{
	switch(key)
	{
	case 'q': //terminate program:
		exit(-1);
		break;

	case 'b': //changes background color to a random color
		glClearColor( randomColor(),  randomColor(),  randomColor(), 0.0);
		glutPostRedisplay();
		break;

	case 'c': //changes background color back to black
		glClearColor(0.0,0.0,0.0,0.0);
		glutPostRedisplay();
		break;

	case 'a': //increases the value of A
		if (A <= MAX_A_VALUE) //won't increase past the max value set for A
			A = A + 0.1;
		glutPostRedisplay();
		break;
	
	case 's': //Decreases the value of A
		if (A > MIN_A_VALUE) //won't decrease past the min value set for A
			A = A - 0.1;
		glutPostRedisplay();
		break;

	case 'w': //Swing-type mode
		swingInc = true;
		swingMode(0);
		break;

	case 'f': //Fading ON/OFF
		fadingMode = !fadingMode;
		colorSpiral = false; //turns off colorSpiral so it turns off, so fading mode can be seen
		glutPostRedisplay();
		break;

	case 'u': //translates spiral +y
		if (spiralHeight < SCREEN_HEIGHT_MAX) //doesnt translate past certain +y point
			spiralHeight += 10;
		glutPostRedisplay();
		break;

	case 'i': //translates spiral -y
		if (spiralHeight > SCREEN_HEIGHT_MIN) //doesnt translate past certain -y point
			spiralHeight -= 10;
		glutPostRedisplay();
		break;
	
	case 'j': //translates spiral +x
		if (spiralWidth < SCREEN_WIDTH_MAX)
			spiralWidth += 10;
		glutPostRedisplay();
		break;

	case 'k': //translates spiral -x
		if (spiralWidth > SCREEN_WITDH_MIN)
			spiralWidth -= 10;
		glutPostRedisplay();
		break;

	case 'z': //changes background color to white
		glClearColor(1.0f,1.0f,1.0f,0.0);
		glutPostRedisplay();
		break;

	case 'o': //translates spiral back to the default origin point
		spiralWidth = 0;
		spiralHeight = 0;
		glutPostRedisplay();
		break;

	case 'r': //rotates spiral
		if (rotation >= PI_TWO) //prevents having to store a big value and causing issues
			rotation = 0;
		rotation += PI_THIRD;
		glutPostRedisplay();
		break;

	case 'h': //color changes smoothly for spiral
		colorSpiral = !colorSpiral; //turns on/off the color variance
		fadingMode = false; //turns off fading mode to avoid issues
		glutPostRedisplay();
		break;

	case 'n': //flipping x axis
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		//Swaps left and right
		tempFlip = left;
		left = right;
		right = tempFlip;

		gluOrtho2D (left, right, bottom, top);
		glutPostRedisplay();
		break;

	case 'm': //flipping y axis
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		//Swaps bottom and top
		tempFlip = bottom;
		bottom = top;
		top = tempFlip;

		gluOrtho2D (left, right, bottom, top);
		glutPostRedisplay();
		break;

	default:
		break; //do nothing
	}

}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON) //left mouse click increases value of maxK
		{ 
			if (maxK <= MAX_K_VALUE)
				maxK++; 
		}
		else if (button == GLUT_RIGHT_BUTTON) //right mouse click decreases value of maxK
		{
			if (maxK >= MIN_K_VALUE)
				maxK--;
		}
			
		glutPostRedisplay(); //shows graphical changes
	}
}

void main(int argc, char **argv)
{
	glutInit(&argc,argv); // initializes the toolkit

	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB); //display mode is now set
	glutInitWindowSize(WIDTH_DEFAULT,HEIGHT_DEFAULT); //defines the window size to 600x480
	glutInitWindowPosition(100,100);
	glutCreateWindow("Archimedean Spiral"); //names window

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(reshape); //if manual reshaping of the window occurs, maintains aspect ratio

	myInit();

	glutKeyboardFunc(myKeyboard); //keyboard input

	glutMouseFunc(mouse); //mouse input

	glutMainLoop();

}