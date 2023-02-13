#include <windows.h>
#include <GL/glut.h>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <iostream>
void display()
{
    // Clear the color buffer to the current clear color
    glClear(GL_COLOR_BUFFER_BIT);

    // Set the current color to red
    glColor3f(1.0, 0.0, 0.0);

    // Begin drawing a triangle
    glBegin(GL_TRIANGLES);

    // Specify the vertices of the triangle
    glVertex2f(-1.0, -1.0);  // Bottom left vertex
    glVertex2f(1.0, -1.0);   // Bottom right vertex
    glVertex2f(0.0, 1.0);    // Top vertex

    // End drawing the triangle
    glEnd();

    // Ensure that all OpenGL commands are executed immediately
    glFlush();
}

int main(int argc, char** argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);

    // Specify the display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Set the initial window size
    glutInitWindowSize(500, 500);

    // Create a window with the specified title
    glutCreateWindow("My Triangle");

    // Set the clear color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Register the display function as the callback for redrawing the window
    glutDisplayFunc(display);

    // Enter the main event loop
    glutMainLoop();

    // Return 0 to indicate successful completion
    return 0;
}
