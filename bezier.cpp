#include <GL/glut.h>
#include <cmath>

struct Point2D {
    float x, y;
};

const int maxControlPoints = 4;         // Maximum number of control points
Point2D controlPoints[maxControlPoints]; // Control points of the Bezier curve
const int numSegments = 100;            // Number of line segments to approximate the curve

// Function to compute the Bezier curve point at t
Point2D computeBezierPoint(float t) {
    float u = 1.0f - t;
    float coefficients[maxControlPoints];

    // Compute the coefficients using Pascal's triangle
    coefficients[0] = 1.0f;
    for (int i = 1; i < maxControlPoints; ++i)
        coefficients[i] = coefficients[i - 1] * u;

    Point2D bezierPoint = {0.0f, 0.0f};

    // Compute the Bezier curve point by multiplying control points with coefficients
    for (int i = 0; i < maxControlPoints; ++i) {
        float coefficient = coefficients[maxControlPoints - 1 - i];
        float powerTerm = pow(t, i);
        float x = controlPoints[i].x * coefficient * powerTerm;
        float y = controlPoints[i].y * coefficient * powerTerm;
        bezierPoint.x += x;
        bezierPoint.y += y;
    }

    return bezierPoint;
}

// Function to render the Bezier curve
void renderBezierCurve() {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= numSegments; ++i) {
        float t = static_cast<float>(i) / numSegments;
        Point2D point = computeBezierPoint(t);
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

// Function to display the OpenGL scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);

    // Render the Bezier curve
    renderBezierCurve();

    glFlush();
}

int main(int argc, char** argv) {
    // Add control points to define the shape of the Bezier curve
    controlPoints[0] = {0.1f, 0.1f};
    controlPoints[1] = {0.4f, 0.9f};
    controlPoints[2] = {0.8f, 0.2f};
    controlPoints[3] = {0.9f, 0.8f};

    glutInit(&argc, argv);
    glutCreateWindow("Bezier Curve");
    glutInitWindowSize(500, 500);
    glutDisplayFunc(display);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutMainLoop();

    return 0;
}
