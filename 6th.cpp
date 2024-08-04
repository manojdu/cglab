#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.1416

static int win, val = 0, CMenu; // Global variables for window ID and menu value

// Function prototypes
void CreateMenu(void);
void Menu(int value);

// Structure to store 3D points
struct wcPt3D {
    GLfloat x, y, z;
};

// Window and world coordinates settings
GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = 0.0, xwcMax = 130.0;
GLfloat ywcMin = 0.0, ywcMax = 130.0;

// Function to compute binomial coefficients
void bino(GLint n, GLint *C) {
    GLint k, j;
    for (k = 0; k <= n; k++) {
        C[k] = 1;
        for (j = n; j >= k + 1; j--)
            C[k] *= j;
        for (j = n - k; j >= 2; j--)
            C[k] /= j;
    }
}

// Function to compute a point on the Bezier curve
void computeBezPt(GLfloat u, struct wcPt3D *bezPt, GLint nCtrlPts, struct wcPt3D *ctrlPts, GLint *C) {
    GLint k, n = nCtrlPts - 1;
    GLfloat bezBlendFcn;
    bezPt->x = bezPt->y = bezPt->z = 0.0;

    for (k = 0; k < nCtrlPts; k++) {
        bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
        bezPt->x += ctrlPts[k].x * bezBlendFcn;
        bezPt->y += ctrlPts[k].y * bezBlendFcn;
        bezPt->z += ctrlPts[k].z * bezBlendFcn;
    }
}

// Function to draw a Bezier curve
void bezier(struct wcPt3D *ctrlPts, GLint nCtrlPts, GLint nBezCurvePts) {
    struct wcPt3D bezCurvePt;
    GLfloat u;
    GLint *C = new GLint[nCtrlPts];
    bino(nCtrlPts - 1, C);

    glBegin(GL_LINE_STRIP);
    for (int k = 0; k <= nBezCurvePts; k++) {
        u = GLfloat(k) / GLfloat(nBezCurvePts);
        computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C);
        glVertex2f(bezCurvePt.x, bezCurvePt.y);
    }
    glEnd();
    delete[] C;
}

// Display callback function
void displayFcn() {
    GLint nCtrlPts = 4, nBezCurvePts = 20;
    static float theta = 0;
    struct wcPt3D ctrlPts[4] = {{20, 100, 0}, {30, 110, 0}, {50, 90, 0}, {60, 100, 0}};

    // Animate control points
    ctrlPts[1].x += 10 * sin(theta * PI / 180.0);
    ctrlPts[1].y += 5 * sin(theta * PI / 180.0);
    ctrlPts[2].x -= 10 * sin((theta + 30) * PI / 180.0);
    ctrlPts[2].y -= 10 * sin((theta + 30) * PI / 180.0);
    ctrlPts[3].x -= 4 * sin((theta) * PI / 180.0);
    ctrlPts[3].y += sin((theta - 30) * PI / 180.0);
    theta += 0.1;

    // Clear the window
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5);

    // Draw flag based on menu selection
    if (val == 1) { // Indian Flag
        glPushMatrix();
        glLineWidth(5);
        glColor3f(1.0, 0.5, 0); // Orange
        for (int i = 0; i < 8; i++) {
            glTranslatef(0, -0.8, 0);
            bezier(ctrlPts, nCtrlPts, nBezCurvePts);
        }
        glColor3f(1, 1, 1); // White
        for (int i = 0; i < 8; i++) {
            glTranslatef(0, -0.8, 0);
            bezier(ctrlPts, nCtrlPts, nBezCurvePts);
        }
        glColor3f(0, 1.0, 0); // Green
        for (int i = 0; i < 8; i++) {
            glTranslatef(0, -0.8, 0);
            bezier(ctrlPts, nCtrlPts, nBezCurvePts);
        }
        glPopMatrix();
        glColor3f(0.7, 0.5, 0.3);
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex2f(20, 100);
        glVertex2f(20, 40);
        glEnd();
        glFlush();
    }
    if (val == 2) { // Karnataka Flag
        glPushMatrix();
        glLineWidth(5);
        glColor3f(1.0, 1.0, 0.0); // Yellow
        for (int i = 0; i < 12; i++) {
            glTranslatef(0, -0.8, 0);
            bezier(ctrlPts, nCtrlPts, nBezCurvePts);
        }
        glColor3f(1, 0.0, 0.0); // Red
        for (int i = 0; i < 12; i++) {
            glTranslatef(0, -0.8, 0);
            bezier(ctrlPts, nCtrlPts, nBezCurvePts);
        }
        glPopMatrix();
        glColor3f(0.7, 0.5, 0.3);
        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex2f(20, 100);
        glVertex2f(20, 40);
        glEnd();
        glFlush();
    }

    // Redraw the scene
    glutPostRedisplay();
    glutSwapBuffers();
}

// Window reshape callback function
void winReshapeFun(GLint newWidth, GLint newHeight) {
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

// Menu creation function
void CreateMenu(void) {
    CMenu = glutCreateMenu(Menu); // Create menu
    glutAddMenuEntry("Indian Flag", 1);
    glutAddMenuEntry("Karnataka Flag", 2);
    glutAddMenuEntry("Exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to right button
}

// Menu callback function
void Menu(int value) {
    if (value == 0) {
        glutDestroyWindow(win);
        exit(0);
    } else {
        val = value;
    }
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set display mode
    glutInitWindowPosition(50, 50); // Set window position
    glutInitWindowSize(winWidth, winHeight); // Set window size
    win = glutCreateWindow("Prg. 8 Bezier Curve"); // Create window
    CreateMenu(); // Create menu
    glutDisplayFunc(displayFcn); // Register display callback function
    glutReshapeFunc(winReshapeFun); // Register reshape callback function
    glutMainLoop(); // Enter main loop
    return 0;
}
