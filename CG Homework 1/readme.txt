Homework 01 - CSE313 - Computer Graphics
Student: Rafael C. B. de Oliveira

Summary

This program was developed using C++ language, OpenGL and Glut. Microsoft Visual Studio Express 2012 was used for this project.
The project includes both a .cpp file and a header file. Both include comments that explain how the program works and the logic behind it.



The program displays initially an image of an Archimedean Spiral. User input will change the spiral's appearance depending on what he chooses to do with the tools provided by this program.
The radius of the Spiral is defined by: r = A * theta. Where the user can increase/decrease the value of A or the maximum value of theta. The user can use do a "swing-type" animation and
turn on/off a color "fading" mode for the graph.

This program requires the necessary OpenGL files. 


Extra features: 

Background color can be randomly changed and reverted back to default color (black).
The spiral's center can be translated in the +x or -x direction and the +y or -y direction. It can also be translated back to its original point.
Spiral can also be rotated by one third of pi.
If the windows is resized, the aspect ratio will be kept the same. glutReshapeFunc() was used.
The program is also able to vary the RGB color scheme along the curve by varying the hue smoothly along the curve.The function used to convert HSV to RGB is available on this site: http://www.cs.rit.edu/~ncs/color/t_convert.html
The program can also flip the Spiral in the x and y axis.

How to Use the Program:

Keyboard:

Press b - changes the color of the background to a different color
Press c - changes color of the background to the default color(black)
Press z - changes background color to white
Press a - increases the value of A
Press s - decreases the value of A
Press w - enters swing-type mode
Press f - enables fading mode/ disables fading mode
Press u - translates spiral +y
Press i - translates spiral -y
Press j - translates spiral +x
Press k - translates spiral -x
Press o - translates spiral back to origin(default position)
Press r - rotates spiral by one third of pi
Press h - varies the RGB color scheme along the Spiral curve
Press n - Flip x axis
Press m - Flip y axis
Press q - terminates the program.

Mouse:

Left click - increases value of maxK
Right click - decreases value of maxK

Note: inputs are case sensitive.