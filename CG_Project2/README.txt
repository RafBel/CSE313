========================================================================
    			Project 2 - Phase1  - Overview
		  Author: Rafael C. B. de Oliveira
========================================================================

Overview:
===========================

This program was made using Visual Studio 2012 Express, C++, and the OpenGL API for the CSE313 - Computer Graphics course.

Requirements to run the project: Visual Studio 2012 Express and the necessary OpenGL files.

The skeleton code was used for this project.
For phase 01, the missing code for CTreePart::CTreePart() has been completed with the code for procedural tree generation, and the depth level for the tree has been properly updated in CScene::build().
This program is able to create random generated trees. In other words, the program will create different trees every time it is run.

For phase 02, the missing code for the rest of the project has been filled in. Smaller bugs have been added and they follow around their "mother". All the forces have been calculated and 
added, so the bugs won't hit each other or the tree. The main bug wanders around the scene and the other bugs follow her around.
Shadows have also been added to the scene using shadowProject().


Extra Credit:
===========================


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
s: toggles shadows on/off (on program start, it is set to on)


Note: All keys are case sensitive.

Mouse: Mouse drag to move or rotate.

At any time, press r, then x, y, or z to switch from translation mode to rotation mode.
Press t to go back to translate mode.
 

