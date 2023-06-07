#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;
void init()
{
    //Set the background color to white
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //Set 2D co-ordinate system
    gluOrtho2D(0,500,0,500);
}

void BresenhamLine(int x0, int y0, int x1, int y1)
{
    bool steep = abs(y1-y0) > abs(x1-x0);
    if(steep)
    {
	swap(x0, y0);
	swap(x1, y1);
    }
    if(x0 > x1)
    {
	swap(x0, x1);
	swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    int error = dx/2;
    int ystep = (y0 < y1);
    int y = y0;

    glBegin(GL_POINTS);
    for(int x = x0; x <= x1; ++x)
    {
	if(steep)
		glVertex2i(y, x);
	else
		glVertex2i(x, y);
	error -= dy;
        if(error < 0)
	{
		y += ystep;
		error += dx;
	}
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //Set color to black
    glColor3f(0.0, 0.0, 0.0);
    //Call Bresenham's line drawing algorithm
    BresenhamLine(100, 100, 400, 400);
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Line Drawing Algorithm");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
