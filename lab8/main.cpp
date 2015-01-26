// Name: Katherine Gallaher
// Quarter, Year: Fall 2014
// Lab: M 8-11
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include "color.h"
#include <complex>
#include <iostream>
using namespace std;


vector<Color3d> colors;
Color3d temp(0,0,0);
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

// Renders a quad at cell (x, y) with dimensions CELL_LENGTH
void renderPixel(double x, double y, float r = 1.0, float g = 1.0, float b = 1.0)
{
	glBegin(GL_POINTS);
	glColor3f(r,g,b);//decides color of pixels
	glVertex2f(x,y);
	glEnd();
}

void renderJuliaSet(double xmin, double xmax, double ymin, double ymax)
{
	for(int i=0; i<100; i++)//fill color vector
	{
		temp.rotateHue(i*5);
		colors.push_back(temp);
	}

//	complex<double> val(-0.7795,0.134);
	complex<double> val(0.621,0);
	for(double i=xmin; i<xmax; i+= 0.01)
	{
		for(double j=ymin; j<ymax; j+=0.01)
		{
			complex<double> x(i,j);
			int iterations = 0;
			while(abs(x) < 2.0 && iterations < 100)
			{
				x = exp(x*x*x) -val;
//				x = x*x + val;
				iterations++;
			}
			int newi = (i+2)*800 /4;
			int newj = (j+2)*800 /4;
			renderPixel(newi,newj,abs(colors[iterations].r),abs(colors[iterations].g),abs(colors[iterations].b));
		}
	}
}

void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	renderJuliaSet(-2.0,2.0,-2.0,2.0);
	glutSwapBuffers();
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("CS 130 - Katherine Gallaher");
	

	// The default view coordinates is (-1.0, -1.0) bottom left & (1.0, 1.0) top right.
	// For the purposes of this lab, this is set to the number of pixels
	// in each dimension.
	glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);

	glutDisplayFunc(GL_render);
}

int main(int argc, char** argv)
{	
	GLInit(&argc, argv);
	glutMainLoop();
	return 0;
}


