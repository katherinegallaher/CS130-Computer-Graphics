// Name: Katherine Gallaher
// Quarter, Year: Fall 2014
// Lab: M 8-11
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <math.h>
#include "point2d.h"
#include <vector>

using namespace std;
#include <iostream>

vector<Point2D> points;

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

void mouse(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cout<<x<<" "<<y<<endl;

		points.push_back(GLscreenToWindowCoordinates(Point2D(x,y)));
		//cout<<points[0].x <<" "<<points[0].y<<endl;
		glutPostRedisplay();
	}
}

void renderLine(int x0, int y0, int x1, int y1)
{
	double i;
	if(x1-x0 <0 || x1-x0 == 0)
		i=0;//line goes from right to left so create it at the origin then move it over
	else 
		i=round(x0);
	
	double m=0;
	if(x1-x0 != 0)
		m=double(y1-y0)/double(x1-x0);

	double y=y0+m*(i-x0);

	int originy= y0;
	int upto = x1;
	while(i<=upto)
	{
		if(x1-x0 == 0) //undefined lines
		{
			upto=abs(y1-y0-1);

			renderPixel(x0,originy);
			if(y1-y0 >=0)
				originy++;
			else
				originy--;
		}
	
		else if(x1-x0<0)//the line is going from right to left
		{
			if(m==0)//straight line
				renderPixel(i+x0/2,round(y));
			else if(m<0)
				renderPixel(i+x0/2,round(y)-y0/2);
			else 
				renderPixel(i+x0/2,round(y)+y0/2);
		}
		else //line goes left to right
			renderPixel(i,round(y));
		i++;
		y+=m;
	}
}

int dofactorial(int a)
{
	if(a <= 1)
		return 1;
	else
		a = a * dofactorial(a-1);
	
	return a;
}

float coefficient(float k,float i)
{
	float coef;
	coef = dofactorial(k) / (dofactorial(i)*dofactorial(k-i));
	return coef;
}

void Bezier(Point2D &p, double a)
{
	p.x =0;
	p.y = 0;

	for(float i=0; i<points.size(); i++)
	{
		p.x= p.x + coefficient(float(points.size() -1), i)  * pow(a,double(i)) * pow((1-a),points.size()-1-i) * points[i].x;
		p.y= p.y +coefficient(float(points.size() -1), i)  * pow(a,double(i)) * pow((1-a),points.size()-1-i) * points[i].y;

	}
}

void renderBezier()
{
	Point2D current, p;
	current.x = points[0].x;
	current.y = points[0].y;

	for(double t=0.0; t<=1.0; t+=0.01)
	{
		Bezier(p, t);
		renderLine(current.x,current.y,p.x,p.y);

		current.x = p.x;
		current.y = p.y;
	}
}

void renderCircle(int x0, int y0, int r)
{
	int i=0;
	int j = r;
	while(i <= j)
	{
		renderPixel(i+x0,j+y0);
		renderPixel(j+x0,i+y0);
		renderPixel(-i+x0,j+y0);
		renderPixel(i+x0,-j+y0);
		renderPixel(-j+x0,i+y0);
		renderPixel(j+x0,-i+y0);
		renderPixel(-i+x0,-j+y0);
		renderPixel(-j+x0,-i+y0);

		i++;
		double F = r*r - i*i - (j+0.5)*(j+0.5);
		if(F < 0)
			j--;
	}
}

void GL_render()
{
	glClear(GL_COLOR_BUFFER_BIT);

//	renderPixel(400,400);//single pixel
/*	
	renderLine(400,400,400,600);   //undefined slope, straight up 

	renderLine(400,400,600,600); //works
	renderLine(400,400,600,400); //works
	renderLine(400,400,600,200); //works

	renderLine(400,400,200,200); //works
	renderLine(400,400,200,400); //works
	renderLine(400,400,200,600); //works 

	renderLine(400,400,400,200);   //undefined slope, straight down

	renderCircle(400,400,200);

	*/
	 //checking if clicking works
//	if(points.size() >=2)
//	{
//		renderLine(points[0].x, points[0].y,points[1].x,points[1].y);
		//glBegin(GL_LINES);
		//glColor3f(1.0,1.0,1.0);//decides color of pixels
		//glVertex2f(points[0].x,points[0].y);
		//glVertex2f(points[1].x,points[1].y);
		//glEnd();
//	}

	if(points.size() >=2)
		renderBezier();
/*	
	if(points.size() >=3)
	{
		cout<<"point 1: "<<points[0].x<<" "<<points[0].y<<endl;
		cout<<"point 2: "<<points[1].x<<" "<<points[1].y<<endl;
		cout<<"point 3: "<<points[2].x<<" "<<points[2].y<<endl;
		renderCurve(points[0],points[1],points[2]);
	}
*/
	glutSwapBuffers();
}
//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// ...
	// Complete this function
	// ...
	glutCreateWindow("CS 130 - Katherine Gallaher");

	// The default view coordinates is (-1.0, -1.0) bottom left & (1.0, 1.0) top right.
	// For the purposes of this lab, this is set to the number of pixels
	// in each dimension.
	glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
	glutMouseFunc(mouse);
}

int main(int argc, char** argv)
{	
	GLInit(&argc, argv);

	glutDisplayFunc(GL_render);

	glutMainLoop();


	return 0;
}


