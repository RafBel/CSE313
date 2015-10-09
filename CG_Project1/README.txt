========================================================================
    			Project 1  - Overview
		  Author: Rafael C. B. de Oliveira
========================================================================

Overview:
===========================

This program was made using Visual Studio 2012 Express, C++, and the OpenGL API for the CSE313 - Computer Graphics course.

Requirements to run the project: Visual Studio 2012 Express and the necessary OpenGL files.

The skeleton was used as reference for this project. Some classes were rewritten (Mesh, IDVert, Face, etc...), while others are similar to the skeleton(Camera, CameraView, etc...).
This program is able to:

		1. Set up a fulstrum-perspective projection for objects.

		2. Implement object and camera transformations (rotation,
		translation, and scaling). 

		3. When loading a .obj file, the program calculates the normals used for lighting

			- Able to implement Newell's Method for calculating face normals

			- Able to implement Gourand's Method for calculating vertex normals

		4. Draw vertex/face normals.


		.obj files included in this project:
		
			-bones.obj
			-bunny.obj
			-cow.obj
			-cube.obj
			-para.obj
			-cylinder.obj (created using this program)

Extra Credit:
===========================

-The program is able to write the current object to a file. The user will be asked for the desired file name. The file will be saved in the working directory.

-This program is able to produce a cylinder using tesselation.

-This program is able to add extra objects in a view by using glut-provided objects:  glutWireCone(), glutSolidCone(), glutWireSphere(), glutSolidSphere()
Note: For better understanding of the object, only one is shown at a time (cone or sphere). This was a decision made by the author. Also, normal mode and .obj writing only work for the
object (object read from file).

-This program creates an extra viewing window to show the view of a second camera in the scene.


Significant Modifications:
===========================

Normal.h and Normal.cpp : removed, was implemented as Vector3D in a different way.

VertexID.h and VertexID.cpp: implemented differently as IDVert class.

Mesh class has 3 vectors: one for vectors(Vector3D object), one for normals(Vector3D object), and one for faces(Face object). They store the data from the .obj file read.

How to Use:
===========================

Keyboard:
 
q: quits the program
r: enable rotation
t: translate the object
x: rotate around the X axis
y: rotate around the Y axis
z: rotate around the Z axis
+: increase size of object
-: decrease size of object
s: enable smooth shading
f: enable flat shading
n: toggle normal display on/off
p: draw object as polygons
w: draw object as wireframe
c: initialize a new cube
o: open an object file, give full name (including .obj) at prompt
h: writes an object file, give full name (including .obj) at prompt
k: shows a cylinder created using tesselation
l: creates a sphere in the camera view
d: creates a cone in the camera view

Note: All keys are not case sensitive (example: rotation will be enable if 'r' or 'R' is pressed).

Mouse: Mouse drag to move or rotate.

At any time, press r, then x, y, or z to switch from translation mode to rotation mode.
Press t to go back to translate mode.
 

