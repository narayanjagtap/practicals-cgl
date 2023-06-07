#include <GL/glut.h>
#include <cmath>

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500, 500, -500, 500);
}

void drawCircleBresenham(int centerX, int centerY, int radius)
{
    int x = 0;
    int y = radius;
    int d = 3 - (2 * radius);

    glBegin(GL_POINTS);

    while (x <= y)
    {
        glVertex2i(centerX + x, centerY + y);
        glVertex2i(centerX - x, centerY + y);
        glVertex2i(centerX + x, centerY - y);
        glVertex2i(centerX - x, centerY - y);
        glVertex2i(centerX + y, centerY + x);
        glVertex2i(centerX - y, centerY + x);
        glVertex2i(centerX + y, centerY - x);
        glVertex2i(centerX - y, centerY - x);

        if (d < 0)
        {
            d += (4 * x) + 6;
        }
        else
        {
            d += (4 * (x - y)) + 10;
            y--;
        }
        x++;
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    int centerX = 0;
    int centerY = 0;
    int radius = 200;

    drawCircleBresenham(centerX, centerY, radius);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham Circle Generation Algorithm (Simple)");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
