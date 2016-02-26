////////////////////////////////////////////////////////////////////////////////
// OpenGL first program
// Special for course "Algorithmic basics of multimedia"
//
// Copyright (C) 2011 by icosaeder
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "GL/glut.h"

void draw()
{
    // Set background color (actually, the color that fills color buffer and 
    // "cleans up" the scene) to black
    glClearColor(0, 0, 0, 0);
    // Force color buffer to fill with clear color
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw geometry connecting all the given vertices to quad areas
    glBegin(GL_QUADS);
        glColor3ub(255, 0, 0);
        glVertex2d(-0.5, -0.5);
        glColor3ub(0, 255, 0);
        glVertex2d(0.5, -0.5);
        glColor3ub(0, 0, 255);
        glVertex2d(0.5, 0.5);
        glColor3ub(255, 255, 0);
        glVertex2d(-0.5, 0.5);
    glEnd();
    // Force pipeline to execute commands from command buffer
    glFlush();
}

void reshape(int width, int height)
{
    // Set viewport to match whole window area
    glViewport(0, 0, width, height);
    // Switch matrix mode to projection
    glMatrixMode(GL_PROJECTION);
    // Load the E-matrix to drop all the previous projection settings
    glLoadIdentity();
    // Set the scene to be a square [-1; 1] x [-1; 1]
    gluOrtho2D(-1, 1, -1, 1);
    // Swtich matrix mode back to modelview
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    // Inirialize GLUT
    glutInit(&argc,argv);
    // Set window size to 640x640
    glutInitWindowSize(640, 640);
    // Set initial window position on screen at 100x100
    glutInitWindowPosition(100, 100);
    // Set display mode to use RGB color model
    glutInitDisplayMode(GLUT_RGB);
    // Create window with parameres set by previous calls 
    // and title "Test of OpenGL"
    glutCreateWindow("Test of OpenGL");
    // Register callback function for drawing frame
    glutDisplayFunc(draw);
    // Register callback function for handling window resizing event
    glutReshapeFunc(reshape);
    // Start drawing loop
    glutMainLoop();
    
    return 0;
}

