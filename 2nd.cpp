#include <stdio.h>
#include <GL/glut.h>

// Define a type for 2D points
typedef float point2[2];

/* Initial triangle vertices for the Sierpinski Gasket */
point2 v[] = {{-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15}};
int n; // Number of subdivisions

/* Function to display one triangle */
void triangle(point2 a, point2 b, point2 c)
{
    glBegin(GL_TRIANGLES); // Start drawing a triangle
    glVertex2fv(a);        // Specify the first vertex
    glVertex2fv(b);        // Specify the second vertex
    glVertex2fv(c);        // Specify the third vertex
    glEnd();               // End drawing the triangle
}

/* Function to divide a triangle into smaller triangles */
void divide_triangle(point2 a, point2 b, point2 c, int m)
{
    point2 v0, v1, v2; // Midpoints of the triangle's edges
    int j;

    if (m > 0) // Check if further subdivision is needed
    {
        // Compute the midpoints of the edges
        for (j = 0; j < 2; j++) v0[j] = (a[j] + b[j]) / 2;
        for (j = 0; j < 2; j++) v1[j] = (a[j] + c[j]) / 2;
        for (j = 0; j < 2; j++) v2[j] = (b[j] + c[j]) / 2;

        // Recursively divide the smaller triangles
        divide_triangle(a, v0, v1, m - 1);
        divide_triangle(c, v1, v2, m - 1);
        divide_triangle(b, v2, v0, m - 1);
    }
    else
    {
        // Draw the triangle when the desired subdivision level is reached
        triangle(a, b, c);
    }
}

/* Display callback function */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
    divide_triangle(v[0], v[1], v[2], n); // Start the subdivision process
    glFlush(); // Ensure all OpenGL commands are executed
}

/* Initialization function */
void myinit()
{
    glMatrixMode(GL_PROJECTION); // Set the matrix mode to projection
    glLoadIdentity(); // Load the identity matrix
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0); // Set up a 2D orthographic viewing region
    glMatrixMode(GL_MODELVIEW); // Set the matrix mode to modelview
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set the background color to white
    glColor3f(0.0, 0.0, 0.0); // Set the drawing color to black
}

/* Main function */
int main(int argc, char **argv)
{
    printf(" No. of Subdivisions : ");
    scanf("%d", &n); // Read the number of subdivisions

    glutInit(&argc, argv); // Initialize the GLUT library
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode (single buffer and RGB)
    glutInitWindowSize(500, 500); // Set the window size
    glutCreateWindow("Sierpinski Gasket 2D triangle"); // Create the window with a title
    glutDisplayFunc(display); // Register the display callback function
    myinit(); // Call the initialization function
    glutMainLoop(); // Enter the GLUT main loop
    return 0; // Return 0 to indicate successful execution
}