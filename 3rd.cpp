#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Define a type for 3D points
typedef float point[3];

// Initial vertices of the tetrahedron
point v[] = {
    {0.0, 0.0, 1.0},       // Vertex A
    {0.0, 0.942809, -0.33333}, // Vertex B
    {-0.816497, -0.471405, -0.333333}, // Vertex C
    {0.816497, -0.471405, -0.333333}  // Vertex D
};

static GLfloat theta[] = {0.0, 0.0, 0.0}; // Rotational angles
int n; // Number of subdivisions

// Function to display one triangle
void triangle(point a, point b, point c)
{
    glBegin(GL_POLYGON); // Start drawing a polygon (triangle in this case)
       glNormal3fv(a);   // Set the normal for lighting calculations
       glVertex3fv(a);   // Specify the first vertex
       glVertex3fv(b);   // Specify the second vertex
       glVertex3fv(c);   // Specify the third vertex
    glEnd();            // End drawing the polygon
}

// Function to subdivide a triangle into smaller triangles
void divide_triangle(point a, point b, point c, int m)
{
    point v1, v2, v3; // Midpoints of the triangle's edges
    int j;

    if (m > 0) // Check if further subdivision is needed
    {
        // Compute the midpoints of the edges
        for (j = 0; j < 3; j++) v1[j] = (a[j] + b[j]) / 2;
        for (j = 0; j < 3; j++) v2[j] = (a[j] + c[j]) / 2;
        for (j = 0; j < 3; j++) v3[j] = (b[j] + c[j]) / 2;

        // Recursively divide the smaller triangles
        divide_triangle(a, v1, v2, m - 1);
        divide_triangle(c, v2, v3, m - 1);
        divide_triangle(b, v3, v1, m - 1);
    }
    else
    {
        // Draw the triangle when the desired subdivision level is reached
        triangle(a, b, c);
    }
}

// Function to apply triangle subdivision to faces of the tetrahedron
void tetrahedron(int m)
{
    glColor3f(1.0, 0.0, 0.0); // Set color to red
    divide_triangle(v[0], v[1], v[2], m); // Front face
    glColor3f(0.0, 1.0, 0.0); // Set color to green
    divide_triangle(v[3], v[2], v[1], m); // Right face
    glColor3f(0.0, 0.0, 1.0); // Set color to blue
    divide_triangle(v[0], v[3], v[1], m); // Left face
    glColor3f(0.0, 0.0, 0.0); // Set color to black
    divide_triangle(v[0], v[2], v[3], m); // Bottom face
}

// Display callback function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and depth buffer
    glLoadIdentity(); // Load the identity matrix to reset transformations
    tetrahedron(n); // Draw the tetrahedron
    glFlush(); // Ensure all OpenGL commands are executed
}

// Reshape callback function
void myReshape(int w, int h)
{
    glViewport(0, 0, w, h); // Set the viewport to cover the whole window
    glMatrixMode(GL_PROJECTION); // Set the matrix mode to projection
    glLoadIdentity(); // Load the identity matrix
    // Set up orthographic projection
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
                2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
                2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW); // Set the matrix mode to modelview
    glutPostRedisplay(); // Request a redraw
}

// Main function
int main(int argc, char **argv)
{
    int i = 0;
    printf("Enter value of N: "); // Prompt for number of subdivisions
    scanf("%d", &i); // Read the number of subdivisions
    n = i; // Store the value in the global variable

    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Set display mode
    glutInitWindowSize(500, 500); // Set the window size
    glutCreateWindow("3D Tetrahedron Gasket"); // Create the window with a title
    glutReshapeFunc(myReshape); // Register the reshape callback function
    glutDisplayFunc(display); // Register the display callback function
    glEnable(GL_DEPTH_TEST); // Enable depth testing for proper occlusion handling
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set the background color to white
    glutMainLoop(); // Enter the GLUT main loop

    return 0; // Return 0 to indicate successful execution
}
