////////////////////////////////////////////////////////////////////////////////
// OpenGL first animation program
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

#define TIME_PRECISION_FACTOR 0

unsigned char color[] = {255, 0, 0};

void draw()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3ub(color[0], color[1], color[2]);
        glVertex2d(-0.5, -0.5);
        glVertex2d(0.5, -0.5);
        glVertex2d(0.5, 0.5);
        glVertex2d(-0.5, 0.5);
    glEnd();
    
    // Swap buffers in double buffered mode
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void animate()
{
    static int startTime = 0;
    static int loops = 0;
    static int animationEnabled = 0;
    static float delta = 1;
    int currentTime;
    
    if (!startTime)
        startTime = glutGet(GLUT_ELAPSED_TIME);
    
    if (loops++ > TIME_PRECISION_FACTOR)
    {
        animationEnabled = 1;
        currentTime = glutGet(GLUT_ELAPSED_TIME);
        delta = (currentTime - startTime) / (loops * 1000.0);
        startTime = currentTime;
        loops = 0;
    }
    
    if (animationEnabled)
        glRotatef(90.0 * delta, 0, 0, 1);
    
    // Invoke drawing callback
    glutPostRedisplay();
}

void timer(int value)
{
    switch (value)
    {
        case 0:
            color[0] = 0;
            color[1] = 255;
            color[2] = 0;
            break;
        case 1:
            color[0] = 0;
            color[1] = 0;
            color[2] = 255;
            break;
        case 2:
            color[0] = 255;
            color[1] = 0;
            color[2] = 0;
            value = -1;
            break;
    }
    
    // Reset timer
    glutTimerFunc(1000, timer, ++value);
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 100);
    // Init display with RGB color palette and double buffering
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Test of animation");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    // Register callback function for continuous iterations
    glutIdleFunc(animate);
    // Register callback function for timer event to be called in 1000 
    // milliseconds with 0 as parameter
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    
    return 0;
}

