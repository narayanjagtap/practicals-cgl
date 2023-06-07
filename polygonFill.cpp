#include <GL/glut.h>

struct Point {
    int x, y;
};

const int MAX_VERTICES = 100;
Point vertices[MAX_VERTICES];
int numVertices = 0;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void drawPolygon()
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numVertices; i++) {
        glVertex2i(vertices[i].x, vertices[i].y);
    }
    glEnd();
}

void fillPolygon()
{
    int minY = vertices[0].y;
    int maxY = vertices[0].y;

    for (int i = 1; i < numVertices; i++) {
        if (vertices[i].y < minY) {
            minY = vertices[i].y;
        }
        if (vertices[i].y > maxY) {
            maxY = vertices[i].y;
        }
    }

    for (int y = minY; y <= maxY; y++) {
        int intersectionPoints[MAX_VERTICES];
        int numIntersections = 0;

        for (int i = 0, j = numVertices - 1; i < numVertices; j = i++) {
            if ((vertices[i].y < y && vertices[j].y >= y) || (vertices[j].y < y && vertices[i].y >= y)) {
                int x = vertices[i].x + ((y - vertices[i].y) / (vertices[j].y - vertices[i].y)) * (vertices[j].x - vertices[i].x);
                intersectionPoints[numIntersections++] = x;
            }
        }

        for (int i = 0; i < numIntersections - 1; i += 2) {
            glBegin(GL_LINES);
            glVertex2i(intersectionPoints[i], y);
            glVertex2i(intersectionPoints[i + 1], y);
            glEnd();
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    drawPolygon();
    fillPolygon();

    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        vertices[numVertices].x = x;
        vertices[numVertices].y = 500 - y;
        numVertices++;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Polygon Filling Algorithm");
    glutDisplayFunc(display);
    init();
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
