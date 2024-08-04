#include <stdlib.h>
#include <GL/glut.h>

// Define the vertices of a cube
GLfloat vertices[][3] = {
    {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0},   // Bottom face vertices
    {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0},     // Bottom face vertices
    {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0},     // Top face vertices
    {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}        // Top face vertices
};

// Define the colors corresponding to each vertex
GLfloat colors[][3] = {
    {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},    // Black, Red
    {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0},    // Yellow, Green
    {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0},    // Blue, Magenta
    {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}     // White, Cyan
};

// Function to draw a polygon with vertices a, b, c, and d
void polygon(int a, int b, int c, int d) {
    glBegin(GL_POLYGON);
        glColor3fv(colors[a]);
        glVertex3fv(vertices[a]);
        glColor3fv(colors[b]);
        glVertex3fv(vertices[b]);
        glColor3fv(colors[c]);
        glVertex3fv(vertices[c]);
        glColor3fv(colors[d]);
        glVertex3fv(vertices[d]);
    glEnd();
}

// Function to draw a color cube using the defined polygons
void colorcube() {
    polygon(0, 3, 2, 1);  // Back face
    polygon(2, 3, 7, 6);  // Top face
    polygon(0, 4, 7, 3);  // Left face
    polygon(1, 2, 6, 5);  // Right face
    polygon(4, 5, 6, 7);  // Front face
    polygon(0, 1, 5, 4);  // Bottom face
}

// Rotation angles for x, y, and z axes
static GLfloat theta[] = {0.0, 0.0, 0.0};
// The current axis of rotation: 0 = x, 1 = y, 2 = z
static GLint axis = 2;
// Viewer position
static GLdouble viewer[] = {0.0, 0.0, 5.0};

void display(void) {
    // Clear the display and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Set the viewer's position and direction
    gluLookAt(viewer[0], viewer[1], viewer[2], 
              0.0, 0.0, 0.0, 
              0.0, 1.0, 0.0);
    // Apply rotations around x, y, and z axes
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    // Draw the color cube
    colorcube();
    glFlush();
    glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y) {
    // Determine which axis to rotate based on mouse button
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;    // Rotate around x-axis
    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;  // Rotate around y-axis
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;   // Rotate around z-axis
    theta[axis] += 4.0; // Increment rotation angle
    if (theta[axis] > 360.0) theta[axis] -= 360.0; // Keep angles within 360 degrees
    display(); // Redraw
}

void keys(unsigned char key, int x, int y) {
    // Modify viewer position based on key input
    if (key == 'x') viewer[0] -= 1.0;
    if (key == 'X') viewer[0] += 1.0;
    if (key == 'y') viewer[1] -= 1.0;
    if (key == 'Y') viewer[1] += 1.0;
    if (key == 'z') viewer[2] -= 1.0;
    if (key == 'Z') viewer[2] += 1.0;
    display(); // Redraw
}

void myReshape(int w, int h) {
    glViewport(0, 0, w, h); // Set viewport size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set the perspective projection
    if (w <= h)
        glFrustum(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
                  2.0 * (GLfloat) h / (GLfloat) w, 2.0, 20.0);
    else
        glFrustum(-2.0, 2.0, -2.0 * (GLfloat) w / (GLfloat) h,
                  2.0 * (GLfloat) w / (GLfloat) h, 2.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set display mode
    glutInitWindowSize(500, 500);  // Set window size
    glutCreateWindow("Colorcube Viewer");  // Create window
    glutReshapeFunc(myReshape);  // Register reshape function
    glutDisplayFunc(display);  // Register display function
    glutMouseFunc(mouse);  // Register mouse callback
    glutKeyboardFunc(keys);  // Register keyboard callback
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glutMainLoop();  // Enter the main loop
    return 0;
}
