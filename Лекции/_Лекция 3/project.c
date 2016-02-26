////////////////////////////////////////////////////////////////////////////////
// OpenGL projection program
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

int perspective = 0;

void draw()
{
    glClearColor(0, 0, 0, 0);
    
    // Clear color buffer and zBuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBegin(GL_QUADS);
        glColor3ub(255, 0, 0);
        glVertex3d(-0.5, -0.5, -0.5);
        glColor3ub(0, 255, 0);
        glVertex3d(0.5, -0.5, -0.5);
        glColor3ub(0, 0, 255);
        glVertex3d(0.5, 0.5, -0.5);
        glColor3ub(255, 255, 0);
        glVertex3d(-0.5, 0.5, -0.5);
        
        glColor3ub(255, 0, 0);
        glVertex3d(-0.5, -0.5, -0.5);
        glColor3ub(0, 255, 0);
        glVertex3d(-0.5, -0.5, 0.5);
        glColor3ub(0, 0, 255);
        glVertex3d(-0.5, 0.5, 0.5);
        glColor3ub(255, 255, 0);
        glVertex3d(-0.5, 0.5, -0.5);
        
        glColor3ub(255, 0, 0);
        glVertex3d(-0.5, -0.5, 0.5);
        glColor3ub(0, 255, 0);
        glVertex3d(0.5, -0.5, 0.5);
        glColor3ub(0, 0, 255);
        glVertex3d(0.5, 0.5, 0.5);
        glColor3ub(255, 255, 0);
        glVertex3d(-0.5, 0.5, 0.5);
        
        glColor3ub(255, 0, 0);
        glVertex3d(0.5, -0.5, 0.5);
        glColor3ub(0, 255, 0);
        glVertex3d(0.5, 0.5, 0.5);
        glColor3ub(0, 0, 255);
        glVertex3d(0.5, 0.5, -0.5);
        glColor3ub(255, 255, 0);
        glVertex3d(0.5, -0.5, -0.5);
        
        glColor3ub(255, 0, 0);
        glVertex3d(-0.5, 0.5, -0.5);
        glColor3ub(0, 255, 0);
        glVertex3d(0.5, 0.5, -0.5);
        glColor3ub(0, 0, 255);
        glVertex3d(0.5, 0.5, 0.5);
        glColor3ub(255, 255, 0);
        glVertex3d(-0.5, 0.5, 0.5);
        
        glColor3ub(255, 0, 0);
        glVertex3d(-0.5, -0.5, -0.5);
        glColor3ub(0, 255, 0);
        glVertex3d(0.5, -0.5, -0.5);
        glColor3ub(0, 0, 255);
        glVertex3d(0.5, -0.5, 0.5);
        glColor3ub(255, 255, 0);
        glVertex3d(-0.5, -0.5, 0.5);
    glEnd();
    
    glutSwapBuffers();
}

void setupProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (perspective)
        gluPerspective(45, 1, 1, 10);
    else
        gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (perspective)
        glTranslated(0, 0, -3);
    glRotated(45, 1, 1, 0);
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    setupProjection();
}

void keyPressed(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        perspective = !perspective;
        setupProjection();
        glutPostRedisplay();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 100);
    // Init display with RGB color palette and double buffering 
    // and activate zBuffer
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Test of projection");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    // Register callback function to hanlde key ress events
    glutKeyboardFunc(keyPressed);
    // Enable zBuffer in OpenGL
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    
    return 0;
}

