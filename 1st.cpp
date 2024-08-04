#include <GL/glut.h>
#include <stdio.h>

int x1, y1, x2, y2; // Global variables for the coordinates of the line

void myInit() 
{
    glClear(GL_COLOR_BUFFER_BIT);             // Clear the window
    glClearColor(0.0, 0.0, 0.0, 1.0);         // Set the background color to black
    glMatrixMode(GL_PROJECTION);              // Set the matrix mode to projection
    gluOrtho2D(0, 500, 0, 500);               // Set up a 2D orthographic viewing region
    glFlush();                                // Force execution of OpenGL commands
}

void draw_pixel(int x, int y) 
{ 
    glBegin(GL_POINTS);                       // Start drawing points
    glVertex2i(x, y);                         // Specify the coordinates for a point
    glEnd();                                  // End drawing
}

void draw_line(int x1, int x2, int y1, int y2) 
{ 
    int dx, dy, i, e;                         // Difference in x and y, loop counter, error
    int incx, incy, inc1, inc2;               // Increments for x and y, intermediate values
    int x, y;                                 // Current x and y coordinates

    dx = x2 - x1;                             // Calculate the change in x
    dy = y2 - y1;                             // Calculate the change in y

    if (dx < 0) dx = -dx;                     // Absolute value of dx
    if (dy < 0) dy = -dy;                     // Absolute value of dy

    incx = 1;
    if (x2 < x1) incx = -1;                   // Determine increment for x direction
    incy = 1;
    if (y2 < y1) incy = -1;                   // Determine increment for y direction

    x = x1; y = y1;                           // Start at the first point

    if (dx > dy) 
    {
        draw_pixel(x, y);                     // Plot the initial point
        e = 2 * dy - dx;                      // Initial value of the decision parameter
        inc1 = 2 * (dy - dx);                 // Increment used when e >= 0
        inc2 = 2 * dy;                        // Increment used when e < 0
        for (i = 0; i < dx; i++) 
        {
            if (e >= 0) 
            {
                y += incy;                    // Increment y-coordinate
                e += inc1;                    // Update decision parameter
            }
            else
                e += inc2;                    // Update decision parameter

            x += incx;                        // Increment x-coordinate
            draw_pixel(x, y);                 // Plot the new point
        }
    } 
    else 
    {
        draw_pixel(x, y);                     // Plot the initial point
        e = 2 * dx - dy;                      // Initial value of the decision parameter
        inc1 = 2 * (dx - dy);                 // Increment used when e >= 0
        inc2 = 2 * dx;                        // Increment used when e < 0
        for (i = 0; i < dy; i++) 
        {
            if (e >= 0) 
            {
                x += incx;                    // Increment x-coordinate
                e += inc1;                    // Update decision parameter
            }
            else
                e += inc2;                    // Update decision parameter

            y += incy;                        // Increment y-coordinate
            draw_pixel(x, y);                 // Plot the new point
        }
    }
}

void myDisplay() 
{
    draw_line(x1, x2, y1, y2);                // Draw the line using the coordinates
    glFlush();                                // Force execution of OpenGL commands
}

int main(int argc, char **argv) 
{ 
    printf("Enter (x1, y1, x2, y2)\n");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2); // Read the coordinates of the line from the user

    glutInit(&argc, argv);                    // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode (single buffer and RGB color)
    glutInitWindowSize(500, 500);             // Set the window size
    glutInitWindowPosition(0, 0);             // Set the window position
    glutCreateWindow("Bresenham's Line Drawing"); // Create the window with a title

    myInit();                                 // Call the initialization function
    glutDisplayFunc(myDisplay);               // Register the display callback function
    glutMainLoop();                           // Enter the GLUT main loop

    return 0;
}
