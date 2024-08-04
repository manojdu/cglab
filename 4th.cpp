#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

// Initial triangle vertices
GLfloat t[3][3] = {
    {10.0, 30.0, 20.0},  // X coordinates
    {20.0, 20.0, 40.0},  // Y coordinates
    {1.0, 1.0, 1.0}      // Homogeneous coordinates
};

// Rotation matrix and result matrix
GLfloat rotatemat[3][3] = {{0}, {0}, {0}};
GLfloat result[3][3] = {{0}, {0}, {0}};

// Fixed point for rotation
GLfloat xr = 10.0;
GLfloat yr = 20.0;

// Rotation angle and choice
GLfloat theta;
GLint ch;

// Matrix multiplication function
void multiply() {
    int i, j, k;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (k = 0; k < 3; k++) {
                result[i][j] += rotatemat[i][k] * t[k][j];
            }
        }
    }
}

// Rotation about the origin
void rotate_about_origin() {
    rotatemat[0][0] = cos(theta);
    rotatemat[0][1] = -sin(theta);
    rotatemat[0][2] = 0;
    rotatemat[1][0] = sin(theta);
    rotatemat[1][1] = cos(theta);
    rotatemat[1][2] = 0;
    rotatemat[2][0] = 0;
    rotatemat[2][1] = 0;
    rotatemat[2][2] = 1;
    multiply();
}

// Rotation about a fixed point
void rotate_about_fixed_point() {
    GLfloat m, n;
    m = xr * (1 - cos(theta)) + yr * sin(theta);
    n = yr * (1 - cos(theta)) - xr * sin(theta);
    
    rotatemat[0][0] = cos(theta);
    rotatemat[0][1] = -sin(theta);
    rotatemat[0][2] = m;
    rotatemat[1][0] = sin(theta);
    rotatemat[1][1] = cos(theta);
    rotatemat[1][2] = n;
    rotatemat[2][0] = 0;
    rotatemat[2][1] = 0;
    rotatemat[2][2] = 1;
    multiply();
}

// Draw the original triangle
void draw_triangle() {
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex2f(t[0][0], t[1][0]);
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex2f(t[0][1], t[1][1]);
    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex2f(t[0][2], t[1][2]);
    glEnd();
    glFlush();
}

// Draw the rotated triangle
void draw_rotated_triangle() {
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex2f(result[0][0], result[1][0]);
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex2f(result[0][1], result[1][1]);
    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex2f(result[0][2], result[1][2]);
    glEnd();
    glFlush();
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_triangle();
    if (ch == 1) {
        rotate_about_origin();
    } else if (ch == 2) {
        rotate_about_fixed_point();
    }
    draw_rotated_triangle();
}

// Initialization function
void myinit() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50.0, 50.0, -50.0, 50.0); // Orthographic projection
}

// Main function
int main(int argc, char** argv) {
    printf("***Rotation***\n1. Rotation about origin\n2. Rotation about a fixed point (xr, yr)\n");
    printf("Enter choice: ");
    scanf("%d", &ch);
    printf("Enter the rotation angle in degrees: ");
    scanf("%f", &theta);
    
    theta = theta * (M_PI / 180.0); // Convert angle to radians
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Triangle Rotation");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    
    return 0;
}
